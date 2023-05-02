/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Scheduler.hpp"
#include "sys.MutexManager.hpp"
#include "sys.SemaphoreManager.hpp"
#include "sys.StreamManager.hpp"
#include "sys.Heap.hpp"
#include "sys.Error.hpp"
#include "lib.LinkedList.hpp"
#include "Program.hpp"

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
    System()
        : NonCopyable<NoAllocator>()
        , api::System()
        , heap_()    
        , scheduler_()
        , mutex_()
        , semaphore_()    
        , stream_() {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }    

    /**
     * @brief Destructor.
     */
    virtual ~System()
    {
        eoos_ = NULLPTR;
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    virtual api::Scheduler& getScheduler()
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

    /**
     * @copydoc eoos::api::System::getHeap()
     */
    virtual api::Heap& getHeap()
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return heap_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }    

    /**
     * @copydoc eoos::api::System::hasMutexManager()
     */
    virtual bool_t hasMutexManager()
    {
        bool_t res( true );
        if( !isConstructed() )
        {
            res = false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::System::getMutexManager()
     */
    virtual api::MutexManager& getMutexManager()
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return mutex_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

    /**
     * @copydoc eoos::api::System::hasSemaphoreManager()
     */
    virtual bool_t hasSemaphoreManager()
    {
        bool_t res( true );
        if( !isConstructed() )
        {
            res = false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::System::getSemaphoreManager()
     */
    virtual api::SemaphoreManager& getSemaphoreManager()
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return semaphore_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }
    
    /**
     * @copydoc eoos::api::System::hasStreamManager()
     */
    virtual bool_t hasStreamManager()
    {
        bool_t res( true );
        if( !isConstructed() )
        {
            res = false;
        }
        return res;
    }

    /**
     * @copydoc eoos::api::System::getStreamManager()
     */
    virtual api::StreamManager& getStreamManager()
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return stream_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
    }

    /**
     * @brief Executes the operating system.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute() const
    {
        char_t* args[] = {NULLPTR};
        return execute(0, args); ///< SCA MISRA-C++:2008 Justified Rule 5-2-12
    }    
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]) const
    {
        return Program::start(argc, argv);
    }

    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static api::System& getSystem()
    {
        if(eoos_ == NULLPTR)
        {   ///< UT Justified Branch: Startup dependency
            exit(ERROR_SYSCALL_CALLED);
        }
        return *eoos_;
    }

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
            if( eoos_ != NULLPTR )
            {   ///< UT Justified Branch: Startup dependency
                break;
            }
            if( !heap_.isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }                
            if( !scheduler_.isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            if( !mutex_.isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            if( !semaphore_.isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            if( !stream_.isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }        
            eoos_ = this;
            res = true;
        } while(false);    
        return res;
    }
    
    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error)
    {
        ::exit( static_cast<int_t>(error) ); ///< SCA MISRA-C++:2008 Justified Rule 18-0-3
        // This code must NOT be executed
        // @todo throw an exection here is better.
        while( true ) {}
    }

    /**
     * @brief The operating system.
     */
    static api::System* eoos_;

    /**
     * @brief The system heap.
     */
    mutable Heap heap_;
 
    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler<NoAllocator> scheduler_;

    /**
     * @brief The mutex sub-system manager.
     */
    mutable MutexManager<NoAllocator> mutex_;

    /**
     * @brief The semaphore sub-system manager.
     */
    mutable SemaphoreManager<NoAllocator> semaphore_;
    
    /**
     * @brief The stream sub-system manager.
     */
    mutable StreamManager<NoAllocator> stream_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
