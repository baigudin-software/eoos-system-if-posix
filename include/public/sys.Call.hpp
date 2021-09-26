/**
 * @file      sys.Call.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_CALL_HPP_
#define SYS_CALL_HPP_

#include "api.System.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class Call
 * @brief System calls class of the operating system.
 */
class Call
{

public:

    /**
     * @brief Initializes the operating system.
     *
     * This function has to be called to create internel object of the OS.
     * This allows to access to the `get` function and also uses resourses 
     * of a native OS.
     *
     * @return True if the operating system is initialized.
     */
    static bool_t initialize();
    
    /**
     * @brief Deinitializes the operating system.
     */
    static void deinitialize();
    
    /**
     * @brief Executes the operating system.
     *
     * This function invokes `Program::start()` function if the OS is initialized.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    static int32_t execute();    

    /**
     * @brief Returns the operating system syscall interface.
     *
     * @return The operating system syscall interface.
     */
    static api::System& get();

};

} // namespace sys
} // namespace eoos
#endif // SYS_CALL_HPP_
