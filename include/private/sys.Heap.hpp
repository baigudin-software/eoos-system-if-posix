/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Heap.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Heap
 * @brief The operating system heap memory class.
 */
class Heap : public NonCopyable, public api::Heap
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Heap();

    /**
     * @brief Destructor.
     */
    ~Heap() override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override;

    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    void* allocate(size_t size, void* ptr) override;

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    void free(void* ptr) override;

};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
