//
// Created by shi on 2020/11/20.
//

#ifndef BOOST_ASIO_11_CUSTOM_ALLOC_HANDLER_H
#define BOOST_ASIO_11_CUSTOM_ALLOC_HANDLER_H

#include "handle_memory.h"
#include "handle_allocator.h"

namespace shi {

    template<typename Handler>
    class custom_alloc_handler
    {
    public:
        using allocator_type = handle_allocator<Handler>;

        custom_alloc_handler(handle_memory& m, Handler h)
            : memory_(m), handler_(h)
        {

        }

        allocator_type get_allocator() const noexcept
        {
            return allocator_type(memory_);
        }

        template<typename ...Args>
        void operator()(Args&&... args)
        {
            handler_(std::forward<Args>(args)...);
        }

    private:
        handle_memory& memory_;
        Handler handler_;
    };

    // Helper function to wrap a handler object to add custom allocation
    template<typename Handler>
    inline custom_alloc_handler<Handler> make_custom_alloc_handler(
            handle_memory&m, Handler h)
    {
        return custom_alloc_handler<Handler>(m, h);
    }

}

#endif //BOOST_ASIO_11_CUSTOM_ALLOC_HANDLER_H
