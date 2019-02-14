/**
 * The operating system heap memory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_HEAP_HPP_
#define SYSTEM_HEAP_HPP_

#include "system.Object.hpp"
#include "api.Heap.hpp"

namespace local
{
    namespace system
    {
        class Heap : public system::Object, public api::Heap
        {
            typedef system::Heap   Self;
            typedef system::Object Parent;
        
        public:
        
            /** 
             * Constructor.
             */     
            Heap();
    
            /** 
             * Destructor.
             */
            virtual ~Heap();
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool isConstructed() const;

            /**
             * Allocates memory.
             *
             * @param size - required memory size in byte.
             * @param ptr  - NULL value becomes to allocate memory, and 
             *               other given values are simply returned 
             *               as memory address.
             * @return pointer to allocated memory or NULL.
             */    
            virtual void* allocate(size_t size, void* ptr);
            
            /**
             * Frees an allocated memory.
             *
             * @param ptr - pointer to allocated memory.
             */      
            virtual void free(void* ptr);
    
        };
    }
}
#endif // SYSTEM_HEAP_HPP_
