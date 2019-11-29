/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_HTLC_LOCK_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_HTLC_LOCK_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "typeGroup": 1,
//         "type": 8,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "10000000",
//         "amount": "1",
//         "recipientId": "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff",
//         "asset": {
//             "lock": {
//                 "secretHash": "09b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c",
//                 "expiration": {
//                     "type": 1,
//                     "value": 81242895
//                 }
//             }
//         },
//         "signature": "3044022034491f6ee88278248c3b0ddd62b7ee0cb68e0ff93a51008899240b32d111b90a022043b10dd604f2d6256c75e50b5423612824a971c1876528af983ebb8145403e86",
//         "id": "50f301306d8da58d62332ce3a361d9fd4a01b0a89ca914517b685e2d3714e24e"
//     },
//     "serialized": "ff02170100000008000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000009b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c010fabd704171dfc69b54c7fe901e91d5a9ab78388645e2427ea3044022034491f6ee88278248c3b0ddd62b7ee0cb68e0ff93a51008899240b32d111b90a022043b10dd604f2d6256c75e50b5423612824a971c1876528af983ebb8145403e86"
// }

////////////////////////////////////////////////////////////////////////////////
constexpr uint8_t TYPE_8_TYPE                   = 8U;
constexpr uint64_t TYPE_8_FEE                   = 10000000ULL;
constexpr uint64_t TYPE_8_AMOUNT                = 1ULL;
constexpr uint8_t TYPE_8_EXPIRATION_TYPE        = 1ULL;
constexpr uint32_t TYPE_8_EXPIRATION_VALUE      = 81242895UL;
constexpr uint64_t TYPE_8_VF_LENGTH             = 0U;

////////////////////////////////////////////////////////////////////////////////
constexpr auto TYPE_8_AMOUNT_STRING             = "1";
constexpr auto TYPE_8_SECRET_STRING             = "09b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c";
constexpr auto TYPE_8_EXPIRATION_TYPE_STRING    = "1";
constexpr auto TYPE_8_EXPIRATION_VALUE_STRING   = "81242895";
constexpr auto TYPE_8_RECIPIENT_STRING          = "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff";

////////////////////////////////////////////////////////////////////////////////
// ff02170100000008000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000009b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c010fabd704171dfc69b54c7fe901e91d5a9ab78388645e2427ea3044022034491f6ee88278248c3b0ddd62b7ee0cb68e0ff93a51008899240b32d111b90a022043b10dd604f2d6256c75e50b5423612824a971c1876528af983ebb8145403e86
const std::vector<uint8_t> TYPE_8_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   8,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 128, 150, 152, 0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   9,   185, 162, 131, 147, 239, 208, 47,
    205, 118, 162, 27,  15,  15,  85,  186, 42,  173, 143, 54,  64,  255, 140,
    174, 134, 222, 3,   58,  156, 251, 215, 140, 1,   15,  171, 215, 4,   23,
    29,  252, 105, 181, 76,  127, 233, 1,   233, 29,  90,  154, 183, 131, 136,
    100, 94,  36,  39,  234, 48,  68,  2,   32,  52,  73,  31,  110, 232, 130,
    120, 36,  140, 59,  13,  221, 98,  183, 238, 12,  182, 142, 15,  249, 58,
    81,  0,   136, 153, 36,  11,  50,  209, 17,  185, 10,  2,   32,  67,  177,
    13,  214, 4,   242, 214, 37,  108, 117, 229, 11,  84,  35,  97,  40,  36,
    169, 113, 193, 135, 101, 40,  175, 152, 62,  187, 129, 69,  64,  62,  134 };

////////////////////////////////////////////////////////////////////////////////
// 09b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c
constexpr uint8_t TYPE_8_SECRET_HASH[] = {
    9,   185, 162, 131, 147, 239, 208, 47,  205, 118, 162,
    27,  15,  15,  85,  186, 42,  173, 143, 54,  64,  255,
    140, 174, 134, 222, 3,   58,  156, 251, 215, 140 };

////////////////////////////////////////////////////////////////////////////////
// base58Decode(AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff)
constexpr uint8_t TYPE_8_RECIPIENT[] = {
    23, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
    90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

////////////////////////////////////////////////////////////////////////////////
// 3044022034491f6ee88278248c3b0ddd62b7ee0cb68e0ff93a51008899240b32d111b90a022043b10dd604f2d6256c75e50b5423612824a971c1876528af983ebb8145403e86
constexpr uint8_t TYPE_8_SIGNATURE[] = {
    48,  68,  2,   32,  52,  73,  31,  110, 232, 130, 120, 36,  140, 59,
    13,  221, 98,  183, 238, 12,  182, 142, 15,  249, 58,  81,  0,   136,
    153, 36,  11,  50,  209, 17,  185, 10,  2,   32,  67,  177, 13,  214,
    4,   242, 214, 37,  108, 117, 229, 11,  84,  35,  97,  40,  36,  169,
    113, 193, 135, 101, 40,  175, 152, 62,  187, 129, 69,  64,  62,  134 };

#endif
