/**
 * @file      sys.MutexAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXALLOCATOR_HPP_
#define SYS_MUTEXALLOCATOR_HPP_

#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class MutexAllocator
 * @brief Mutex memory allocator.
 */ 
class MutexAllocator
{

public:

    /**
     * @brief Allocate memory for mutex.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t size);

    /**
     * @brief Frees allocated memory of Mutex.
     */
    static void free(void* ptr);

};

} // namespace sys
} // namespace eoos

#endif // SYS_MUTEXALLOCATOR_HPP_
