/**
 * Global thread switching controller.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_GLOBAL_THREAD_HPP_
#define SYSTEM_GLOBAL_THREAD_HPP_

#include "system.Object.hpp"
#include "api.Toggle.hpp"

namespace local
{
    namespace system
    {
        class GlobalThread : public system::Object, public api::Toggle
        {
            typedef system::GlobalThread Self;
            typedef system::Object       Parent;

        public:

            /**
             * Constructor.
             */
            GlobalThread() : Parent()
            {
            }

            /**
             * Destructor.
             */
            virtual ~GlobalThread()
            {
            }

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool isConstructed() const
            {
                return Parent::isConstructed();
            }

            /**
             * Disables all maskable interrupts.
             *
             * @return global interrupt enable bit value before method was called.
             */
            virtual bool disable()
            {
                return false;
            }

            /**
             * Enables all maskable interrupts.
             *
             * @param status returned status by disable method.
             */
            virtual void enable(bool status)
            {
            }

        private:

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            GlobalThread(const GlobalThread& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            GlobalThread& operator =(const GlobalThread& obj);

        };
    }
}
#endif // SYSTEM_GLOBAL_THREAD_HPP_
