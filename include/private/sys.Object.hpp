/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "Object.hpp"
#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 */
class Object : public ::eoos::Object<Allocator>
{
    using Parent = ::eoos::Object<Allocator>;

public:

    /**
     * @brief Constructor.
     */
    Object() noexcept : Parent() {}

    /**
     * @brief Destructor.
     */
    ~Object() noexcept override {}
    
    /**
     * @copydoc eoos::Object::Object(const Object&)
     */
    Object(const Object& obj) noexcept : Parent(obj) {} 
    
    /**
     * @copydoc eoos::Object::operator=(const Object&)
     */       
    Object& operator=(const Object& obj) noexcept
    {
        Parent::operator=(obj);
        return *this;
    }    

    /**
     * @copydoc eoos::Object::Object(const Object&&)
     */       
    Object(Object&& obj) noexcept : Parent( lib::move(obj) ) {}
    
    /**
     * @copydoc eoos::Object::operator=(const Object&&)
     */
    Object& operator=(Object&& obj) noexcept
    {
        Parent::operator=( lib::move(obj) );
        return *this;
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
