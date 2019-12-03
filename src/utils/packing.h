/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_PACKING_H
#define ARK_UTILS_PACKING_H

#include <cstdint>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
const uint8_t U1_MAX        = 0xFF;
const uint16_t U2_MAX       = 0xFFFF;
const uint32_t U4_MAX       = 0xFFFFFFFF;
const uint64_t U8_MAX       = 0xFFFFFFFFFFFFFFFF;

const auto U1_SIZE        = sizeof(uint8_t);
const auto U2_SIZE        = sizeof(uint16_t);
const auto U4_SIZE        = sizeof(uint32_t);
const auto U8_SIZE        = sizeof(uint64_t);

const uint16_t U1_SHIFT     = 8U;
const uint32_t U2_SHIFT     = 16U;
const uint64_t U4_SHIFT     = 32U;

////////////////////////////////////////////////////////////////////////////////
#define pack2LE(dst, src) memcpy (dst, src, U2_SIZE)

////////////////////////////////////////////////////////////////////////////////
#define pack4LE(dst, src) memcpy (dst, src, U4_SIZE)

////////////////////////////////////////////////////////////////////////////////
#define pack8LE(dst, src) memcpy (dst, src, U8_SIZE)

////////////////////////////////////////////////////////////////////////////////
#define unpack2LE(src, offset)                                                              \
    ((((uint16_t)(((src)[(offset)])                         & U1_MAX))                  |   \
     (((uint16_t)(((src)[((offset) + U1_SIZE)])             & U1_MAX)   << U1_SHIFT)))      \
                                                            & U2_MAX)

////////////////////////////////////////////////////////////////////////////////
#define unpack4LE(src, offset)                                                              \
    ((((uint32_t)((unpack2LE((src), (offset)))              & U2_MAX))                  |   \
     (((uint32_t)((unpack2LE((src), ((offset) + U2_SIZE)))  & U2_MAX)   << U2_SHIFT)))      \
                                                            & U4_MAX)

////////////////////////////////////////////////////////////////////////////////
#define unpack8LE(src, offset)                                                              \
    ((((uint64_t)((unpack4LE((src), (offset)))              & U4_MAX))                  |   \
     (((uint64_t)((unpack4LE((src), ((offset) + U4_SIZE)))  & U4_MAX)   << U4_SHIFT)))      \
                                                            & U8_MAX)

#endif
