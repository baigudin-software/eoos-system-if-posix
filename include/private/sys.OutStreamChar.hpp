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
        TYPE_COUT, ///< @brief COUT
        TYPE_CERR  ///< @brief CERR
    };

    /**
     * @brief Constructor.
     *
     * @param type Type output.
     */
    OutStreamChar(Type type) 
        : NonCopyable()
        , api::OutStream<char_t>()
        , stream_( NULLPTR ) {
        bool_t const isConstructed( construct(type) );
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
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
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
            static_cast<void>( ::fputs(source, stream_) );
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
            static_cast<void>( ::fflush(stream_) );
        }
        return *this;
    }
    
private:

    /**
     * @brief Constructor.
     *
     * @param type Type output.     * 
     * @return True if object has been constructed successfully.
     */
    bool_t construct(Type type)
    {
        bool_t res( false );
        while(true)
        {   
            if( !isConstructed() )
            {
                break;
            }
            if(type == TYPE_COUT)
            {
                stream_ = ::stdout;
            }
            else
            {
                stream_ = ::stderr;
            }            
            res = true;
            break;
        }
        return res;
    }

    /**
     * @brief Output stream.
     */
    ::FILE* stream_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_OUTSTREAMCHAR_HPP_
