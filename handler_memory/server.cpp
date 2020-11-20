//
// Created by shi on 2020/11/20.
//

#include "server.h"

namespace shi {

    server::server(boost::asio::io_service &ioService, short port)
        : acceptor_(ioService, tcp::endpoint(tcp::v4(), port)),
                socket_(ioService)
    {
        do_accept();
    }

    void server::do_accept() {
        acceptor_.async_accept(socket_,
                [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<session>(std::move(socket_))->start();
            }
            do_accept();
        });
    }
}