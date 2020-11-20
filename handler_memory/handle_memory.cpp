//
// Created by shi on 2020/11/20.
//

#include "handle_memory.h"

namespace shi {
    shi::handle_memory::handle_memory() : in_use_(false) {

    }

    void *handle_memory::allocate(std::size_t size) {
        if (!in_use_ && size < sizeof(storage_)) {
            in_use_ = true;
            return &storage_;
        } else {
            return ::operator new(size);
        }
    }

    void handle_memory::deAllocated(void *pointer) {
        if (pointer == &storage_) {
            in_use_ = false;
        } else {
            ::operator delete(pointer);
        }
    }
}
