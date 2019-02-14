/** 
 * Hardware global interrupts resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_GLOBAL_INTERRUPT_HPP_
#define SYSTEM_GLOBAL_INTERRUPT_HPP_
    
#include "system.Object.hpp"
#include "api.Toggle.hpp"

namespace local
{
    namespace system
    {
        class GlobalInterrupt : public system::Object, public api::Toggle
        {
            typedef system::GlobalInterrupt Self;
            typedef system::Object          Parent;
        
        public:
          
            /** 
             * Constructor.
             */
            GlobalInterrupt() : Parent()
            {
            }  
            
            /** 
             * Destructor.
             */                               
            virtual ~GlobalInterrupt()
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
            GlobalInterrupt(const GlobalInterrupt& obj);
          
            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.     
             */
            GlobalInterrupt& operator =(const GlobalInterrupt& obj);    

        }; 
    }
}
#endif // SYSTEM_GLOBAL_INTERRUPT_HPP_
