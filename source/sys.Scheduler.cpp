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

bool_t Scheduler::yield()
{
    bool_t res( false );
    if( isConstructed() )
    {
        int_t const error( ::sched_yield() );
        if(error == 0)
        {
            res = true;
        }
    }
    return res;
}

bool_t Scheduler::construct()
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( pool_.memory.isConstructed() )
        {
            if( initialize(&pool_.memory) )
            {
                if( setThreadAffinity() )
                {
                    if( setThreadPolicy() )
                    {
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

bool_t Scheduler::setThreadAffinity()
{
    #ifdef EOOS_GLOBAL_SYS_SCHEDULER_THREAD_AFFINITY
    bool_t res( false );
    cpu_set_t set;
    CPU_ZERO(&set);
    uint_t cpu;
    int_t error( ::getcpu(&cpu, NULL) );
    if( error == 0 )
    {
        CPU_SET(cpu, &set);
        error = ::sched_setaffinity(0, sizeof(set), &set);
        if( error == 0 )
        {
            int_t const count( CPU_COUNT(&set) );
            if( count == 1 )
            {
                res = true;
            }
        }
    }
    return res;
    #else // !EOOS_GLOBAL_SYS_SCHEDULER_THREAD_AFFINITY
    return true;
    #endif // EOOS_GLOBAL_SYS_SCHEDULER_THREAD_AFFINITY
}

bool_t Scheduler::setThreadPolicy()
{
    #ifdef EOOS_GLOBAL_SYS_SCHEDULER_REALTIME
    const int_t POLICY( SCHED_RR );
    int_t min( ::sched_get_priority_min(POLICY) );
    int_t max( ::sched_get_priority_max(POLICY) );
    bool_t res( false );
    if( (min != -1) && (max != -1) )
    {
        int_t priority( (min + max) / 2 );
        ::sched_param param = { .sched_priority = priority };
        int_t pid( ::getpid() );
        int_t error( ::sched_setscheduler(pid, POLICY, &param) );
        if( error != -1 ) 
        {
            int_t const policy( ::sched_getscheduler(0) );
            if( policy == POLICY )
            {
                res = true;
            }
        }
    }
    return res;
    #else // !EOOS_GLOBAL_SYS_SCHEDULER_REALTIME
    return true;
    #endif // EOOS_GLOBAL_SYS_SCHEDULER_REALTIME
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
    void* addr( NULLPTR );
    if( resource_ != NULLPTR )
    {
        addr = resource_->allocate(size, NULLPTR);
    }
    return addr;
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
    bool_t res( false );
    if( resource_ == NULLPTR )
    {
        resource_ = resource;
        res = true;
    }
    return res;
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
