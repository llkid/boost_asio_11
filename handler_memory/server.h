//
// Created by shi on 2020/11/20.
//

#ifndef BOOST_ASIO_11_SERVER_H
#define BOOST_ASIO_11_SERVER_H

#include "session.h"

namespace shi {
    class server {
    public:
        server(boost::asio::io_service& ioService, short port);

    private:
        void do_accept();

        tcp::acceptor acceptor_;
        tcp::socket socket_;
    };
}


#endif //BOOST_ASIO_11_SERVER_H
