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
        
bool_t System::isInitialized_ {false};

System::System() : Parent()
{
    bool_t const isConstructed = construct();
    setConstructed( isConstructed );
}

System::~System()
{
    isInitialized_ = false;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler() const
{
    if( not isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return scheduler_;
}

api::Mutex* System::createMutex()
{
    api::Mutex* const res = isConstructed() ? new Mutex() : NULLPTR;
    return proveResource(res);
}

api::Semaphore* System::createSemaphore(int32_t permits, bool_t isFair)
{
    api::Semaphore* const res = isConstructed() ? new Semaphore(permits) : NULLPTR;
    return proveResource(res);
}

int32_t System::execute()
{
    int32_t error;
    if( not isConstructed() )
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

void System::exit(Error const error)
{
    const int STATUS_MASK {0xFF};
    ::exit(static_cast<int>(error) & STATUS_MASK);
    // This code must NOT be executed
    // @todo throw an exection here is better.
    volatile bool_t const isTerminated = true;
    while( isTerminated ){};
}

bool_t System::construct()
{
    bool_t res = isConstructed();
    while(res == true)
    {
        if( isInitialized_ )
        {
            res = false;
            continue;
        }
        if( not scheduler_.isConstructed() )
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
