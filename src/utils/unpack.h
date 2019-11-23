/********************************************************************************
*
*  Copyright (c) Simon Downey <simon@ark.io> <https://github.com/sleepdefic1t>
*
*  The MIT License (MIT)
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy of
*  this software and associated documentation files (the "Software"), to deal in
*  the Software without restriction, including without limitation the rights to
*  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
*  the Software, and to permit persons to whom the Software is furnished to do so,
*  subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
*  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
*  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
*  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
*  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************/

#ifndef ARK_UTILS_UNPACK_H
#define ARK_UTILS_UNPACK_H

#include <cstdint>

//////////////////////////////////////////////////////////////////////

#define FLAG_1_BYTE     0xFF
#define FLAG_2_BYTE     0xFFFF
#define FLAG_4_BYTE     0xFFFFFFFF
#define FLAG_8_BYTE     0xFFFFFFFFFFFFFFFF

//////////////////////////////////////////////////////////////////////

#define unpack2LE(src, offset)                                                  \
        ((((uint16_t)src[offset]                    & FLAG_1_BYTE)          |   \
          ((uint16_t)src[offset + 1U]               & FLAG_1_BYTE)  << 8U)      \
                                                    & FLAG_2_BYTE)

#define unpack4LE(src, offset)                                                  \
        ((((uint32_t)unpack2LE(src, offset)         & FLAG_2_BYTE)          |   \
          ((uint32_t)unpack2LE(src, offset + 2U)    & FLAG_2_BYTE)  << 16U)     \
                                                    & FLAG_4_BYTE)

#define unpack8LE(src, offset)                                                  \
        ((((uint64_t)unpack4LE(src, offset)         & FLAG_4_BYTE)          |   \
          ((uint64_t)unpack4LE(src, offset + 4U)    & FLAG_4_BYTE)  << 32U)     \
                                                    & FLAG_8_BYTE)

//////////////////////////////////////////////////////////////////////

#endif
