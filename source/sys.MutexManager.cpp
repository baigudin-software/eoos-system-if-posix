/**
 * @file      sys.MutexManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexManager.hpp"
#include "sys.MutexAllocator.hpp"
#include "sys.Mutex.hpp"
#include "lib.UniquePointer.hpp"


namespace eoos
{
namespace sys
{

MutexManager::MutexManager() 
    : NonCopyable<NoAllocator>()
    , api::MutexManager() {
    setConstructed( true );
}

MutexManager::~MutexManager()
{
}

bool_t MutexManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::Mutex* MutexManager::create()
{
    api::Mutex* ptr( NULLPTR );
    if( isConstructed() )
    {
        lib::UniquePointer<api::Mutex> res( new Mutex<MutexAllocator>() );
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

} // namespace sys
} // namespace eoos
