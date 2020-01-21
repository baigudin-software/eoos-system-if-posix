/**
 * The operating system heap memory.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#include "system.Heap.hpp"
#include "system.Allocator.hpp"

namespace local
{
    namespace system
    {
        /**
         * Constructor.
         */
        Heap::Heap() : Parent()
        {
        }

        /**
         * Destructor.
         */
        Heap::~Heap()
        {
        }

        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */
        bool Heap::isConstructed() const
        {
            return Parent::isConstructed();
        }

        /**
         * Allocates memory.
         *
         * @param size - required memory size in byte.
         * @param ptr  - NULL value becomes to allocate memory, and
         *               other given values are simply returned
         *               as memory address.
         * @return pointer to allocated memory or NULL.
         */
        void* Heap::allocate(size_t const size, void* const ptr)
        {
            void* addr;
            if(ptr == NULL)
            {
                addr = Allocator::allocate(size);
            }
            else
            {
                addr = ptr;
            }
            return addr;
        }

        /**
         * Frees an allocated memory.
         *
         * @param ptr - pointer to allocated memory.
         */
        void Heap::free(void* const ptr)
        {
            Allocator::free(ptr);
        }
    }
}
