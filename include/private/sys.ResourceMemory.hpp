/**
 * @file      sys.ResourceMemory.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_RESOURCEMEMORY_HPP_
#define SYS_RESOURCEMEMORY_HPP_

#include "sys.NonCopyable.hpp"
#include "sys.Heap.hpp"
#include "sys.Mutex.hpp"
#include "lib.MutexGuard.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class ResourceMemory<T,N>
 * @brief Pool resource memory allocator.
 * 
 * @tparam T Resource type
 * @tparam N Number of resources
 */
template <typename T, int32_t N>
class ResourceMemory : public NonCopyable<NoAllocator>, public api::Heap
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    ResourceMemory() 
        : NonCopyable<NoAllocator>()
        , api::Heap() {
        bool_t const isConstructed( construct() );
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    virtual ~ResourceMemory() 
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
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    virtual void* allocate(size_t size, void* ptr)
    {
        lib::MutexGuard<NoAllocator> guard( mutex_ );
        if( size != sizeof(T) )
        {
            return NULLPTR;
        }
        for(int32_t i=0; i<N; i++)
        {
            if( isAllocated_[i] == true )
            {
                continue;
            }
            uint64_t* const memory( memory_[i] );
            uintptr_t const address( reinterpret_cast<uintptr_t>(memory) );
            if( ( address & 0x7 ) != 0 )
            {
                return NULLPTR;
            }
            isAllocated_[i] = true;
            return memory;
        }
        return NULLPTR;
    }

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    virtual void free(void* ptr)
    {
        lib::MutexGuard<NoAllocator> guard( mutex_ );
        for(int32_t i=0; i<N; i++)
        {
            if( memory_[i] == ptr )
            {
                isAllocated_[i] = false;
                return;
            }
        }
    }

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res( false );
        do 
        {
            if( !isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            for(int32_t i=0; i<N; i++)
            {
                isAllocated_[i] = false;
            }
            res = true;
        } while(false);    
        return res;
    }

    /**
     * @brief Resource allocation guard 
     */
    Mutex<NoAllocator> mutex_;

    /**
     * @brief Resource memory pull. 
     */
    bool_t isAllocated_[N]; 

    /**
     * @brief Resource memory pull.
     * 
     * @note Memory is double array of uint64_t type to be align 8.  
     */
    uint64_t memory_[N][(sizeof(T) >> 3) + 1]; 
    
};

/**
 * @class ResourceMemory<T,0>
 * @brief Heap resource memory allocator.
 * 
 * @tparam T Resource type
 */
template <typename T>
class ResourceMemory<T,0> : public Heap
{

public:

    /**
     * @brief Constructor.
     */
    ResourceMemory() 
        : Heap() {
    }

    /**
     * @brief Destructor.
     */
    virtual ~ResourceMemory() 
    {
    }
    
};

} // namespace sys
} // namespace eoos

#endif // SYS_RESOURCEMEMORY_HPP_
