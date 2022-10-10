/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "sys.Mutex.hpp"
#include "sys.Semaphore.hpp"
#include "Program.hpp"
#include "lib.LinkedList.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

api::System* System::eoos_( NULLPTR );

System::System() 
    : NonCopyable()
    , api::System()
    , configuration_()
    , scheduler_()
    , heap_() 
    , cout_(OutStreamChar::TYPE_COUT) 
    , cerr_(OutStreamChar::TYPE_CERR) {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

System::~System() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    static_cast<void>(cout_.flush());
    static_cast<void>(cerr_.flush());
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1 and Defected Rule 10-3-2
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Heap& System::getHeap() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return heap_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::OutStream<char_t>& System::getOutStreamChar() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return cout_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::OutStream<char_t>& System::getErrorStreamChar() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(ERROR_SYSCALL_CALLED);
    }
    return cerr_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Mutex* System::createMutex() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    api::Mutex* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Mutex> res( new Mutex() );
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                res.reset();
            }
        }
        ptr = res.release();
    }    
    return ptr;
}

api::Semaphore* System::createSemaphore(int32_t permits) ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    api::Semaphore* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Semaphore> res( new Semaphore(permits) );
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
        if( !scheduler_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !heap_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !cout_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !cerr_.isConstructed() )
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
