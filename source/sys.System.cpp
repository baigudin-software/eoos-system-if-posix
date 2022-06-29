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
    , scheduler_()
    , heap_() 
    , cout_(OutStreamChar::TYPE_COUT) 
    , cerr_(OutStreamChar::TYPE_CERR) {
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

api::Scheduler& System::getScheduler() ///< SCA MISRA-C++:2008 Defected Rule 10-3-2
{
    if( !isConstructed() )
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA MISRA-C++:2008 Justified Rule 9-3-2
}

api::Heap& System::getHeap()
{
    if( !isConstructed() )
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return heap_;
}

api::OutStream<char_t>& System::getOutStreamChar()
{
    if( !isConstructed() )
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return cout_;
}

api::OutStream<char_t>& System::getErrorStreamChar()
{
    if( !isConstructed() )
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return cerr_;
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
    return execute(0, NULLPTR);
}
    
int32_t System::execute(int32_t argc, char_t* argv[]) const
{
    int32_t error;
    if( !isConstructed() )
    {
        error = static_cast<int32_t>(ERROR_UNDEFINED);
    }
    else
    {
        lib::LinkedList<char_t*> args;
        for(int32_t i(0); i<argc; i++)
        {
            args.add(argv[i]);
        }
        error = Program::start(args);        
    }
    return error;
}

api::System& System::getSystem()
{
    if(eoos_ == NULLPTR)
    {
        exit(ERROR_SYSCALL_CALLED);
    }
    return *eoos_;
}
    
#ifdef EOOS_NO_STRICT_MISRA_RULES

void* System::operator new(size_t)
{
    return getNullptr();
}

void System::operator delete(void*)
{
}

void* System::getNullptr()
{
    return NULLPTR;
}
    
#endif // EOOS_NO_STRICT_MISRA_RULES
    
void System::exit(Error const error)
{
    ::exit( static_cast<int_t>(error) );
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ) {}
}

bool_t System::construct()
{
    bool_t res( isConstructed() );
    while(res == true)
    {
        if( eoos_ != NULLPTR )
        {
            res = false;
            continue;
        }
        if( !scheduler_.isConstructed() )
        {
            res = false;
            continue;
        }
        if( !heap_.isConstructed() )
        {
            res = false;
            continue;
        }
        eoos_ = this;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
