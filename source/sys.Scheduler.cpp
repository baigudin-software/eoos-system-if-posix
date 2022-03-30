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
 * @brief Suspends the execution of the calling thread
 *
 * @param rem   Time remained to sleep is in and out param
 * @return See NANOSLEEP(2)
 */
int nanosleep(::timespec* const rem)
{
    ::timespec const req {*rem};
    return ::nanosleep(&req, rem);
}

} // namespace

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task)
{
    api::Thread* thread {NULLPTR};
    if( isConstructed() )
    {
        thread = new Thread {task};
    }
    return thread;
}

void Scheduler::sleep(int64_t millis, int32_t nanos)
{
    if( isConstructed() )
    {
        bool_t hasToSleep {false};
        ::timespec rem {millis * 1000, nanos};
        do {
            int const error { nanosleep(&rem) };
            if(error == 0) 
            {
                hasToSleep = false;
                break;
            }
            else if(error == -1)
            {
                int errsv = errno;
                switch( errsv )
                {
                    // Problem with copying information from user space.
                    case EFAULT:
                    {
                        hasToSleep = false;
                        break;
                    }
                    // The pause has been interrupted by a signal that was delivered to the thread.
                    case EINTR:
                    {
                        hasToSleep = true;                
                        break;
                    }        
                    // The value in the tv_nsec field was not in the range 0 to 999999999 or tv_sec was negative.
                    case EINVAL:
                    {
                        hasToSleep = false;
                        break;
                    }
                    default:
                    {
                        setConstructed(false);
                        hasToSleep = false;
                        break;
                    }
                }
            }
            else
            {
                setConstructed(false);
                hasToSleep = false;
            }
        } while(hasToSleep);
    }
}

void Scheduler::yield()
{
    if( isConstructed() )
    {
        // @todo Use  sched_yield() as standardized function.
        int const error = ::pthread_yield();
        if(error != 0)
        {
            setConstructed(false);
        }
    }
}

} // namespace sys
} // namespace eoos
