/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "Program.hpp"

namespace eoos
{
namespace sys
{

System* System::eoos_( NULLPTR );

System::System()
    : NonCopyable<NoAllocator>()
    , api::System()
    , heap_()
    , scheduler_()
    , memoryManager_()    
    , mutexManager_()
    , semaphoreManager_()    
    , streamManager_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}    

System::~System()
{
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Heap& System::getHeap()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return heap_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

bool_t System::hasMutexManager()
{
    bool_t res( true );
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::MutexManager& System::getMutexManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return mutexManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

bool_t System::hasSemaphoreManager()
{
    bool_t res( true );
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::SemaphoreManager& System::getSemaphoreManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return semaphoreManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

bool_t System::hasStreamManager()
{
    bool_t res( true );
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::StreamManager& System::getStreamManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return streamManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

MemoryManager& System::getMemoryManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return memoryManager_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}    

int32_t System::execute() const
{
    char_t* args[] = {NULLPTR};
    return execute(0, args); ///< SCA MISRA-C++:2008 Justified Rule 5-2-12
}    

int32_t System::execute(int32_t argc, char_t* argv[]) const
{
    return Program::start(argc, argv);
}

System& System::getSystem()
{
    if(eoos_ == NULLPTR)
    {   ///< UT Justified Branch: Startup dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return *eoos_;
}

bool_t System::construct()
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
        if( !memoryManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }     
        if( !scheduler_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !mutexManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !semaphoreManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !streamManager_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }        
        eoos_ = this;
        res = true;
    } while(false);    
    return res;
}

void System::exit(Error error)
{
    ::exit( static_cast<int_t>(error) ); ///< SCA MISRA-C++:2008 Justified Rule 18-0-3
    // This code must NOT be executed
    while( true ) {}
}

} // namespace sys
} // namespace eoos
