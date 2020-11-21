//
// Created by shi on 2020/11/21.
//

#include <thread>

#include "src/client/chat_client.hpp"

int main(int argc, char** argv)
{
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        shi::ChatClient c(io_service, endpoint_iterator);

        std::thread t([&io_service]{ io_service.run(); });

        char line[shi::ChatMessage::max_body_length + 1]{};
        while (std::cin.getline(line, shi::ChatMessage::max_body_length + 1)) {
            std::cout << "\n====>>>> 发送消息" << line << '\n';
            shi::ChatMessage msg;
            msg.bodyLength(std::strlen(line));
            std::memcpy((void *) msg.body(), line, msg.bodyLength());
            msg.encodeHeader();
            c.write(msg);
        }

        c.close();
        t.join();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    return 0;
}