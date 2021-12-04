/**
 * @file      sys.Posix.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 * 
 * @brief POSIX System includes and definitions.
 */
#ifndef SYS_POSIX_HPP_
#define SYS_POSIX_HPP_

#include <stdlib.h>     ///< For EXIT(3)
#include <pthread.h>
#include <sys/types.h>
#include <time.h>       ///< For NANOSLEEP(2)
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>     ///< For GETPID(2)
#include <errno.h>

#endif // SYS_POSIX_HPP_
