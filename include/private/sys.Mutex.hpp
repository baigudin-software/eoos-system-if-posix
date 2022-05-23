/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2022, Sergey Baigudin, Baigudin Software
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
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    Mutex() 
        : NonCopyable()
        , api::Mutex()
        , mutex_( NULLPTR ) {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~Mutex()
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
     * @copydoc eoos::api::Mutex::tryLock()
     */
    virtual bool_t tryLock()
    {
        bool_t res( false );
        if( isConstructed() )
        {
            int_t const error( ::pthread_mutex_trylock(mutex_) );
            res = (error == 0) ? true : false;
        }
        return res;
    }    

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    virtual bool_t lock()
    {
        bool_t res( false );
        if( isConstructed() )
        {
            int_t const error( ::pthread_mutex_lock(mutex_) );
            res = (error == 0) ? true : false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    virtual void unlock()
    {
        if( isConstructed() )
        {
            int_t const error( ::pthread_mutex_unlock(mutex_) );
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
    bool_t construct() try
    {
        bool_t res( false );
        do
        {   
            if( !isConstructed() )
            {
                break;
            }
            // @todo Revise possobility to avoud memory allocation here.
            mutex_ = new ::pthread_mutex_t;
            if(mutex_ == NULLPTR)
            {
                break;
            }
            int_t const error( ::pthread_mutex_init(mutex_, NULL) );
            if(error != 0)
            {
                break;
            }
            res = true;
        } while(false);
        return res;
    } catch(...) {
        return false;
    }
    
    /**
     * @brief Destructs this object.
     */
    void destruct() const
    {
        if(mutex_ != NULLPTR)
        {
            static_cast<void>( ::pthread_mutex_destroy(mutex_) );
            delete mutex_;
        }        
    }

    /**
     * @brief Mutex resource identifier.
     */
    pthread_mutex_t* mutex_;    
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
