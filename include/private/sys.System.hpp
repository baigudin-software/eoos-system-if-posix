/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Scheduler.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable, public api::System
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    System();

    /**
     * @brief Destructor.
     */
    virtual ~System();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    virtual api::Scheduler& getScheduler() const;

    /**
     * @copydoc eoos::api::System::createMutex()
     */
    virtual api::Mutex* createMutex();

    /**
     * @copydoc eoos::api::System::creatSemaphore(int32_t)
     */
    virtual api::Semaphore* createSemaphore(int32_t permits);

    /**
     * @brief Executes the operating system.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute();

    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error);

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Proves a resource.
     *
     * @tparam T Resource type.
     * @param res A resource.
     * @return A passed resource, or NULLPTR if the resource has not been approved.
     */
    template <class T>
    static T* proveResource(T* res)
    {
        if(res != NULLPTR)
        {
            if( not res->isConstructed() )
            {
                delete res;
                res = NULLPTR;
            }
        }
        return res;
    }

    /**
     * @brief The operating system initialization flag.
     */
    static bool_t isInitialized_;
    
    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler scheduler_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
