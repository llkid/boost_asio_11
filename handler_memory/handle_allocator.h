//
// Created by shi on 2020/11/20.
//

#ifndef BOOST_ASIO_11_HANDLE_ALLOCATOR_H
#define BOOST_ASIO_11_HANDLE_ALLOCATOR_H

#include "handle_memory.h"

namespace shi {

    template<typename T>
    class handle_allocator
    {
    public:
        using value_type = T;

        explicit handle_allocator(handle_memory& mem)
            : memory_(mem)
        {

        }

        template<typename U>
        explicit handle_allocator(const handle_allocator<U>& other) noexcept
            : memory_(other.memory_)
        {

        }

        bool operator==(const handle_allocator& other) const noexcept
        {
            return &memory_ == &other.memory_;
        }

        bool operator!=(const handle_allocator& other) const noexcept
        {
            return &memory_ != &other.memory_;
        }

        T* allocate(std::size_t n) const
        {
            return static_cast<T*>(memory_.allocate(sizeof(T) * n));
        }

        void deAllocate(T* p, std::size_t) const
        {
            return memory_.deAllocated(p);
        }

    private:
        template <typename> friend class handle_allocator;

        // The underlying memory
        handle_memory& memory_;
    };

}

#endif //BOOST_ASIO_11_HANDLE_ALLOCATOR_H
