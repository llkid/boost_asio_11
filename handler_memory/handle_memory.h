//
// Created by shi on 2020/11/20.
//

#ifndef BOOST_ASIO_11_HANDLE_MEMORY_H
#define BOOST_ASIO_11_HANDLE_MEMORY_H

#include <memory>
#include <iostream>
#include <type_traits>

namespace shi {

    class handle_memory {
    public:
        handle_memory();
        handle_memory(const handle_memory&) = delete;
        handle_memory& operator=(const handle_memory&) = delete;

        void* allocate(std::size_t size);
        void deAllocated(void* pointer);

    private:
        // Storage space used for handler-based custom memory allocation.
        typename std::aligned_storage<1024>::type storage_{};

        // Whether the handler-based custom allocation storage has been used.
        bool in_use_;
    };

}


#endif //BOOST_ASIO_11_HANDLE_MEMORY_H
