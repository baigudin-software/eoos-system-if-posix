/**
 * @file      sys.Error.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin
 */
#ifndef SYS_ERROR_HPP_
#define SYS_ERROR_HPP_

namespace eoos
{
namespace sys
{
    
/**
 * @enum  Error
 * @brief The operating system error codes.
 */
enum class Error : int32_t
{
    /**
     * @brief No errors have been occurred.
     */
    OK = 0,

    /**
     * @brief Error of the operating system kernel syscall calling.
     */
    SYSCALL_CALLED = 1,

    /**
     * @brief Error of the OS termination.
     */
    SYSTEM_ABORT = 2,

    /**
     * @brief Error of a user program occurred.
     */
    USER_ABORT = 3,

    /**
     * @brief Error of searching of a resource.
     */
    RESOURCE_NOT_FOUND = 4,

    /**
     * @brief An undefined error has been occurred.
     */
    UNDEFINED = 127,

    /**
     * @brief The last unused error code.
     */
    LAST = 128

};

} // namespace sys
} // namespace eoos
#endif // SYS_ERROR_HPP_
