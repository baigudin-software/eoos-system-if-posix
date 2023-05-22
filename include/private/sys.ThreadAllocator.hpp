/**
 * @file      sys.ThreadAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREADALLOCATOR_HPP_
#define SYS_THREADALLOCATOR_HPP_

#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class ThreadAllocator
 * @brief Thread memory allocator.
 */ 
class ThreadAllocator
{

public:

    /**
     * @brief Allocate memory for thread.
     *
     * @return The null pointer.
     */
    static void* allocate(size_t size);

    /**
     * @brief Frees allocated memory of thread.
     */
    static void free(void* ptr);

};

} // namespace sys
} // namespace eoos

#endif // SYS_THREADALLOCATOR_HPP_
