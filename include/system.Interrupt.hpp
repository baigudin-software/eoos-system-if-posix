/**
 * Hardware interrupt resource.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSYEM_INTERRUPT_HPP_
#define SYSYEM_INTERRUPT_HPP_

#include "system.Object.hpp"
#include "api.Interrupt.hpp"
#include "api.Task.hpp"

namespace local
{
    namespace system
    {
        class Interrupt : public system::Object, public api::Interrupt
        {
            typedef system::Interrupt Self;
            typedef system::Object    Parent;

        public:

            /**
             * Constructor.
             *
             * @param handler user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             */
            Interrupt(api::Task& handler, int32 source);

            /**
             * Destructor.
             */
            virtual ~Interrupt();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool isConstructed() const;

            /**
             * Jumps to interrupt hardware vector.
             */
            virtual void jump();

            /**
             * Clears an interrupt status of this source.
             */
            virtual void clear();

            /**
             * Sets an interrupt status of this source.
             */
            virtual void set();

            /**
             * Locks this interrupt source.
             *
             * @return an interrupt enable source bit value before method was called.
             */
            virtual bool disable();

            /**
             * Unlocks this interrupt source.
             *
             * @param status returned status by lock method.
             */
            virtual void enable(bool status);

            /**
             * Disables all maskable interrupts.
             *
             * @return global interrupts enable bit value before method was called.
             */
            static bool disableAll();

            /**
             * Enables all maskable interrupts.
             *
             * The true passed argument directly turns all maskable interrupts on,
             * and the false does nothing, the interrupts stay in the current state.
             *
             * @param status the returned status by disable method.
             */
            static void enableAll(bool status=true);

        private:

            /**
             * Constructor.
             *
             * @param handler pointer to user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             * @return true if object has been constructed successfully.
             */
            bool construct(api::Task* handler, int32 source);

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Interrupt(const Interrupt& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Interrupt& operator =(const Interrupt& obj);

        };
    }
}
#endif // SYSYEM_INTERRUPT_HPP_
