/**
 * @file      sys.ThreadAllocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREADALLOCATOR_HPP_
#define SYS_THREADALLOCATOR_HPP_

#include "sys.Thread.hpp"
#include "lib.Allocator.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class ThreadAllocator
 * @brief Thread memory allocator.
 */ 
class ThreadAllocator : public lib::Allocator
{

public:

};

} // namespace sys
} // namespace eoos

#endif // SYS_THREADALLOCATOR_HPP_
