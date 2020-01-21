/**
 * Runtime system execution.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_RUNTIME_HPP_
#define SYSTEM_RUNTIME_HPP_

#include "system.Object.hpp"
#include "api.Runtime.hpp"
#include "system.Interrupt.hpp"

namespace local
{
    namespace system
    {
        class Runtime : public system::Object, public api::Runtime
        {
            typedef system::Runtime Self;
            typedef system::Object  Parent;

        public:

            /**
             * Constructor.
             */
            Runtime() : Parent()
            {
            }

            /**
             * Destructor.
             */
            virtual ~Runtime()
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
             * Loads a program for executing.
             *
             * @param path a system path to a program.
             * @return true if program has been loaded successfully.
             */
            virtual bool load(const char* path)
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Terminates a system execution.
             *
             * @param status a termination status.
             */
            virtual void exit(int32 const status)
            {
                // ... TODO ...
                bool const is = Interrupt::disableAll();
                volatile bool const isTerminate = true;
                while( isTerminate ){};
                Interrupt::enableAll(is);
            }

        private:

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Runtime(const Runtime& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Runtime& operator =(const Runtime& obj);

        };
    }
}
#endif // SYSTEM_RUNTIME_HPP_
