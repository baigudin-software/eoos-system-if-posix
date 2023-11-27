/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::Heap* Scheduler::resource_( NULLPTR );

Scheduler::Scheduler()
    : NonCopyable<NoAllocator>()
    , api::Scheduler()
    , pool_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );    
}

Scheduler::~Scheduler()
{
    Scheduler::deinitialize();
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task)
{
    api::Thread* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Thread> res( new Resource(task) );
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

bool_t Scheduler::sleep(int32_t ms)
{
    bool_t res( false );
    if( isConstructed() )
    {
        int32_t time( ms / 1000 );
        sSleep(time);
        time = ms % 1000;
        res = msSleep(time);
    }
    return res;
}

void Scheduler::yield()
{
    if( isConstructed() )
    {
        int_t const error( ::sched_yield() );
        if(error != 0)
        {   ///< UT Justified Branch: OS dependency
            setConstructed(false);
        }
    }
}

bool_t Scheduler::construct()
{
    bool_t res( false );
    do 
    {
        if( !isConstructed() )
        {
            break;
        }
        if( !pool_.memory.isConstructed() )
        {
            break;
        }
        if( !Scheduler::initialize(&pool_.memory) )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

void Scheduler::sSleep(int32_t const s)
{
    uint_t sec( static_cast<uint_t>(s) );
    while(sec != 0U)
    {
        sec = ::sleep(sec);
    }
}    

bool_t Scheduler::msSleep(int32_t const ms)
{
    bool_t res( false );
    if( (0 < ms) && (ms < 1000) )
    {
        ::useconds_t const us( static_cast< ::useconds_t >(ms) * 1000U );
        int_t const error( ::usleep(us) );
        if(error == 0)
        {
            res = true;
        }
    }
    return res;
}

void* Scheduler::allocate(size_t size)
{
    if( resource_ != NULLPTR )
    {
        return resource_->allocate(size, NULLPTR);
    }
    else
    {
        return NULLPTR;
    }
}

void Scheduler::free(void* ptr)
{
    if( resource_ != NULLPTR )
    {
        resource_->free(ptr);
    }
}

bool_t Scheduler::initialize(api::Heap* resource)
{
    if( resource_ == NULLPTR )
    {
        resource_ = resource;
        return true;
    }
    else
    {
        return false;
    }

}

void Scheduler::deinitialize()
{
    resource_ = NULLPTR;
}

Scheduler::ResourcePool::ResourcePool()
    : mutex_()
    , memory( mutex_ ) {
}

} // namespace sys
} // namespace eoos
