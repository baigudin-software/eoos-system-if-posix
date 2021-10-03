/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SysSemaphore.hpp"

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
    Semaphore(int32_t permits) : Parent()
    {
        bool_t const isConstructed = construct(permits);
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Semaphore() override
    {
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
        if( not isConstructed() ) return false;
        return false;
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire(int32_t)
     */
    bool_t acquire(int32_t permits) override
    {
        if( not isConstructed() ) return false;
        return false;
    }

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    void release() override
    {
        if( not isConstructed() ) return;
    }

    /**
     * @copydoc eoos::api::Semaphore::release(int32_t)
     */
    void release(int32_t permits) override
    {
        if( not isConstructed() ) return;
    }

    /**
     * @copydoc eoos::api::Semaphore::isFair()
     */
    bool_t isFair() const override
    {
        return false;
    }

private:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     * @return true if object has been constructed successfully.
     */
    bool_t construct(int32_t permits)
    {
        if( not isConstructed() ) return false;
        return true;
    }

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
