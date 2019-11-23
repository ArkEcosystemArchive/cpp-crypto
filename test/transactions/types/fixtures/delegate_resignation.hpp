/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_DELEGATE_RESIGNATION_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_DELEGATE_RESIGNATION_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////

// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 7,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "2500000000",
//         "amount": "0",
//         "signature": "3045022100aa113ddefb502d868219339d16b8d448c8e69c8e320664e12903cc84420c159d02201b6206c7cb9442f6ef07dd0824aeb0cc393d8f9f9909988da6687c44ef897070",
//         "id": "a8cf10c6a7d2e5c82bff0860f83f917f426bdd1ee25bd8d5dad2358973ce4ecb"
//     },
//     "serialized": "ff02170100000007000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f9029500000000003045022100aa113ddefb502d868219339d16b8d448c8e69c8e320664e12903cc84420c159d02201b6206c7cb9442f6ef07dd0824aeb0cc393d8f9f9909988da6687c44ef897070"
// }

////////////////////////////////////////////////////////////////////////////////

static constexpr const uint8_t TYPE_7_TYPE          = 7U;
static constexpr const uint64_t TYPE_7_FEE          = 2500000000ULL;
static constexpr const uint64_t TYPE_7_VF_LENGTH    = 0U;

// ff02170100000007000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f9029500000000003045022100aa113ddefb502d868219339d16b8d448c8e69c8e320664e12903cc84420c159d02201b6206c7cb9442f6ef07dd0824aeb0cc393d8f9f9909988da6687c44ef897070
static const std::vector<uint8_t> TYPE_7_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   7,   0,   1,   0,  0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10, 104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27, 108, 112, 235, 88,
    231, 240, 174, 209, 146, 0,   249, 2,   149, 0,   0,  0,   0,   0,   48,
    69,  2,   33,  0,   170, 17,  61,  222, 251, 80,  45, 134, 130, 25,  51,
    157, 22,  184, 212, 72,  200, 230, 156, 142, 50,  6,  100, 225, 41,  3,
    204, 132, 66,  12,  21,  157, 2,   32,  27,  98,  6,  199, 203, 148, 66,
    246, 239, 7,   221, 8,   36,  174, 176, 204, 57,  61, 143, 159, 153, 9,
    152, 141, 166, 104, 124, 68,  239, 137, 112, 112 };

// 3045022100aa113ddefb502d868219339d16b8d448c8e69c8e320664e12903cc84420c159d02201b6206c7cb9442f6ef07dd0824aeb0cc393d8f9f9909988da6687c44ef897070
static constexpr const uint8_t TYPE_7_SIGNATURE[] = {
    48, 69,  2,   33,  0,   170, 17,  61,  222, 251, 80, 45, 134, 130, 25,
    51, 157, 22,  184, 212, 72,  200, 230, 156, 142, 50, 6,  100, 225, 41,
    3,  204, 132, 66,  12,  21,  157, 2,   32,  27,  98, 6,  199, 203, 148,
    66, 246, 239, 7,   221, 8,   36,  174, 176, 204, 57, 61, 143, 159, 153,
    9,  152, 141, 166, 104, 124, 68,  239, 137, 112, 112 };

////////////////////////////////////////////////////////////////////////////////

#endif
