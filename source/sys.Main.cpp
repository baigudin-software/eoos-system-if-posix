/**
 * @file      sys.Main.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"

/**
 * @brief The main function.
 *
 * The following tasks must be done before the function called:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 *
 * @return error code or zero.
 *
 * @todo Add the arguments to the function.
 * @todo Revise to remove the function at all as for now it won't work at all!
 */
int main() try
{
    ::eoos::sys::System eoos;
    ::eoos::int32_t const error = eoos.execute();
    return static_cast<int>(error);
} 
catch (...) 
{
    // Handle unexpected exceptions following MISRA-C++:2008 Rule 15–3–2 and AUTOSAR C++14 Rule A15-3-2
    return static_cast<int>(::eoos::sys::Error::UNDEFINED);
}
