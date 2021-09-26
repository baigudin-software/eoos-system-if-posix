/**
 * @file      sys.NonCopyable.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_NONCOPYABLE_HPP_
#define SYS_NONCOPYABLE_HPP_

#include "sys.Object.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class NonCopyable
 * @brief Root class of the operating system for objects which cannot be copied.
 */
class NonCopyable : public Object
{
    using Parent = Object;

public:

    /**
     * @brief Constructor.
     */
    NonCopyable() noexcept : Parent() {}

    /**
     * @brief Destructor.
     */
    ~NonCopyable() noexcept override {}
    
private:
    
    /**
     * @copydoc eoos::Object::Object(const Object&)
     */
    NonCopyable(const NonCopyable& obj) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(const Object&)
     */       
    NonCopyable& operator=(const NonCopyable& obj) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(const Object&&)
     */       
    NonCopyable(NonCopyable&& obj) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(const Object&&)
     */
    NonCopyable& operator=(NonCopyable&& obj) noexcept = delete;

};

} // namespace sys
} // namespace eoos
#endif // SYS_NONCOPYABLE_HPP_
