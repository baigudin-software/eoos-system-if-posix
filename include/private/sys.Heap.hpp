/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "api.Heap.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Heap.
 * @brief Heap class.
 */
class Heap : public api::Heap
{

public:

    /**
     * @brief Constructor.
     */
    Heap() 
        : api::Heap() {
    }

    /**
     * @brief Destructor.
     */
    virtual ~Heap()
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const ///< SCA MISRA-C++:2008 Justified Rule 10-3-1
    {
        return true;
    }
    
    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    virtual void* allocate(size_t const size, void* ptr)
    {
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #ifdef EOOS_GLOBAL_ENABLE_NO_HEAP
        static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        return NULLPTR;
        #else
        return new ucell_t[size];
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    }

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    virtual void free(void* ptr)
    {
        #ifdef EOOS_GLOBAL_ENABLE_NO_HEAP
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4        
        #else
        ucell_t* const mem( reinterpret_cast<ucell_t* const>(ptr) ); ///< SCA MISRA-C++:2008 Justified Rule 5-2-8
        delete[] mem;
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    }
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
