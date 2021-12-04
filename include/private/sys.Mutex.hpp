/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Mutex.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Mutex.
 * @brief Mutex class.
 */
class Mutex : public NonCopyable, public api::Mutex
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Mutex() : Parent()
    {
        bool_t const isConstructed { construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Mutex() override
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
     * @copydoc eoos::api::Mutex::tryLock()
     */
    bool_t tryLock() override
    {
        bool_t res {false};
        if( isConstructed() )
        {
            int const error = ::pthread_mutex_trylock(mutex_);
            res = (error == 0) ? true : false;
        }
        return res;
    }    

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    bool_t lock() override
    {
        bool_t res {false};
        if( isConstructed() )
        {
            int const error = ::pthread_mutex_lock(mutex_);
            res = (error == 0) ? true : false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    void unlock() override
    {
        if( isConstructed() )
        {
            int const error { ::pthread_mutex_unlock(mutex_) };
            if (error != 0)
            {
                setConstructed(false);
            }
        }
    }

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res { false };
        do
        {   
            if( not isConstructed() )
            {
                break;
            }
            mutex_ = new (nothrow) ::pthread_mutex_t;
            if(mutex_ == NULLPTR)
            {
                break;
            }
            int const error { ::pthread_mutex_init(mutex_, NULL) };
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
        if(mutex_ != nullptr)
        {
            ::pthread_mutex_destroy(mutex_);
            delete mutex_;
        }        
    }

    /**
     * @brief Mutex resource identifier.
     */
    pthread_mutex_t* mutex_ {NULLPTR};    
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
