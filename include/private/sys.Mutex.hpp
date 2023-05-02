/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2023, Sergey Baigudin, Baigudin Software
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
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Mutex : public NonCopyable<A>, public api::Mutex
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    Mutex() 
        : NonCopyable<A>()
        , api::Mutex()
        , mutex_()
        , id_(-1) {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~Mutex()
    {
        static_cast<void>( deinitialize() );
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Resource::getId()
     */
    virtual int32_t getId() const
    {
        return id_;
    }    
    
    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    virtual bool_t tryLock()
    {
        bool_t res( false );
        if( isConstructed() )
        {
            int_t const error( ::pthread_mutex_trylock(&mutex_) );
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
            int_t const error( ::pthread_mutex_lock(&mutex_) );
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
            int_t const error( ::pthread_mutex_unlock(&mutex_) );
            if (error != 0)
            {   ///< UT Justified Branch: OS dependency
                setConstructed(false);
            }
        }
    }

    /**
     * @brief Initializes kernel mutex resource.
     * 
     * @return True if initialized sucessfully. 
     */
    bool_t initialize()
    {
        bool_t res( false );
        if( isConstructed() )
        {
            int_t const error( ::pthread_mutex_init(&mutex_, NULL) );
            res = error == 0;
        }
        return res;
    }

    /**
     * @brief Deinitializes kernel mutex resource.
     * 
     * @return True if deinitialized sucessfully. 
     */
    bool_t deinitialize()
    {
        bool_t res( false );
        if( isConstructed() )
        {        
            int_t const error( ::pthread_mutex_destroy(&mutex_) );
            res = error == 0;
        }
        return res;
    }

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
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
            res = true;
        } while(false);
        return res;
    }

    /**
     * @brief Mutex POSIX resource identifier.
     */
    ::pthread_mutex_t mutex_;

    /**
     * @brief Mutex resource identifier.
     */
    int32_t id_;
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
