/**
 * @file      sys.Call.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Call.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

static System* system_(NULLPTR);

bool_t Call::initialize()
{
    bool_t isConstructed(false);
    do {
        if(system_ != NULLPTR)
        {
            break;
        }
        system_ = new System();
        if(system_ == NULLPTR)
        {
            break;
        }
        isConstructed = system_->isConstructed();
        if( not isConstructed )
        {
            delete system_;
            system_ = NULLPTR;
        }
    } while(false);
    return isConstructed;
}

void Call::deinitialize()
{
    if(system_ != NULLPTR)
    {
        delete system_;
        system_ = NULLPTR;
    }    
}

int32_t Call::execute()
{
    return (system_ != NULLPTR) ? system_->execute() : -1;
}
    
api::System& Call::get()
{
    if(system_ == NULLPTR)
    {
        System::exit(ERROR_SYSTEM_ABORT);
    }
    return *system_;
}

} // namespace sys
} // namespace eoos
