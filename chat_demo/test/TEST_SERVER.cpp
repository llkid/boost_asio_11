//
// Created by shi on 2020/11/21.
//

#include <iostream>
#include <list>
#include <boost/asio.hpp>

#include "src/server/chat_server.hpp"

int main(int argc, char** argv)
{
    try {
        if (argc < 2) {
            std::cerr << "Usage: chat_server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service ioService;

        std::list<shi::ChatServer> servers;
        for (int i = 1; i < argc; ++i) {
            // endpoint 对应一个端口号，客户端通过接入相同的端口号进行聊天
            // 不同的端口号，类似不同的聊天频道
            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(ioService, endpoint);
        }
        ioService.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    return 0;
}
