/**
 * @file      sys.Scheduler.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Scheduler.hpp"
#include "sys.ThreadAllocator.hpp"
#include "sys.Thread.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Scheduler
 * @brief Thread tasks scheduler class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Scheduler : public NonCopyable<A>, public api::Scheduler
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    Scheduler()
        : NonCopyable<A>()
        , api::Scheduler() {
    }


    /**
     * @brief Destructor.
     */
    virtual ~Scheduler()
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    virtual api::Thread* createThread(api::Task& task)
    {
        api::Thread* ptr( NULLPTR );
        if( isConstructed() )
        {
            lib::UniquePointer<api::Thread> res( new Thread<ThreadAllocator>(task) );
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
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    virtual bool_t sleep(int32_t ms)
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

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    virtual void yield()
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

protected:

    using Parent::setConstructed;    

private:

    /**
     * @brief Causes current thread to sleep in seconds.
     *
     * @param s A time to sleep in seconds.
     */
    static void sSleep(int32_t const s)
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
    static bool_t msSleep(int32_t const ms)
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

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
