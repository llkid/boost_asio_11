#include "server.h"

using namespace shi;

int main(int argc, char** argv) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        boost::asio::io_service ioService;
        server s(ioService, std::atoi(argv[1]));
        ioService.run();
    } catch (std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << '\n';
    }

    return 0;
}
