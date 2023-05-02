/**
 * @file      sys.SemaphoreAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREALLOCATOR_HPP_
#define SYS_SEMAPHOREALLOCATOR_HPP_

#include "sys.Semaphore.hpp"
#include "lib.Allocator.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class SemaphoreAllocator
 * @brief Semaphore memory allocator.
 */ 
class SemaphoreAllocator : public lib::Allocator
{

public:

};

} // namespace sys
} // namespace eoos

#endif // SYS_SEMAPHOREALLOCATOR_HPP_
