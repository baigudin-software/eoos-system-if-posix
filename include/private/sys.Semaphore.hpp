/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Semaphore.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Semaphore
 * @brief Semaphore class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Semaphore : public NonCopyable<A>, public api::Semaphore
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits);

    /**
     * @brief Destructor.
     */
    virtual ~Semaphore();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    virtual bool_t acquire();

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    virtual bool_t release();

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes kernel semaphore resource.
     * 
     * @return True if initialized sucessfully. 
     */
    bool_t initialize();

    /**
     * @brief Deinitializes kernel semaphore resource.
     */
    void deinitialize();

    /**
     * @brief Test if semaphore is fair.
     *
     * @return Fairness flag.
     */
    static bool_t isFair();

    /**
     * @brief Fairness flag.
     */
    bool_t isFair_;
    
    /**
     * @brief Number of permits available.
     */
    int32_t permits_;

    /**
     * @brief Semaphore resource identifier.
     */
    ::sem_t sem_;    

};

template <class A>
Semaphore<A>::Semaphore(int32_t permits) 
    : NonCopyable<A>()
    , api::Semaphore()
    , isFair_(false)
    , permits_(permits)
    , sem_(){
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Semaphore<A>::~Semaphore()
{
    deinitialize();
}

template <class A>
bool_t Semaphore<A>::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
{
    return Parent::isConstructed();
}

template <class A>
bool_t Semaphore<A>::acquire()
{
    bool_t res( false );
    if( isConstructed() )
    {
        int_t const error( ::sem_wait(&sem_) );
        if( error == 0 ) 
        { 
            res = true; 
        }
    }
    return res;
}

template <class A>
bool_t Semaphore<A>::release()
{
    bool_t res( false );
    if( isConstructed() )
    {
        int_t const error( ::sem_post(&sem_) );
        if( error == 0 )
        {
            res = true; 
        }
    }
    return res;
}

template <class A>
bool_t Semaphore<A>::construct()
{
    bool_t res( false );
    if( isConstructed() )
    {
        if( initialize() )
        {
            isFair_ = isFair();
            res = true;
        }
    }
    return res;
}

template <class A>
bool_t Semaphore<A>::initialize()
{
    int_t const error( ::sem_init(&sem_, 0, static_cast<uint_t >(permits_)) );
    return error == 0;
}

template <class A>
void Semaphore<A>::deinitialize()
{
    static_cast<void>( ::sem_destroy(&sem_) );
}


template <class A>
bool_t Semaphore<A>::isFair()
{
    int_t const priority( ::sched_getscheduler(0) );
    return ( (priority == SCHED_FIFO) || (priority == SCHED_RR) ) ? true : false;  ///< SCA MISRA-C++:2008 Justified Rule 16-2-2
}

} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
