/**
 * @file      sys.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_STREAMMANAGER_HPP_
#define SYS_STREAMMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.StreamManager.hpp"
#include "sys.OutStream.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class StreamManager.
 * @brief Stream sub-system manager.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A = Allocator>
class StreamManager : public NonCopyable<A>, public api::StreamManager
{
    typedef NonCopyable<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    StreamManager() 
        : NonCopyable<A>()
        , api::StreamManager() 
        , cout_(OutStream<A>::TYPE_COUT) 
        , cerr_(OutStream<A>::TYPE_CERR) {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    virtual ~StreamManager()
    {
        cout_.flush();
        cerr_.flush();        
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::StreamManager::getCout()
     */    
    virtual api::OutStream<char_t>& getCout()
    {
        return cout_;
    }
    
    /**
     * @copydoc eoos::api::StreamManager::getCerr()
     */
    virtual api::OutStream<char_t>& getCerr()
    {
        return cerr_;
    }    

protected:

    using Parent::setConstructed;

private:
    
    /**
     * @brief The system output character stream.
     */
    OutStream<A> cout_;

    /**
     * @brief The system error character stream.
     */
    OutStream<A> cerr_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_STREAMMANAGER_HPP_
