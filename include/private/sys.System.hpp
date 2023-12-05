/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Heap.hpp"
#include "sys.Scheduler.hpp"
#include "sys.MutexManager.hpp"
#include "sys.SemaphoreManager.hpp"
#include "sys.StreamManager.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable<NoAllocator>, public api::System
{
    typedef NonCopyable<NoAllocator> Parent;

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
    virtual api::Scheduler& getScheduler();

    /**
     * @copydoc eoos::api::System::getHeap()
     */
    virtual api::Heap& getHeap();

    /**
     * @copydoc eoos::api::System::getMutexManager()
     */
    virtual api::MutexManager& getMutexManager();

    /**
     * @copydoc eoos::api::System::getSemaphoreManager()
     */
    virtual api::SemaphoreManager& getSemaphoreManager();
    
    /**
     * @copydoc eoos::api::System::getStreamManager()
     */
    virtual api::StreamManager& getStreamManager();

    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]) const;

    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static System& getSystem();

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief The operating system.
     */
    static System* eoos_;

    /**
     * @brief The system heap.
     */
    Heap heap_;
 
    /**
     * @brief The operating system scheduler.
     */
    Scheduler scheduler_;

    /**
     * @brief The mutex sub-system manager.
     */
    MutexManager mutexManager_;

    /**
     * @brief The semaphore sub-system manager.
     */
    SemaphoreManager semaphoreManager_;
    
    /**
     * @brief The stream sub-system manager.
     */
    StreamManager streamManager_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
