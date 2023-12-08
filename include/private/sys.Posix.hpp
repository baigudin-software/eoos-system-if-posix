/**
 * @file      sys.Posix.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2023, Sergey Baigudin, Baigudin Software
 * 
 * @brief POSIX System includes and definitions.
 */
#ifndef SYS_POSIX_HPP_
#define SYS_POSIX_HPP_

#include <sys/types.h>
#include <stdlib.h> ///< SCA MISRA-C++:2008 Justified Rule 18-0-1
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h> ///< SCA MISRA-C++:2008 Justified Rule 18-0-1 and Rule 27-0-1
#include <errno.h>

#endif // SYS_POSIX_HPP_
