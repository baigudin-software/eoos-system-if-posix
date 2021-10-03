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
    Scheduler();

    /**
     * @brief Destructor.
     */
    ~Scheduler() override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override;

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    api::Thread* createThread(api::Task& task) override;
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int64_t,int32_t)
     */
    void sleep(int64_t millis, int32_t nanos = 0) override;        

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    void yield() override;

private:

    /**
     * @brief Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();
    
};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
