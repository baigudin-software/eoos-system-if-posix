/**
 * @file      sys.Heap.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Heap.hpp"

namespace eoos
{
namespace sys
{

Heap::Heap() : Parent()
{
}

Heap::~Heap()
{
}

bool_t Heap::isConstructed() const
{
    return Parent::isConstructed();
}

void* Heap::allocate(size_t const size, void* const ptr)
{
    void* addr;
    if(ptr == NULLPTR)
    {
        addr = Allocator::allocate(size);
    }
    else
    {
        addr = ptr;
    }
    return addr;
}

void Heap::free(void* const ptr)
{
    Allocator::free(ptr);
}

} // namespace sys
} // namespace eoos
