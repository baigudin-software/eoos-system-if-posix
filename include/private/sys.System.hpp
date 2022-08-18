/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Configuration.hpp"
#include "sys.Scheduler.hpp"
#include "sys.Heap.hpp"
#include "sys.OutStreamChar.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable, public api::System
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    System();

    /**
     * @brief Destructor.
     */
    virtual ~System();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    virtual api::Scheduler& getScheduler();

    /**
     * @copydoc eoos::api::System::getHeap()
     */
    virtual api::Heap& getHeap();
    
    /**
     * @copydoc eoos::api::System::getOutStreamChar()
     */    
    virtual api::OutStream<char_t>& getOutStreamChar();

    /**
     * @copydoc eoos::api::System::getErrorStreamChar()
     */    
    virtual api::OutStream<char_t>& getErrorStreamChar();    

    /**
     * @copydoc eoos::api::System::createMutex()
     */
    virtual api::Mutex* createMutex();

    /**
     * @copydoc eoos::api::System::creatSemaphore(int32_t)
     */
    virtual api::Semaphore* createSemaphore(int32_t permits);

    /**
     * @brief Executes the operating system.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute() const;
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.  
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]) const;

    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static api::System& getSystem();

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();

    #ifdef EOOS_ENABLE_DYNAMIC_HEAP_MEMORY

    /**
     * @brief Operator new.
     *
     * @note Prohibited to be called as no system heap is initialized till the operation.
     *
     * @param size A number of bytes to allocate.
     * @return Allocated memory address or a null pointer.
     */
    static void* operator new(size_t);
    
    /**
     * @brief Operator delete.
     *
     * @note Prohibited to be called as no system heap is initialized till the operation.
     *
     * @param ptr An address of allocated memory block or a null pointer.
     */
    static void operator delete(void*);

    /**
     * @brief Returns nullptr.
     *
     * The function is defined just to avoid G++ warning: 
     * ‘operator new’ must not return NULL unless it is declared ‘throw()’
     * as the EOOS POSIX has to be compiled with C++98 and therefore
     * operator new(std::size_t, std::nothrow_t const&) cannot be declared.
     *
     * @return nullptr.
     */
    static void* getNullptr();

    #endif // EOOS_ENABLE_DYNAMIC_HEAP_MEMORY
    
    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error);    

    /**
     * @brief The operating system.
     */
    static api::System* eoos_;

    /**
     * @brief The operating system configuration.
     */
    Configuration configuration_;
    
    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler scheduler_;

    /**
     * @brief The system heap.
     */
    mutable Heap heap_;    

    /**
     * @brief The system output character stream.
     */
    OutStreamChar cout_;
    
    /**
     * @brief The system error character stream.
     */
    OutStreamChar cerr_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
