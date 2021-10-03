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
    Thread(api::Task& task, Scheduler* const scheduler) try : Parent(),
        task_          (&task),
        scheduler_     (scheduler){
        bool_t const isConstructed  { construct() };
        setConstructed( isConstructed );
    } catch (...) {
        setConstructed(false);
    }

    /**
     * @brief Destructor.
     */
    ~Thread() override
    {
        // @todo POSIX calls
        status_ = STATUS_DEAD;
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
    void execute() override try
    {
        if( isConstructed() && status_ == STATUS_NEW)
        {
            int32_t const exitCode = -7;
            // If the exitCode is 1, the specified thread was suspended but was restarted.
            if(exitCode == 1)
            {
                status_ = STATUS_RUNNABLE;
            }
            else
            {
                status_ = STATUS_DEAD;
            }
        }
    } catch (...) {
        status_ = STATUS_DEAD;
        return;
    }
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    void join() override try
    {
	    if( isConstructed() )
        {
            // @todo POSIX calls
        }
    } catch (...) {
        return;
    }

    /**
     * @copydoc eoos::api::Thread::getId()
     */
    int64_t getId() const override
    {
        return isConstructed() ? static_cast<int64_t>(id_) : ID_WRONG;
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
            // @todo POSIX calls
            res = false;
        } while(false);
        if( res == false )
        {
            status_ = STATUS_DEAD;
        }
        return res;    
    }

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
     * @brief Current identifier.
     */
    int32_t id_ {-7};

};

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
