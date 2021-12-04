/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
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
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    Semaphore(int32_t permits) : Parent(),
        permits_ (permits){
        bool_t const isConstructed { construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Semaphore() override
    {
        destruct();
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    bool_t acquire() override
    {
        bool_t res {false};
        if( isConstructed() )
        {
            int const error { ::sem_wait(sem_) };
            if(error == 0) 
            { 
                res = true; 
            }
        }
        return res;
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire(int32_t)
     */
    bool_t acquire(int32_t permits) override
    {
        // @todo Implement through calling acquire() permits times under a mutex,
        //       or investigate POSIX possobility to do so.
        return false;
    }

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    void release() override
    {
        if( isConstructed() )
        {
            bool_t const isPosted { post() };
            if ( not isPosted )
            {
                setConstructed(false);
            }
        }
    }

    /**
     * @copydoc eoos::api::Semaphore::release(int32_t)
     */
    void release(int32_t permits) override
    {
        // @todo Implement through calling post() permits times under a mutex,
        //       or investigate POSIX possobility to do so.
    }

    /**
     * @copydoc eoos::api::Semaphore::isFair()
     */
    bool_t isFair() const override
    {
        int const priority {::sched_getscheduler(0)};
        return ( priority == SCHED_FIFO || priority == SCHED_RR) ? true : false;
    }

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res {false};
        do {
            if( not isConstructed() )
            {
                break;
            }
            sem_ = new (nothrow) ::sem_t;
            if(sem_ == NULLPTR)
            {
                break;
            }
            int const error {::sem_init(sem_, 0, static_cast<unsigned int>(permits_))};
            if(error != 0)
            {
                break;
            }
            res = true;
        } while(false);
        return res;
    }
    
    /**
     * @brief Destructs this object.
     */
    void destruct()
    {
        if(sem_ != NULLPTR)
        {
            ::sem_destroy(sem_);
            delete sem_;
        }
    }
    
    /**
     * @brief Releases one permit.
     *
     * @return True on success.
     */
    bool_t post()
    {
        bool_t res{true};
        int const error {::sem_post(sem_)};
        if (error != 0)
        {
            res = false;
        }
        return res;
    }    
    
    /**
     * @brief Number of permits available.
     */
    int32_t permits_ {0};

    /**
     * @brief Semaphore resource identifier.
     *
     * @todo Implement it as `sem_t`
     */
    sem_t* sem_ {NULLPTR};    

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
