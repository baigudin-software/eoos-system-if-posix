/**
 * @file      sys.SemaphoreManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreManager.hpp"
#include "sys.SemaphoreAllocator.hpp"
#include "sys.Semaphore.hpp"
#include "lib.UniquePointer.hpp"


namespace eoos
{
namespace sys
{

SemaphoreManager::SemaphoreManager() 
    : NonCopyable<NoAllocator>()
    , api::SemaphoreManager() {
    setConstructed( true );
}

SemaphoreManager::~SemaphoreManager()
{
}

bool_t SemaphoreManager::isConstructed() const
{
    return Parent::isConstructed();
}    

api::Semaphore* SemaphoreManager::create(int32_t permits)
{
    api::Semaphore* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Semaphore> res( new Semaphore<SemaphoreAllocator>(permits) );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {
                res.reset();
            }
        }
        ptr = res.release();
    }    
    return ptr;
}

void SemaphoreManager::remove(api::Semaphore* semaphore)
{
    if( isConstructed() && semaphore != NULLPTR )
    {
        delete semaphore;
    }
}

} // namespace sys
} // namespace eoos
