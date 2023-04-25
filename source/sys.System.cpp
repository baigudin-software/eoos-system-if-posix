/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "Program.hpp"
#include "lib.LinkedList.hpp"

namespace eoos
{
namespace sys
{

api::System* System::eoos_( NULLPTR );

System::System() 
    : NonCopyable()
    , api::System()
    , heap_()    
    , scheduler_()
    , mutex_()
    , semaphore_()    
    , stream_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

System::~System() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1 and Defected Rule 10-3-2
{
    return Parent::isConstructed();
}

api::Heap& System::getHeap() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return heap_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Scheduler& System::getScheduler() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
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
    return mutex_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
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
    return semaphore_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
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
    return stream_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

int32_t System::execute() const
{
    char_t* args[] = {NULLPTR};    
    return execute(0, args); ///< SCA MISRA-C++:2008 Justified Rule 5-2-12
}
    
int32_t System::execute(int32_t argc, char_t* argv[]) const
{
    int32_t error( ERROR_OK );
    if( isConstructed() && (argc >= 0) && (argv != NULLPTR) )
    {
        lib::LinkedList<char_t*> args;
        for(int32_t i(0); i<argc; i++)
        {
            if( argv[i] != NULLPTR )
            {
                if( args.add(argv[i]) == true )
                {
                    continue;
                }
            }
            error = ERROR_ARGUMENT;
            break;
        }
        if( error != ERROR_ARGUMENT )
        {
            if( argv[argc] == NULLPTR )
            {
                error = Program::start(args);
            }
            else
            {
                error = ERROR_ARGUMENT;
            }

        }
    }
    else
    {
        error = ERROR_ARGUMENT;
    }
    return error;
}

api::System& System::getSystem()
{
    if(eoos_ == NULLPTR)
    {   ///< UT Justified Branch: Startup dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return *eoos_;
}
    
void System::exit(Error const error) ///< UT Justified Branch: HW dependency
{
    ::exit( static_cast<int_t>(error) ); ///< SCA MISRA-C++:2008 Justified Rule 18-0-3
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ) {}
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

} // namespace sys
} // namespace eoos
