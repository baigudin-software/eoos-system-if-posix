/**
 * @file      sys.Configuration.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_CONFIGURATION_HPP_
#define SYS_CONFIGURATION_HPP_

#include "Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @struct Configuration
 * @brief The configuration of a target processor.
 */
struct Configuration
{
    /** 
     * Constructor.
     */     
    Configuration();
    
    #ifdef EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Size of heap memory in bytes.
     */
    size_t heapSize;

    #endif // EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Stack size in bytes for the first user thread to be created.
     */
    size_t stackSize;

};

} // namespace sys
} // namespace eoos
#endif // SYS_CONFIGURATION_HPP_
