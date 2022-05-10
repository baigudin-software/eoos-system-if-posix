/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.Thread.hpp"
#include <pthread.h>
#include <sys/types.h>

namespace eoos
{
namespace sys
{
    
namespace
{

/**
 * @brief Causes current thread to sleep in seconds.
 *
 * @param s A time to sleep in seconds.
 */
void sSleep(int32_t const s)
{
    uint_t sec( static_cast<uint_t>(s) );
    while(sec != 0U)
    {
        sec = ::sleep(sec);
    }
}    

/**
 * @brief Causes current thread to sleep in milliseconds.
 *
 * @param ms A time to sleep in milliseconds.
 * @return true if no system errors occured.
 */
bool_t msSleep(int32_t const ms)
{
    bool_t res(false);
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

} // namespace

Scheduler::Scheduler() 
{
}

Scheduler::~Scheduler()
{
}
    
bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task)
{
    api::Thread* thread(NULLPTR);
    if( isConstructed() )
    {
        thread = new Thread(task);
    }
    return thread;
}

bool_t Scheduler::sleep(int32_t ms)
{
    bool_t res(false);
    if( isConstructed() )
    {
        int32_t time = ms / 1000;
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
        {
            setConstructed(false);
        }
    }
}

} // namespace sys
} // namespace eoos
