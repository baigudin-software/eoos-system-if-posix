/**
 * @file      sys.OutStream.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OUTSTREAM_HPP_
#define SYS_OUTSTREAM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.OutStream.hpp"
#include "lib.BaseString.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class OutStream.
 * @brief OutStream class.
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A = Allocator>
class OutStream : public NonCopyable<A>, public api::OutStream<char_t>
{
    typedef NonCopyable<A> Parent;

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
    OutStream(Type type) 
        : NonCopyable<A>()
        , api::OutStream<char_t>()
        , stream_( NULLPTR ) {
        bool_t const isConstructed( construct(type) );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~OutStream()
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
     * @copydoc eoos::api::OutStream::operator<<(T const*)
     */
    virtual api::OutStream<char_t>& operator<<(char_t const* source)
    {
        if( isConstructed() )
        {
            static_cast<void>( ::fputs(source, stream_) );
        }
        return *this;
    }

    /**
     * @copydoc eoos::api::OutStream::operator<<(int32_t)
     */
    virtual api::OutStream<char_t>& operator<<(int32_t value)
    {
        lib::BaseString<char_t,16> str(value);
        return this->operator<<( str.getChar() );
    }    

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    virtual api::OutStream<char_t>& flush()
    {
        if( isConstructed() )
        {
            static_cast<void>( ::fflush(stream_) );
        }
        return *this;
    }

protected:

    using Parent::setConstructed;
    
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
            {   ///< UT Justified Branch: HW dependency
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
#endif // SYS_OUTSTREAM_HPP_
