/**
 * @file      sys.MutexAllocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexAllocator.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

void* MutexAllocator::allocate(size_t size)
{
    return System::getSystem().getMemoryManager().getMutexMemory().allocate(size, NULLPTR);
}

void MutexAllocator::free(void* ptr)
{
    return System::getSystem().getMemoryManager().getMutexMemory().free(ptr);
}

} // namespace sys
} // namespace eoos
