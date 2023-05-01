/**
 * @file      sys.Allocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_ALLOCATOR_HPP_
#define SYS_ALLOCATOR_HPP_

#include "lib.Allocator.hpp"
#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class Allocator
 * @brief Memory allocator.
 */ 
class Allocator : public lib::Allocator
{
};

} // namespace sys
} // namespace eoos

#endif // SYS_ALLOCATOR_HPP_
