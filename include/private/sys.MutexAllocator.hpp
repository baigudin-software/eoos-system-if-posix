/**
 * @file      sys.MutexAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXALLOCATOR_HPP_
#define SYS_MUTEXALLOCATOR_HPP_

#include "sys.Mutex.hpp"
#include "lib.Allocator.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class MutexAllocator
 * @brief Mutex memory allocator.
 */ 
class MutexAllocator : public lib::Allocator
{

public:

    #ifdef EOOS_GLOBAL_ENABLE_NO_HEAP

    /**
     * @brief Allocate memory for mutex.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t size)
    {
        return NULLPTR;
    }

    /**
     * @brief Frees allocated memory of Mutex.
     */
    static void free(void* ptr)
    {
    }

    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP

};

} // namespace sys
} // namespace eoos

#endif // SYS_MUTEXALLOCATOR_HPP_
