/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
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
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Thread : public NonCopyable<A>, public api::Thread
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task A task interface whose main method is invoked when this thread is started.
     */
    Thread(api::Task& task);

    /**
     * @brief Destructor.
     */
    virtual ~Thread();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Thread::execute()
     */
    virtual bool_t execute();
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    virtual bool_t join();

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    virtual int32_t getPriority() const;

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    virtual bool_t setPriority(int32_t priority);

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Starts a thread routine.
     *
     * @param argument Pointer to arguments passed by the POSIX pthread_create function.
     */
    static void* start(void* argument);

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
        PthreadAttr();
        
        /**
         * @brief Destructor.
         */        
        ~PthreadAttr();

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

template <class A>
Thread<A>::Thread(api::Task& task) 
    : NonCopyable<A>()
    , api::Thread()
    , task_ (&task)
    , status_ (STATUS_NEW)
    , priority_ (PRIORITY_NORM)
    , thread_ (0) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Thread<A>::~Thread()
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

template <class A>
bool_t Thread<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t Thread<A>::execute()
{
    bool_t res( false );
    if( isConstructed() && (status_ == STATUS_NEW) )
    {
        int_t error( 0 );
        PthreadAttr pthreadAttr; ///< SCA MISRA-C++:2008 Justified Rule 9-5-1
        size_t const stackSize( task_->getStackSize() );
        if(stackSize != 0U)
        {
            error = ::pthread_attr_setstacksize(&pthreadAttr.attr, stackSize);
        }
        if(error == 0)
        {
            error = ::pthread_create(&thread_, &pthreadAttr.attr, &start, &task_);
            if(error == 0)
            {            
                status_ = STATUS_RUNNABLE;
                res = true;
            }
        }
    }
    return res;        
}

template <class A>
bool_t Thread<A>::join()
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

template <class A>
int32_t Thread<A>::getPriority() const
{
    return isConstructed() ? priority_ : PRIORITY_WRONG;        
}

template <class A>
bool_t Thread<A>::setPriority(int32_t priority)
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( (PRIORITY_MIN <= priority) && (priority <= PRIORITY_MAX) )
        {
            priority_ = priority;
            res = true;
        }
        else if (priority == PRIORITY_IDLE)
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

template <class A>
bool_t Thread<A>::construct()
{
    bool_t res( false );
    if( isConstructed() && Parent::isConstructed(task_) )
    {
        status_ = STATUS_NEW;
        res = true;
    }
    else
    {
        status_ = STATUS_DEAD;
    }
    return res;    
}

template <class A>
void* Thread<A>::start(void* argument)
{
    if(argument != NULLPTR) 
    {
        api::Task** addr( reinterpret_cast<api::Task**>(argument) );
        if( addr != NULLPTR )
        {
            api::Task* const task( *addr ); ///< SCA MISRA-C++:2008 Justified Rule 5-2-8
            if( Parent::isConstructed(task) )
            {
                int_t oldtype;
                // The thread is cancelable.  This is the default
                // cancelability state in all new threads, including the
                // initial thread.  The thread's cancelability type
                // determines when a cancelable thread will respond to a
                // cancellation request.
                int_t error( ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldtype) );
                if(error == 0)
                {
                    // The thread can be canceled at any time. Typically, it
                    // will be canceled immediately upon receiving a cancellation
                    // request, but the system doesn't guarantee this.
                    error = ::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
                    if(error == 0)
                    {
                        task->start();
                    }
                }
            }
        }
    }
    return NULLPTR;
}

template <class A>
Thread<A>::PthreadAttr::PthreadAttr()
{
    static_cast<void>( ::pthread_attr_init(&attr) );
}

template <class A>
Thread<A>::PthreadAttr::~PthreadAttr()
{
    static_cast<void>( ::pthread_attr_destroy(&attr) );
}

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
