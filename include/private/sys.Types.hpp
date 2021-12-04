/**
 * @file      sys.Types.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 * 
 * @brief System type definitions.
 */
#ifndef SYS_TYPES_HPP_
#define SYS_TYPES_HPP_

#include <new>

#include "sys.Posix.hpp"
#include "lib.Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Empty class type used to disambiguate the overloads of throwing and non-throwing allocation.
 */
struct nothrow_t 
{ 
    explicit nothrow_t() = default; 
};

/**
 * @brief Constant of type lib::nothrow_t used to disambiguate the overloads of throwing and non-throwing allocation functions.
 */
const ::std::nothrow_t nothrow { ::std::nothrow };

} // namespace sys
} // namespace eoos
#endif // SYS_TYPES_HPP_
