/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "lib.Object.hpp"
#include "sys.Allocator.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 *
 * @tparam A Heap memory allocator class.
 */
template <class A = Allocator>
class Object : public lib::Object<A>
{
    typedef lib::Object<A> Parent;

public:

    /**
     * @brief Constructor.
     */
    Object()
        : lib::Object<A>() {
    }

    /**
     * @brief Destructor.
     */
    virtual ~Object() {}
    
    /**
     * @copydoc eoos::Object::Object(const Object&)
     */
    Object(const Object& obj) 
        : lib::Object<>(obj) {
    } 
    
    /**
     * @copydoc eoos::Object::operator=(const Object&)
     */       
    Object& operator=(const Object& obj)
    {
        static_cast<void>( Parent::operator=(obj) );
        return *this;
    }    

    #if EOOS_CPP_STANDARD >= 2011

    /**
     * @copydoc eoos::Object::Object(const Object&&)
     */       
    Object(Object&& obj) 
        : lib::Object<>( lib::move(obj) ) {
    }
    
    /**
     * @copydoc eoos::Object::operator=(const Object&&)
     */
    Object& operator=(Object&& obj)
    {
        Parent::operator=( lib::move(obj) );
        return *this;
    }
    
    #endif // EOOS_CPP_STANDARD >= 2011    

};

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
