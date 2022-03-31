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
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Scheduler() = default;

    /**
     * @brief Destructor.
     */
    ~Scheduler() override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override;

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    api::Thread* createThread(api::Task& task) override;
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    bool_t sleep(int32_t ms) override;

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    void yield() override;
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
