/**
 * @file      sys.MemoryManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MEMORYMANAGER_HPP_
#define SYS_MEMORYMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "sys.Mutex.hpp"
#include "sys.MutexAllocator.hpp"
#include "sys.Semaphore.hpp"
#include "sys.SemaphoreAllocator.hpp"
#include "sys.Thread.hpp"
#include "sys.ThreadAllocator.hpp"
#include "sys.ResourceMemory.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class MemoryManager.
 * @brief Resource memory manager.
 */
class MemoryManager : public NonCopyable<NoAllocator>
{
    typedef NonCopyable<NoAllocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    MemoryManager();

    /**
     * @brief Destructor.
     */
    virtual ~MemoryManager();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @brief Return mutex memory.
     * 
     * @return Mutex memory
     */
    api::Heap& getMutexMemory();

    /**
     * @brief Return semaphore memory.
     * 
     * @return Semaphore memory
     */
    api::Heap& getSemaphoreMemory();

    /**
     * @brief Return thread memory.
     * 
     * @return Thread memory
     */
    api::Heap& getThreadMemory();

protected:

    using Parent::setConstructed;

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();
    
    /**
     * @brief Mutex memory allocator.
     */     
    ResourceMemory<Mutex<MutexAllocator>, EOOS_GLOBAL_SYS_NUMBER_OF_MUTEXS> mutexMemory_;

    /**
     * @brief Semaphore memory allocator.
     */     
    ResourceMemory<Semaphore<SemaphoreAllocator>, EOOS_GLOBAL_SYS_NUMBER_OF_SEMAPHORES> semaphoreMemory_;

    /**
     * @brief Thread memory allocator.
     */     
    ResourceMemory<Thread<ThreadAllocator>, EOOS_GLOBAL_SYS_NUMBER_OF_THREADS> threadMemory_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_MEMORYMANAGER_HPP_
