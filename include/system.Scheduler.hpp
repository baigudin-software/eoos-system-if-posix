/**
 * Thread tasks scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SCHEDULER_HPP_
#define SYSTEM_SCHEDULER_HPP_

#include "system.Object.hpp"
#include "api.Scheduler.hpp"
#include "system.GlobalThread.hpp"
#include "library.LinkedList.hpp"

namespace local
{
    namespace system
    {
        class SchedulerThread;

        class Scheduler : public system::Object, public api::Scheduler
        {
            typedef system::Scheduler Self;
            typedef system::Object    Parent;

        public:

            /**
             * Constructor.
             */
            Scheduler();

            /**
             * Destructor.
             */
            virtual ~Scheduler();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool isConstructed() const;

            /**
             * Creates a new thread.
             *
             * @param task an user task which main method will be invoked when created thread is started.
             * @return a new thread.
             */
            virtual api::Thread* createThread(api::Task& task);

            /**
             * Returns currently executing thread.
             *
             * @return executing thread.
             */
            virtual api::Thread& getCurrentThread() const;

            /**
             * Yields to next thread.
             */
            virtual void yield();

            /**
             * Returns the toggle interface for controlling global thread switching.
             *
             * @return toggle interface.
             */
            virtual api::Toggle& toggle();

            /**
             * Adds a thread to execution list
             *
             * @return true if thread has been added successfully.
             */
            bool addThread(SchedulerThread* thread);

            /**
             * Removes the first occurrence of the specified thread.
             *
             * @param thread removing thread.
             */
            void removeThread(SchedulerThread* thread);

        private:

            /**
             * Constructor.
             *
             * When first scheduler timer interrupt is occurred,
             * default registers of parent interrupt class will be used
             * for storing the operating system context to it.
             *
             * @return true if object has been constructed successfully.
             */
            bool construct();

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Scheduler(const Scheduler& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Scheduler& operator =(const Scheduler& obj);

            /**
             * Global thread switching controller.
             */
            GlobalThread globalThread_;

            /**
             * The tasks list.
             */
            library::LinkedList< SchedulerThread* > threads_;

        };
    }
}
#endif // SYSTEM_SCHEDULER_HPP_
