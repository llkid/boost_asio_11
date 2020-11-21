//
// Created by shi on 2020/11/21.
//

#ifndef CHAT_DEMO_CHAT_CLIENT_HPP
#define CHAT_DEMO_CHAT_CLIENT_HPP

#include <boost/asio.hpp>
#include <deque>
#include <utility>
#include <iostream>

#include "chat_message.hpp"

namespace shi {
    using boost::asio::ip::tcp;
    typedef std::deque<ChatMessage> ChatMessageQueue;
    class ChatClient
    {
    public:
        ChatClient(boost::asio::io_service& io_service,
                tcp::resolver::iterator endpoint_iterator)
                : io_service_(io_service)
                , socket_(io_service)
        {
            doConnect(std::move(endpoint_iterator));
        }

        void write(const ChatMessage& msg)
        {
            io_service_.post(
                    [this, msg]()
                    {
                        bool write_in_progress = !write_msgs_.empty();
                        write_msgs_.push_back(msg);
                        if (!write_in_progress) {
                            doWrite();
                        }
                    });
        }

        void close()
        {
            io_service_.post([this]{ socket_.close(); });
        }

    private:
        void doConnect(tcp::resolver::iterator endpoint_iterator)
        {
            boost::asio::async_connect(socket_, std::move(endpoint_iterator),
                    [this](boost::system::error_code ec, const tcp::resolver::iterator&)
                    {
                        if (!ec) {
                            doReadHeader();
                        }
                    });
        }

        void doReadHeader()
        {
            boost::asio::async_read(socket_,
                    boost::asio::buffer(read_msg_.data(), ChatMessage::header_length),
                    [this](boost::system::error_code ec, std::size_t)
                     {
                         if (!ec && read_msg_.decodeHeader()) {
                             doReadBody();
                         } else {
                             socket_.close();
                         }
                     });
        }

        void doReadBody()
        {
            boost::asio::async_read(socket_,
                    boost::asio::buffer(read_msg_.body(), read_msg_.bodyLength()),
                    [this](boost::system::error_code ec, std::size_t)
                     {
                         if (!ec) {
                             std::cout << "\n====>>>> 接收到新的消息:\n";
                             std::cout.write(read_msg_.body(), read_msg_.bodyLength());
                             std::cout << '\n';
                             doReadHeader();
                         } else {
                             socket_.close();
                         }
                     });
        }

        void doWrite()
        {
            boost::asio::async_write(socket_,
                    boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                    [this](boost::system::error_code ec, std::size_t)
                     {
                        if (!ec) {
                            write_msgs_.pop_front();
                            if (!write_msgs_.empty()) {
                                doWrite();
                            }
                        } else {
                            socket_.close();
                        }
                     });
        }

    private:
        boost::asio::io_service& io_service_;
        tcp::socket socket_;
        ChatMessage read_msg_;
        ChatMessageQueue write_msgs_;
    };
}


#endif //CHAT_DEMO_CHAT_CLIENT_HPP
