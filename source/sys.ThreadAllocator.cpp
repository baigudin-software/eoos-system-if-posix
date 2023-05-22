/**
 * @file      sys.ThreadAllocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.ThreadAllocator.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

void* ThreadAllocator::allocate(size_t size)
{
    return System::getSystem().getMemoryManager().getThreadMemory().allocate(size, NULLPTR);
}

void ThreadAllocator::free(void* ptr)
{
    return System::getSystem().getMemoryManager().getThreadMemory().free(ptr);
}

} // namespace sys
} // namespace eoos
