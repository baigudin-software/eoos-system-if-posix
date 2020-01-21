/**
 * Mutex class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MUTEX_HPP_
#define SYSTEM_MUTEX_HPP_

#include "system.Object.hpp"
#include "api.Mutex.hpp"

namespace local
{
    namespace system
    {
        class Mutex : public system::Object, public api::Mutex
        {
                typedef system::Mutex  Self;
                typedef system::Object Parent;

        public:

            /**
             * Constructor.
             */
            Mutex() : Parent()
            {
                bool const isConstructed = construct();
                setConstructed( isConstructed );
            }

            /**
             * Destructor.
             */
            virtual ~Mutex()
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
             * Locks the mutex.
             *
             * @return true if the mutex is lock successfully.
             */
            virtual bool lock()
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Unlocks the mutex.
             */
            virtual void unlock()
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Tests if this resource is blocked.
             *
             * @return true if this resource is blocked.
             */
            virtual bool isBlocked()const
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

        private:

            /**
             * Constructor.
             *
             * @return true if object has been constructed successfully.
             */
            bool construct()
            {
                if( not Self::isConstructed() ) return false;
                return true;
            }

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Mutex(const Mutex& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Mutex& operator =(const Mutex& obj);

        };
    }
}
#endif // SYSTEM_MUTEX_HPP_
