/**
 * @file      sys.OutStreamChar.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OUTSTREAMCHAR_HPP_
#define SYS_OUTSTREAMCHAR_HPP_

#include "sys.NonCopyable.hpp"
#include "api.OutStream.hpp"
#include "lib.Memory.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class OutStreamChar.
 * @brief OutStreamChar class.
 */
class OutStreamChar : public NonCopyable, public api::OutStream<char_t>
{
    typedef NonCopyable Parent;

public:

    /**
     * @class Type.
     * @brief Type output.
     */
    enum Type
    {
        TYPE_OUT, ///< @brief COUT
        TYPE_ERR  ///< @brief CERR
    };

    /**
     * @brief Constructor.
     *
     * @param type Type output.
     */
    OutStreamChar(Type type) 
        : NonCopyable()
        , api::OutStream<char_t>()
        , type_( type ) {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~OutStreamChar()
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::OutStream::operator<<()
     */
    virtual OutStream<char_t>& operator<<(char_t const* source)
    {
        if( isConstructed() )
        {
        }
        return *this;
    }

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    virtual OutStream<char_t>& flush()
    {
        if( isConstructed() )
        {
        }
        return *this;
    }
    
private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res( false );
        while(true)
        {   
            if( !isConstructed() )
            {
                break;
            }
            // @todo Init...
            res = true;
            break;
        }
        return res;
    }
    
    /**
     * @brief Type of stream.
     */
    Type type_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_OUTSTREAMCHAR_HPP_
