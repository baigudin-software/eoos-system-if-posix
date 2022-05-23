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
        
bool_t System::isInitialized_(false);

System::System() 
    : NonCopyable()
    , api::System()
    , scheduler_() {
    bool_t const isConstructed( construct() );
    setConstructed( isConstructed );
}

System::~System() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    isInitialized_ = false;
}

bool_t System::isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1 and Defected Rule 10-3-2
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
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
            {
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
    int32_t error;
    if( !isConstructed() )
    {
        error = static_cast<int32_t>(ERROR_UNDEFINED);
    }
    else
    {
        lib::LinkedList<char_t*> args;
        error = Program::start(&args);
    }
    return error;
}

void System::exit(Error const error)
{
    ::exit( static_cast<int_t>(error) );
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ) {}
}

bool_t System::construct() const
{
    bool_t res( isConstructed() );
    while(res == true)
    {
        if( isInitialized_ )
        {
            res = false;
            continue;
        }
        if( !scheduler_.isConstructed() )
        {
            res = false;
            continue;
        }
        isInitialized_ = true;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
