//
// Created by shi on 2020/11/20.
//

#ifndef BOOST_ASIO_11_SESSION_H
#define BOOST_ASIO_11_SESSION_H

#include <memory>
#include <boost/asio.hpp>
#include <utility>
#include <array>

#include "handle_memory.h"
#include "custom_alloc_handler.h"

namespace shi {

    using namespace boost::asio::ip;
    class session : public std::enable_shared_from_this<session> {
    public:
        explicit session(tcp::socket socket)
            : socket_(std::move(socket))
        {

        }

        void start()
        {
            do_read();
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_),
                    make_custom_alloc_handler(handleMemory_,
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec) {
                                    do_write(length);
                                }
                            }));
        }


        void do_write(std::size_t length)
        {
            auto self(shared_from_this());
            boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                    make_custom_alloc_handler(handleMemory_,
                            [this, self](boost::system::error_code ec, std::size_t) {
                                if (!ec) {
                                    do_read();
                                }
                            }));
        }

        tcp::socket socket_;
        std::array<char, 1024> data_{};
        handle_memory handleMemory_;
    };

}


#endif //BOOST_ASIO_11_SESSION_H
