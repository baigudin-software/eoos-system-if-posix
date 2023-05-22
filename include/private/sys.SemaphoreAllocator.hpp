/**
 * @file      sys.SemaphoreAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREALLOCATOR_HPP_
#define SYS_SEMAPHOREALLOCATOR_HPP_

#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class SemaphoreAllocator
 * @brief Semaphore memory allocator.
 */ 
class SemaphoreAllocator
{

public:

    /**
     * @brief Allocate memory for semaphore.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t size);

    /**
     * @brief Frees allocated memory of semaphore.
     */
    static void free(void* ptr);

};

} // namespace sys
} // namespace eoos

#endif // SYS_SEMAPHOREALLOCATOR_HPP_
