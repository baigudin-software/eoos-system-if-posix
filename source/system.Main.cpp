/**
 * The main entry point.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"

/**
 * Executes a user application main process.
 */
int main()
{
    ::local::system::System eoos;
    return eoos.execute();
}
