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
 * @class Configuration
 * @brief The configuration of a target processor.
 */
struct Configuration
{

public:

    /** 
     * Constructor.
     */     
    Configuration()
        : heapSize_( 0x00000000U )
        , stackSize_( 0x00000000U ){
    }

    #ifdef EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Returns size of heap memory in bytes.
     */
    size_t getHeapSize() const
    { 
        return heapSize_;
    }

    #endif // EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Stack size in bytes for the first user thread to be created.
     */
    size_t getStackSize() const
    {
        return stackSize_;
    }
    
private:
    
    #ifdef EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Size of heap memory in bytes.
     */
    size_t heapSize_;

    #endif // EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Stack size in bytes for the first user thread to be created.
     */
    size_t stackSize_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_CONFIGURATION_HPP_
