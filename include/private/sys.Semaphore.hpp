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
template <class A = Allocator>
class Semaphore : public NonCopyable<A>, public api::Semaphore
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits) 
        : NonCopyable<A>()
        , api::Semaphore()
        , isFair_(false)
        , permits_(permits)
        , sem_(){
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~Semaphore()
    {
        destruct();
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    virtual bool_t acquire()
    {
        bool_t res( false );
        if( isConstructed() )
        {
            int_t const error( ::sem_wait(&sem_) );
            if(error == 0) 
            { 
                res = true; 
            }
        }
        return res;
    }

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    virtual void release()
    {
        if( isConstructed() )
        {
            bool_t const isPosted( post() );
            if ( !isPosted )
            {   ///< UT Justified Branch: OS dependency
                setConstructed(false);
            }
        }
    }

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res( false );
        do {
            if( !isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            int_t const error( ::sem_init(&sem_, 0, static_cast<uint_t >(permits_)) );
            if(error != 0)
            {
                break;
            }
            isFair_ = isFair();
            res = true;
        } while(false);
        return res;
    }
    
    /**
     * @brief Destructs this object.
     */
    void destruct()
    {
        static_cast<void>( ::sem_destroy(&sem_) );
    }

    /**
     * @brief Test if semaphore is fair.
     *
     * @return Fairness flag.
     */
    static bool_t isFair()
    {
        int_t const priority( ::sched_getscheduler(0) );
        return ( (priority == SCHED_FIFO) || (priority == SCHED_RR) ) ? true : false;  ///< SCA MISRA-C++:2008 Justified Rule 16-2-2
    }

    /**
     * @brief Releases one permit.
     *
     * @return True on success.
     */
    bool_t post()
    {
        bool_t res( true );
        int_t const error( ::sem_post(&sem_) );
        if (error != 0)
        {   ///< UT Justified Branch: OS dependency
            res = false;
        }
        return res;
    }

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
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
