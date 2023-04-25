/**
 * @file      sys.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_STREAMMANAGER_HPP_
#define SYS_STREAMMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.StreamManager.hpp"
#include "sys.OutStreamChar.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class StreamManager.
 * @brief Stream sub-system manager.
 */
class StreamManager : public NonCopyable, public api::StreamManager
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    StreamManager() 
        : NonCopyable()
        , api::StreamManager() 
        , cout_(OutStreamChar::TYPE_COUT) 
        , cerr_(OutStreamChar::TYPE_CERR) {
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

private:
    
    /**
     * @brief The system output character stream.
     */
    OutStreamChar cout_;

    /**
     * @brief The system error character stream.
     */
    OutStreamChar cerr_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_STREAMMANAGER_HPP_
