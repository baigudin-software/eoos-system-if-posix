/**
 * @file      sys.StreamManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.StreamManager.hpp"

namespace eoos
{
namespace sys
{

StreamManager::StreamManager() 
    : NonCopyable<NoAllocator>()
    , api::StreamManager() 
    , cout_(OutStream::TYPE_COUT) 
    , cerr_(OutStream::TYPE_CERR) {
    setConstructed( true );
}

StreamManager::~StreamManager()
{
    cout_.flush();
    cerr_.flush();        
}

bool_t StreamManager::isConstructed() const
{
    return Parent::isConstructed();
}

api::OutStream<char_t>& StreamManager::getCout()
{
    return cout_;
}

api::OutStream<char_t>& StreamManager::getCerr()
{
    return cerr_;
}    
    
} // namespace sys
} // namespace eoos
