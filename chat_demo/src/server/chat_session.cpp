//
// Created by shi on 2020/11/21.
//

#include "chat_session.h"

namespace shi {
    ChatSession::ChatSession(boost::asio::ip::tcp::socket socket, shi::ChatRoom &room)
        : socket_(std::move(socket))
        , room_(room)
    {

    }

    void ChatSession::start() {
        room_.join(shared_from_this());
        doReadHeader();
    }

    void ChatSession::deliver(const ChatMessage &msg) {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            doWrite();
        }
    }

    void ChatSession::doReadHeader() {
        auto self(shared_from_this());
        boost::asio::async_read(socket_,
                boost::asio::buffer(read_msg_.data(), ChatMessage::header_length),
                [this, self](boost::system::error_code ec, std::size_t)
                 {
                     if (!ec && read_msg_.decodeHeader()) {
                         doReadBody();
                     } else {
                         room_.leave(shared_from_this());
                     }
                 });
    }

    void ChatSession::doReadBody() {
        auto self(shared_from_this());
        boost::asio::async_read(socket_,
                boost::asio::buffer(read_msg_.body(), read_msg_.bodyLength()),
                [this, self](boost::system::error_code ec, std::size_t)
                {
                    if (!ec) {
                        room_.deliver(read_msg_);
                        doReadHeader();
                    } else {
                        room_.leave(shared_from_this());
                    }
                });
    }

    void ChatSession::doWrite() {
        auto self(shared_from_this());
        boost::asio::async_write(socket_,
                boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                [this, self](boost::system::error_code ec, std::size_t)
                {
                    if (!ec) {
                        write_msgs_.pop_front();
                        if (!write_msgs_.empty()) {
                            doWrite();
                        }
                    } else {
                        room_.leave(shared_from_this());
                    }
                });
    }
}
