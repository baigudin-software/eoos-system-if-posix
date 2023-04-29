/**
 * @file      sys.MutexManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXMANAGER_HPP_
#define SYS_MUTEXMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.MutexManager.hpp"
#include "sys.Mutex.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class MutexManager.
 * @brief Mutex sub-system manager.
 */
class MutexManager : public NonCopyable, public api::MutexManager
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    MutexManager() 
        : NonCopyable()
        , api::MutexManager() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    virtual ~MutexManager()
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }    

    /**
     * @copydoc eoos::api::MutexManager::create()
     */
    virtual api::Mutex* create()
    {
        api::Mutex* ptr( NULLPTR );
        if( isConstructed() )
        {
            lib::UniquePointer<Mutex> mutex( new Mutex() );
            if( !mutex.isNull() )
            {
                bool_t res( false );
                if( mutex->isConstructed() )
                {
                    if( mutex->initialize() )
                    {
                        res = true;
                    }
                }
                if( res == false )
                {
                    mutex.reset();
                }
            }
            ptr = mutex.release();
        }    
        return ptr;
    }

    /**
     * @copydoc eoos::api::MutexManager::remove()
     */
    virtual void remove(api::Mutex* mutex)
    {
        if( isConstructed() && mutex != NULLPTR )
        {
            delete mutex;
        }
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEXMANAGER_HPP_
