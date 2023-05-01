/**
 * @file      sys.SemaphoreManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREMANAGER_HPP_
#define SYS_SEMAPHOREMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SemaphoreManager.hpp"
#include "sys.Semaphore.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SemaphoreManager.
 * @brief Semaphore sub-system manager.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A = Allocator>
class SemaphoreManager : public NonCopyable<A>, public api::SemaphoreManager
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    SemaphoreManager() 
        : NonCopyable<A>()
        , api::SemaphoreManager() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    virtual ~SemaphoreManager()
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
     * @copydoc eoos::api::SemaphoreManager::create()
     */
    virtual api::Semaphore* create(int32_t permits)
    {
        api::Semaphore* ptr( NULLPTR );
        if( isConstructed() )
        {
            lib::UniquePointer<api::Semaphore> res( new Semaphore<A>(permits) );
            if( !res.isNull() )
            {
                if( !res->isConstructed() )
                {
                    res.reset();
                }
            }
            ptr = res.release();
        }    
        return ptr;
    }

    /**
     * @copydoc eoos::api::SemaphoreManager::remove()
     */
    virtual void remove(api::Semaphore* semaphore)
    {
        if( isConstructed() && semaphore != NULLPTR )
        {
            delete semaphore;
        }
    }

protected:

    using Parent::setConstructed;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHOREMANAGER_HPP_
