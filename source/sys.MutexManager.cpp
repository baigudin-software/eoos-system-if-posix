/**
 * @file      sys.MutexManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexManager.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* MutexManager::resource_( NULLPTR );

MutexManager::MutexManager() 
    : NonCopyable<NoAllocator>()
    , api::MutexManager()
    , pool_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

MutexManager::~MutexManager()
{
    MutexManager::deinitialize();
}

bool_t MutexManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::Mutex* MutexManager::create()
{
    api::Mutex* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Mutex> res( new Resource() );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {   ///< UT Justified Branch: OS dependency
                res.reset();
            }
        }
        ptr = res.release();
    }    
    return ptr;
}

bool_t MutexManager::construct()
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

void* MutexManager::allocate(size_t size)
{
    void* addr( NULLPTR );
    if( resource_ != NULLPTR )
    {
        addr = resource_->allocate(size, NULLPTR);
    }
    return addr;
}

void MutexManager::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t MutexManager::initialize(api::Heap* resource)
{
    bool_t res( false );
    if( resource_ == NULLPTR )
    {
        resource_ = resource;
        res = true;
    }
    return res;
}

void MutexManager::deinitialize()
{
    resource_ = NULLPTR;
}

MutexManager::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace sys
} // namespace eoos
