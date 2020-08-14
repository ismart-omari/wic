/* Copyright (c) 2020 Cameron Harper
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * */

#ifndef WIC_INPUT_POOL_HPP
#define WIC_INPUT_POOL_HPP

#include "mbed.h"
#include "wic_buffer.hpp"

namespace WIC {

    class InputPoolBase {

        public:

            virtual BufferBase *alloc() = 0;
            virtual void free(BufferBase *buf) = 0;
    };

    template<size_t MAX_SIZE>
    class InputPool : public InputPoolBase {

        protected:

            rtos::MemoryPool<Buffer<MAX_SIZE>, 1> pool;

        public:

            BufferBase *alloc()
            {
                return static_cast<BufferBase *>(new(pool.alloc_for(osWaitForever)) Buffer<MAX_SIZE>);                
            }

            void free(BufferBase *buf)
            {
                pool.free(static_cast<Buffer<MAX_SIZE> *>(buf));
            }
            
    };
}

#endif