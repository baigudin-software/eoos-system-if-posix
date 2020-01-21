/**
 * Semaphore class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SEMAPHORE_HPP_
#define SYSTEM_SEMAPHORE_HPP_

#include "system.Object.hpp"
#include "api.Semaphore.hpp"
#include "system.Interrupt.hpp"

namespace local
{
    namespace system
    {
        class Semaphore : public system::Object, public api::Semaphore
        {
            typedef system::Semaphore Self;
            typedef system::Object    Parent;

        public:

            /**
             * Constructor.
             *
             * @param permits the initial number of permits available.
             */
            Semaphore(int32 permits) : Parent()
            {
                bool const isConstructed = construct(permits);
                setConstructed( isConstructed );
            }

            /**
             * Destructor.
             */
            virtual ~Semaphore()
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
             * Acquires one permit from this semaphore.
             *
             * @return true if the semaphore is acquired successfully.
             */
            virtual bool acquire()
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Acquires the given number of permits from this semaphore.
             *
             * @param permits the number of permits to acquire.
             * @return true if the semaphore is acquired successfully.
             */
            virtual bool acquire(int32 permits)
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Releases one permit.
             */
            virtual void release()
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Releases the given number of permits.
             *
             * @param permits the number of permits to release.
             */
            virtual void release(int32 permits)
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Tests if this semaphore is fair.
             *
             * @return true if this semaphore has fairness set true.
             */
            virtual bool isFair() const
            {
                return false;
            }

            /**
             * Tests if this resource is blocked.
             *
             * @return true if this resource is blocked.
             */
            virtual bool isBlocked() const
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

        private:

            /**
             * Constructor.
             *
             * @param permits the initial number of permits available.
             * @return true if object has been constructed successfully.
             */
            bool construct(int32 permits)
            {
                if( not Self::isConstructed() ) return false;
                return true;
            }

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Semaphore(const Semaphore& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Semaphore& operator =(const Semaphore& obj);

        };
    }
}
#endif // SYSTEM_SEMAPHORE_HPP_
