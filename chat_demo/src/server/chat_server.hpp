//
// Created by shi on 2020/11/21.
//

#ifndef CHAT_DEMO_CHAT_SERVER_HPP
#define CHAT_DEMO_CHAT_SERVER_HPP

#include <boost/asio.hpp>
#include "chat_room.hpp"
#include "chat_session.h"

namespace shi {
    class ChatServer
    {
    public:
        ChatServer(boost::asio::io_service& ioService,
                const boost::asio::ip::tcp::endpoint& endpoint)
                : acceptor_(ioService, endpoint)
                , socket_(ioService)
        {
            doAccept();
        }

    private:
        /**
         * @brief: 处理连接的客户端套接字，并创建一个回话对象
         * */
        void doAccept()
        {
            acceptor_.async_accept(socket_,
                    [this](boost::system::error_code ec)
                    {
                        if (!ec) {
                            std::make_shared<ChatSession>(std::move(socket_), room_)->start();
                            std::cout << "\n====>>>> 接入新的客户端\n";
                        }

                        doAccept();
                    });
        }

    private:
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::ip::tcp::socket socket_;
        ChatRoom room_;
    };
}

#endif //CHAT_DEMO_CHAT_SERVER_HPP
