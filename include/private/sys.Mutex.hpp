/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SysMutex.hpp"

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
    Mutex() noexcept : Parent()
    {
        bool_t const isConstructed = construct();
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Mutex() noexcept override
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override 
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    bool_t tryLock() noexcept override try
    {
        bool_t res {false};
        if( isConstructed() )
        {
            // @todo POSIX calls
        }
        return res;
    } catch (...) {
        return false;
    }    

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    bool_t lock() noexcept override try
    {
        bool_t res {false};
        if( not isConstructed() )
        {
            // @todo POSIX calls
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    void unlock() noexcept override try
    {
        if( not isConstructed() )
        {
            // @todo POSIX calls
        }
    } catch (...) {
        return;
    }

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() noexcept try
    {
        bool_t res = false;
        do
        {   
            if( not isConstructed() )
            {
                break;
            }
            // @todo POSIX calls
            res = false;
        } while(false);
        return res;
    } catch (...) {
        return false;
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
