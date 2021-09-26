/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.Thread.hpp"

namespace eoos
{
namespace sys
{
    
Scheduler::Scheduler() try : Parent()
{
    bool_t const isConstructed = construct();
    setConstructed( isConstructed );
} catch (...) {
    setConstructed(false);
}

Scheduler::~Scheduler()
{
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task) try
{
    return new Thread {task, this};
} catch (...) {
    return NULLPTR;
}

void Scheduler::sleep(int64_t millis, int32_t nanos) try
{
    // @todo POSIX calls
} catch (...) {
    return;
}

void Scheduler::yield() try
{
    // @todo POSIX calls
} catch (...) {
    return;
}

bool_t Scheduler::construct()
{
    bool_t res {false};
    do
    {
        if( not Self::isConstructed() )
        {
            break;
        }
        // @todo POSIX calls
        res = false;
    } while(false);
    return res;
}

} // namespace sys
} // namespace eoos
