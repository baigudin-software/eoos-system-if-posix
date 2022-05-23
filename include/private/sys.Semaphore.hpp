/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2022, Sergey Baigudin, Baigudin Software
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
 */
class Semaphore : public NonCopyable, public api::Semaphore
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits) 
        : NonCopyable()
        , api::Semaphore()
        , isFair_(false)
        , permits_(permits)
        , sem_(NULLPTR){
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
            int_t const error( ::sem_wait(sem_) );
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
            {
                setConstructed(false);
            }
        }
    }

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct() try
    {
        bool_t res( false );
        do {
            if( !isConstructed() )
            {
                break;
            }
            sem_ = new ::sem_t;
            if(sem_ == NULLPTR)
            {
                break;
            }
            int_t const error( ::sem_init(sem_, 0, static_cast<uint_t >(permits_)) );
            if(error != 0)
            {
                break;
            }
			isFair_ = isFair();
            res = true;
        } while(false);
        return res;
    } catch (...) {
        return false;
    }
    
    /**
     * @brief Destructs this object.
     */
    void destruct() const
    {
        if(sem_ != NULLPTR)
        {
            static_cast<void>( ::sem_destroy(sem_) );
            delete sem_;
        }
    }

    /**
     * @brief Test if semaphore is fair.
     *
     * @return Fairness flag.
     */
    static bool_t isFair()
    {
        int_t const priority( ::sched_getscheduler(0) );
        return ( (priority == SCHED_FIFO) || (priority == SCHED_RR) ) ? true : false;
    }

    /**
     * @brief Releases one permit.
     *
     * @return True on success.
     */
    bool_t post() const
    {
        bool_t res( true );
        int_t const error( ::sem_post(sem_) );
        if (error != 0)
        {
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
     *
     * @todo Implement it as `sem_t`
     */
    sem_t* sem_;    

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
