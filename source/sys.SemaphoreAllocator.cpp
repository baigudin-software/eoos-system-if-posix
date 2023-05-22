/**
 * @file      sys.SemaphoreAllocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreAllocator.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

void* SemaphoreAllocator::allocate(size_t size)
{
    return System::getSystem().getMemoryManager().getSemaphoreMemory().allocate(size, NULLPTR);
}

void SemaphoreAllocator::free(void* ptr)
{
    return System::getSystem().getMemoryManager().getSemaphoreMemory().free(ptr);
}

} // namespace sys
} // namespace eoos
