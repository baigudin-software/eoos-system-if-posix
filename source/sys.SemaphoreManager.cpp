/**
 * @file      sys.SemaphoreManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* SemaphoreManager::resource_( NULLPTR );

SemaphoreManager::SemaphoreManager()
    : NonCopyable<NoAllocator>()
    , api::SemaphoreManager()
    , pool_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

SemaphoreManager::~SemaphoreManager()
{
    SemaphoreManager::deinitialize();
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
        lib::UniquePointer<api::Semaphore> res( new Resource(permits) );
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

bool_t SemaphoreManager::construct()
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( pool_.memory.isConstructed() )
        {
            if( initialize(&pool_.memory) )
            {
                res = true;
            }
        }
    }
    return res;
}

void* SemaphoreManager::allocate(size_t size)
{
    void* addr( NULLPTR );
    if( resource_ != NULLPTR )
    {
        addr = resource_->allocate(size, NULLPTR);
    }
    return addr;
}

void SemaphoreManager::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t SemaphoreManager::initialize(api::Heap* resource)
{
    bool_t res( true );
    if( resource_ == NULLPTR )
    {
        resource_ = resource;
        res = true;
    }
    return res;
}

void SemaphoreManager::deinitialize()
{
    resource_ = NULLPTR;
}

SemaphoreManager::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace sys
} // namespace eoos
