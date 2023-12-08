/**
 * @file      sys.Heap.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Heap.hpp"

namespace eoos
{
namespace sys
{

Heap::Heap() 
    : api::Heap() {
}

Heap::~Heap()
{
}

bool_t Heap::isConstructed() const
{
    return true;
}

void* Heap::allocate(size_t const size, void* ptr)
{
    static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
    #ifdef EOOS_GLOBAL_ENABLE_NO_HEAP
    static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
    return NULLPTR;
    #else
    return ::malloc(size);
    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
}

void Heap::free(void* ptr)
{
    #ifdef EOOS_GLOBAL_ENABLE_NO_HEAP
    static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4        
    #else
    ::free(ptr);
    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
}

} // namespace sys
} // namespace eoos
