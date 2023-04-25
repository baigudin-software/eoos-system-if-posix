/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
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
 * @class Heap.
 * @brief Heap class.
 */
class Heap : public NonCopyable, public api::Heap
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    Heap() 
        : NonCopyable()
        , api::Heap() {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
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
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    virtual void* allocate(size_t const size, void* ptr)
    {    
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
        return new ucell_t[size];
        #else
        static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        return NULLPTR;
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    }

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    virtual void free(void* ptr)
    {
        #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
        ucell_t* const mem( reinterpret_cast<ucell_t* const>(ptr) ); ///< SCA MISRA-C++:2008 Justified Rule 5-2-8
        delete[] mem;
        #else
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    }
    
private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() const
    {
        bool_t res( false );
        while(true)
        {   
            if( !isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            res = true;
            break;
        }
        return res;
    }
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
