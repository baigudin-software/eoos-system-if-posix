/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
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
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task A task interface whose main method is invoked when this thread is started.
     */
    Thread(api::Task& task) 
        : NonCopyable()
        , api::Thread()
        , task_ (&task)
        , status_ (STATUS_NEW)
        , priority_ (PRIORITY_NORM)
        , thread_ (0) {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~Thread()
    {
        if( thread_ != 0U )
        {
            // @todo The thread detaching means the thread will still be executed by OS.
            // Thus, to keep compatibility, common approach for all OSs shall be found
            // for using pthread_cancel function to cancel the thread execution forcely.
            static_cast<void>( ::pthread_detach(thread_) );
            status_ = STATUS_DEAD;            
        }
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    virtual bool_t execute()
    {
        bool_t res( false );
        do{
            if( !isConstructed() )
            {
                break;
            }
            if( status_ != STATUS_NEW )
            {
                break;
            }
            int_t error( 0 );
            PthreadAttr pthreadAttr; ///< SCA MISRA-C++:2008 Justified Rule 9-5-1
            size_t const stackSize( task_->getStackSize() );
            if(stackSize != 0U)
            {
                error = ::pthread_attr_setstacksize(&pthreadAttr.attr, stackSize);
                if(error != 0)
                {   ///< UT Justified Branch: OS dependency
                    break;
                }
            }
            error = ::pthread_create(&thread_, &pthreadAttr.attr, &start, &task_);
            if(error != 0)
            {   ///< UT Justified Branch: OS dependency
                break;
            }
            status_ = STATUS_RUNNABLE;
            res = true;
        } while(false);
        return res;        
    }
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    virtual bool_t join()
    {
        bool_t res( false );    
        if( isConstructed() && (status_ == STATUS_RUNNABLE) )
        {
            int_t const error( ::pthread_join(thread_, NULL) );
            res = (error == 0) ? true : false;
            status_ = STATUS_DEAD;
        }
        return res;

    }

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    virtual int32_t getPriority() const
    {
        return isConstructed() ? priority_ : PRIORITY_WRONG;        
    }

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    virtual bool_t setPriority(int32_t priority)
    {
        bool_t res( false );
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

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {  
        bool_t res( false );
        do
        {
            if( !isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            if( task_ == NULLPTR )
            {   ///< UT Justified Branch: SW dependency
                break;
            }
            if( !task_->isConstructed() )
            {
                break;
            }
            status_ = STATUS_NEW;
            res = true;
        } while(false);
        if( res == false )
        {
            status_ = STATUS_DEAD;
        }
        return res;    
    }

    /**
     * @brief Starts a thread routine.
     *
     * @param argument Pointer to arguments passed by the POSIX pthread_create function.
     */
    static void* start(void* argument)
    {
        if(argument == NULLPTR) 
        {   ///< UT Justified Branch: SW dependency
            return NULLPTR;
        }
        api::Task* const task( *reinterpret_cast<api::Task**>(argument) ); ///< SCA MISRA-C++:2008 Justified Rule 5-2-8
        if(task == NULLPTR)
        {   ///< UT Justified Branch: HW dependency
            return NULLPTR;
        }
        if( !task->isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            return NULLPTR;
        }        
        int_t oldtype;
        // The thread is cancelable.  This is the default
        // cancelability state in all new threads, including the
        // initial thread.  The thread's cancelability type
        // determines when a cancelable thread will respond to a
        // cancellation request.
        int_t error( ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldtype) );
        if(error != 0)
        {   ///< UT Justified Branch: OS dependency
            return NULLPTR;
        }
        // The thread can be canceled at any time. Typically, it
        // will be canceled immediately upon receiving a cancellation
        // request, but the system doesn't guarantee this.
        error = ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
        if(error != 0)
        {   ///< UT Justified Branch: OS dependency
            return NULLPTR;
        }
        task->start();
        return NULLPTR;
    }

    /**
     * @struct The pthread attr container for the pthread_create function
     * @brief The struct implements RAII approach on pthread_attr_t.
     */
    struct PthreadAttr
    {
        /**
         * @brief Attributes of the pthread_create function.
         */
        ::pthread_attr_t attr; ///< SCA MISRA-C++:2008 Justified Rule 9-5-1 and Rule 11-0-1
        
        /**
         * @brief Constructor of not constructed object.
         */        
        PthreadAttr()
        {
            static_cast<void>( ::pthread_attr_init(&attr) );
        }
        
        /**
         * @brief Destructor.
         */        
        ~PthreadAttr()
        {
            static_cast<void>( ::pthread_attr_destroy(&attr) );
        }        
    };    
    
    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_;

    /**
     * @brief Current status.
     */
    Status status_;
    
    /**
     * @brief This thread priority.
     */    
    int32_t priority_;    
    
    /**
     * @brief The new thread resource identifier.
     */
    ::pthread_t thread_;    

};

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
