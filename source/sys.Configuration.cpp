/**
 * @file      sys.Configuration.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.Configuration.hpp"

namespace eoos
{
namespace sys
{

Configuration::Configuration()
    : heapSize  (0x00000000U)
    , stackSize (0x00000000U) {
}

} // namespace sys
} // namespace eoos
