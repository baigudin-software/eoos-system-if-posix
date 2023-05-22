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
    Mutex();

    /**
     * @brief Destructor.
     */
    virtual ~Mutex();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    virtual bool_t tryLock();

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    virtual bool_t lock();

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    virtual void unlock();

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Initializes kernel mutex resource.
     * 
     * @return True if initialized sucessfully. 
     */
    bool_t initialize();

    /**
     * @brief Deinitializes kernel mutex resource.
     */
    void deinitialize();

    /**
     * @brief Mutex POSIX resource identifier.
     */
    ::pthread_mutex_t mutex_;
    
};

template <class A>
Mutex<A>::Mutex()
    : NonCopyable<A>()
    , api::Mutex()
    , mutex_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

template <class A>
Mutex<A>::~Mutex()
{
    deinitialize();
}

template <class A>
bool_t Mutex<A>::isConstructed() const
{
    return Parent::isConstructed();
}

template <class A>
bool_t Mutex<A>::tryLock()
{
    bool_t res( false );
    if( isConstructed() )
    {
        int_t const error( ::pthread_mutex_trylock(&mutex_) );
        res = (error == 0) ? true : false;
    }
    return res;
}    

template <class A>
bool_t Mutex<A>::lock()
{
    bool_t res( false );
    if( isConstructed() )
    {
        int_t const error( ::pthread_mutex_lock(&mutex_) );
        res = (error == 0) ? true : false;
    }
    return res;
}

template <class A>
void Mutex<A>::unlock()
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

template <class A>
bool_t Mutex<A>::construct()
{
    bool_t res( false );
    do
    {   
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !initialize() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

template <class A>
bool_t Mutex<A>::initialize()
{
    int_t const error( ::pthread_mutex_init(&mutex_, NULL) );
    return error == 0;
}

template <class A>
void Mutex<A>::deinitialize()
{
    static_cast<void>( ::pthread_mutex_destroy(&mutex_) );
}

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
