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
    ~Heap()
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    void* allocate(size_t const size, void* ptr)
    {    
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #ifdef EOOS_NO_STRICT_MISRA_RULES
        return new cell_t[size];
        #else
        static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        return NULLPTR;
        #endif
    }

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    void free(void* ptr)
    {
        #ifdef EOOS_NO_STRICT_MISRA_RULES
        cell_t* const mem( reinterpret_cast<cell_t* const>(ptr) );
        delete[] mem;
        #else
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #endif
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
            {
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
