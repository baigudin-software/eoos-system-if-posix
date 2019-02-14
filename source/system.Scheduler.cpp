/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Scheduler.hpp" 
#include "system.SchedulerThread.hpp"
#include "system.System.hpp"
#include "system.Interrupt.hpp"

namespace local
{
    namespace system
    {
        /** 
         * Constructor.
         */
        Scheduler::Scheduler() : Parent(),
            globalThread_  (),
            threads_       (NULL){
            setConstructed( construct() );
        }
      
        /** 
         * Destructor.
         */
        Scheduler::~Scheduler()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        bool Scheduler::isConstructed() const
        {
            return Parent::isConstructed();
        }
        
        /**
         * Creates a new thread.
         *
         * @param task an user task which main method will be invoked when created thread is started.
         * @return a new thread.
         */
        api::Thread* Scheduler::createThread(api::Task& task)
        {
            if( not Self::isConstructed() ) return NULL;
            SchedulerThread* thread = new SchedulerThread(task, this);
            if(thread == NULL) return NULL; 
            if(thread->isConstructed()) return thread;  
            delete thread;
            return NULL;
        }
        
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        api::Thread& Scheduler::getCurrentThread() const
        {
            if( not Self::isConstructed() ) 
            {
                System::terminate(ERROR_SYSCALL_CALLED);
            }
            bool const is = Interrupt::disableAll();
            api::Thread* thread = NULL;
            int64 id = -1; // TODO: get a current thread ID static_cast<int64>( gettid() );
            int32 length = threads_.getLength();
            for(int32 i=0; i<length; i++)
            {
                thread = threads_.get(i);
                if(thread == NULL) break;
                if(thread->getId() == id) break;
            }
            if(thread == NULL) 
            {
                System::terminate(ERROR_RESOURCE_NOT_FOUND);
            }
            Interrupt::enableAll(is);
            return *thread;
        }
        
        /**
         * Yields to next thread.
         */
        void Scheduler::yield()
        {
            if( not Self::isConstructed() )
            {
                System::terminate(ERROR_SYSCALL_CALLED);
            }                
            // TODO: sched_yield();
        }
        
        /** 
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */ 
        api::Toggle& Scheduler::toggle()
        {
            return globalThread_;
        }    
    
        /** 
         * Constructor.
         *
         * When first scheduler timer interrupt is occurred, 
         * default registers of parent interrupt class will be used
         * for storing the operating system context to it.
         *
         * @return true if object has been constructed successfully.
         */
        bool Scheduler::construct()
        {
            if( not isConstructed() ) return false;
            if( not globalThread_.isConstructed() ) return false;
            if( not threads_.isConstructed() ) return false;        
            return true;      
        }
        
        /**
         * Adds a thread to execution list
         *
         * @return true if thread has been added successfully.
         */
        bool Scheduler::addThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return false;
            bool const is = Interrupt::disableAll();
            bool res = threads_.add(thread);
            Interrupt::enableAll(is);
            return res;
        }    
        
        /**
         * Removes the first occurrence of the specified thread.
         *
         * @param thread removing thread.
         */
        void Scheduler::removeThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return;
            bool const is = Interrupt::disableAll();
            threads_.removeElement(thread);
            Interrupt::enableAll(is);
        }    
    }
}
