/**
 * @file      sys.Scheduler.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Scheduler.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Scheduler
 * @brief Thread tasks scheduler class.
 */
class Scheduler : public NonCopyable, public api::Scheduler
{
    typedef NonCopyable Parent;

public:

    /**
     * @brief Constructor.
     */
    Scheduler();

    /**
     * @brief Destructor.
     */
    virtual ~Scheduler();

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const;

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    virtual api::Thread* createThread(api::Task& task);
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    virtual bool_t sleep(int32_t ms);

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    virtual void yield();
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
