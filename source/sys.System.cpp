/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "sys.Mutex.hpp"
#include "sys.Semaphore.hpp"
#include "Program.hpp"
#include "lib.LinkedList.hpp"

namespace eoos
{
namespace sys
{
        
api::System* System::system_ = NULLPTR;

System::System() : Parent()
{
    bool_t const isConstructed = construct();
    setConstructed( isConstructed );
}

System::~System()
{
    system_ = NULLPTR;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

int64_t System::getTime() const
{
    return 0;
}

api::Heap& System::getHeap() const
{
    if( not Self::isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return heap_;
}

api::Scheduler& System::getScheduler() const
{
    if( not Self::isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return scheduler_;
}

api::Mutex* System::createMutex()
{
    api::Mutex* const res = new Mutex();
    return proveResource(res);
}

api::Semaphore* System::createSemaphore(int32_t permits, bool_t isFair)
{
    api::Semaphore* const res = new Semaphore(permits);
    return proveResource(res);
}

int32_t System::execute()
{
    int32_t error;
    if( not Self::isConstructed() )
    {
        error = static_cast<int32_t>(Error::UNDEFINED);
    }
    else
    {
        lib::LinkedList<char_t*> args;
        error = Program::start(&args);
    }
    return error;
}

api::System& System::call()
{
    if( system_ == NULLPTR )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return *system_;
}

void System::exit(Error const error)
{
    // This code must NOT be executed
    // @todo throw an exection here is better.
    volatile bool_t const isTerminated = true;
    while( isTerminated ){};
}

bool_t System::construct()
{
    bool_t res = Self::isConstructed();
    while(res == true)
    {
        if( system_ != NULLPTR )
        {
            res = false;
            continue;
        }
        if( not heap_.isConstructed() )
        {
            res = false;
            continue;
        }
        if( not scheduler_.isConstructed() )
        {
            res = false;
            continue;
        }
        system_ = this;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
