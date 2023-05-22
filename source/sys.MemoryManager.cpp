/**
 * @file      sys.MemoryManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MemoryManager.hpp"

namespace eoos
{
namespace sys
{

MemoryManager::MemoryManager() 
    : NonCopyable<NoAllocator>()
    , mutexMemory_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

MemoryManager::~MemoryManager()
{
}

bool_t MemoryManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::Heap& MemoryManager::getMutexMemory()
{
    return mutexMemory_;
}

api::Heap& MemoryManager::getSemaphoreMemory()
{
    return semaphoreMemory_;
}

api::Heap& MemoryManager::getThreadMemory()
{
    return threadMemory_;
}

bool_t MemoryManager::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !mutexMemory_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !semaphoreMemory_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        res = true;
    } while(false);    
    return res;
}

} // namespace sys
} // namespace eoos
