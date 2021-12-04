/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "sys.Scheduler.hpp"
#include "lib.Semaphore.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Thread
 * @brief Thread class.
 */
class Thread : public NonCopyable, public api::Thread
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task      A task interface whose main method is invoked when this thread is started.
     * @param scheduler A scheduler controls this thread.
     */
    Thread(api::Task& task, Scheduler* const scheduler) : Parent(),
        task_          (&task),
        scheduler_     (scheduler){
        bool_t const isConstructed  { construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Thread() override
    {
        status_ = STATUS_DEAD;        
        if( not isJoined_ )
        {
            ::pthread_cancel(thread_);
        }
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    void execute() override
    {
        if( isConstructed() && status_ == STATUS_NEW)
        {
            status_ = STATUS_RUNNABLE;
            sem_.release();
        }
    }
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    bool_t join() override
    {
        if( isConstructed() )
        {
            // Initiate joining
            isJoining_ = true;
            // Release even if it is released by Execute function
            sem_.release();
            // Do the kernel syscall
            int const error {::pthread_join(thread_, NULL)};
            isJoined_ = (error == 0) ? true : false;
        }
        return isJoined_;

    }

    /**
     * @copydoc eoos::api::Thread::getStatus()
     */
    Status getStatus() const override
    {
        return status_;
    }    

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    int32_t getPriority() const override
    {
        return isConstructed() ? priority_ : PRIORITY_WRONG;        
    }

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    bool_t setPriority(int32_t priority) override
    {
        bool_t res { false };
        if( isConstructed() )
        {
            if( (PRIORITY_MIN <= priority) && (priority <= PRIORITY_MAX) )
            {
                priority_ = priority;
                res = true;
            }
            else if (priority == PRIORITY_LOCK)
            {
                priority_ = priority;
                res = true;
            }
            else 
            {
                res = false;
            }
        }
        // @todo Implemet setting priority on system level regarding common API rage
        return res;
    }
    
    /**
     * @copydoc eoos::api::Thread::getExecutionError()
     */
    int32_t getExecutionError() const override
    {
        return error_;
    }    

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {  
        bool_t res {false};
        do
        {
            if( not isConstructed() )
            {
                break;
            }
            if( task_ == NULLPTR || scheduler_ == NULLPTR )
            {
                break;
            }
            if( not task_->isConstructed() || not scheduler_->isConstructed() )
            {
                break;
            }
            if( not sem_.isConstructed() )
            {
                break;
            }
            int const error = ::pthread_create(&thread_, NULL, start, &this_);
            if(error != 0)
            {
                break;
            }
            res = true;
        } while(false);
        if( res == false )
        {
            status_ = STATUS_DEAD;
        }
        return res;    
    }
    
    /**
     * @brief Runs a start function of the task interface.
     *
     * @return zero, or error code if an error has been occurred.
     */
    int32_t run()
    {
        // Wait for calling Execute function
        bool const isAcquired {sem_.acquire()};
        // Start user main function
        if( isAcquired && not isJoining_ )
        {
            error_ = task_->start();
        }
        status_ = STATUS_DEAD;
        return error_;
    }

    /**
     * @brief Starts a thread routine.
     *
     * @param argument Pointer to arguments passed by the POSIX pthread_create function.
     */
    static void* start(void* argument)
    {
        void* const retptr {NULLPTR};
        if(argument == NULLPTR) 
        {
            return retptr;
        }
        Thread* const thread { *reinterpret_cast<Thread**>(argument) };
        if(thread == NULLPTR || not thread->isConstructed() )
        {
            return retptr;
        }
        int oldtype;
        int error {::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldtype)};
        if(error != 0)
        {
            return retptr;
        }
        error = ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        if(error != 0)
        {
            return retptr;
        }
        // Invoke the member function through the pointer
        // @todo Check the return value
        thread->run();
        return retptr;
    }    
    
    /**
     * @brief The semaphore to start user thread.
     */
    lib::Semaphore<> sem_ {0};    

    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_ {NULLPTR};

    /**
     * @brief The scheduler resource.
     */
    Scheduler* scheduler_ {NULLPTR};

    /**
     * @brief Current status.
     */
    Status status_ {STATUS_NEW};
    
    /**
     * @brief This thread priority.
     */    
    int32_t priority_ {PRIORITY_NORM};    
    
    /**
     * @brief Error of the thread task execution.
     */    
    int32_t error_ {-1};

    /**
     * @brief This class pointer.
     */
    Thread* this_ {this};

    /**
     * @brief Waiting for this thread to die is initiated.
     */
    bool isJoining_ {false};

    /**
     * @brief This thread is dead.
     */
    bool isJoined_ {false};
    
    /**
     * @brief The new thread resource identifier.
     */
    ::pthread_t thread_ {0};    

};

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
