/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Interrupt.hpp"

namespace local
{ 
    namespace system
    {
        /**
         * Constructor.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.   
         * @param source  available interrupt source.
         */
        Interrupt::Interrupt(api::Task& handler, int32 source) : Parent()
        {
            bool const isConstructed = construct(&handler, source);
            setConstructed( isConstructed );
        }
        
        /**
         * Destructor.
         */
        Interrupt::~Interrupt()
        {
        }
        
        /**
         * Constructor.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.   
         * @param source  available interrupt source.
         * @return true if object has been constructed successfully.
         */
        bool Interrupt::construct(api::Task* handler, int32 source)
        {
            if( not Self::isConstructed() ) return false;
            return true;
        }
      
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        bool Interrupt::isConstructed() const
        {
            return Parent::isConstructed();
        }
        
        /**
         * Jumps to interrupt HW vector.
         */  
        void Interrupt::jump()
        {
        }
        
        /**
         * Clears an interrupt status of this source.
         */  
        void Interrupt::clear()
        {
        }
        
        /**
         * Sets an interrupt status of this source.
         */  
        void Interrupt::set()
        {
        }  
        
        /**
         * Locks this interrupt source.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        bool Interrupt::disable()
        {
            return false;
        }
        
        /**
         * Unlocks this interrupt source.
         *
         * @param status returned status by disable method.
         */
        void Interrupt::enable(bool status)
        {
        }
        
        /**
         * Disables all maskable interrupts.
         *
         * @return global interrupts enable bit value before method was called.
         */
        bool Interrupt::disableAll()
        {
            return false;
        }
        
        /**
         * Enables all maskable interrupts.
         *
         * The true passed argument directly turns all maskable interrupts on, 
         * and the false does nothing, the interrupts stay in the current state.     
         *
         * @param status the returned status by disable method.
         */
        void Interrupt::enableAll(bool status)
        {
        }

    }
}
