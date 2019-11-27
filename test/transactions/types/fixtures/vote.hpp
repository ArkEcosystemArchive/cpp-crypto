/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_VOTE_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_VOTE_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 3,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "100000000",
//         "asset": {
//             "votes": [
//                 "+034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192"
//             ]
//         },
//         "signature": "3045022100dfa4edd1fb7bc587eb277dd996ab0dde73dc4942a293e5634bd48be9c7d25880022025c91f30c88f49bc3ed77614749c0c439f0759457a4bf22ed5c97f338659ccee",
//         "id": "ca544581927728ae03a63f088e76053f357dc8fb0422512bb8a7c6a0f7ae16cf"
//     },
//     "serialized": "ff02170100000003000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200e1f50500000000000101034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1923045022100dfa4edd1fb7bc587eb277dd996ab0dde73dc4942a293e5634bd48be9c7d25880022025c91f30c88f49bc3ed77614749c0c439f0759457a4bf22ed5c97f338659ccee"
// }

////////////////////////////////////////////////////////////////////////////////
constexpr uint8_t TYPE_3_TYPE           = 3U;
constexpr uint64_t TYPE_3_FEE           = 100000000ULL;
constexpr uint8_t TYPE_3_VOTE_COUNT     = 1U;

////////////////////////////////////////////////////////////////////////////////
constexpr auto TYPE_3_VOTES_STRING = "+034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";

////////////////////////////////////////////////////////////////////////////////
// ff02170100000003000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200e1f50500000000000101034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1923045022100dfa4edd1fb7bc587eb277dd996ab0dde73dc4942a293e5634bd48be9c7d25880022025c91f30c88f49bc3ed77614749c0c439f0759457a4bf22ed5c97f338659ccee
const std::vector<uint8_t> TYPE_3_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   3,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 0,   225, 245, 5,   0,   0,   0,   0,   0,   1,
    1,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,  57,
    79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,  231,
    240, 174, 209, 146, 48,  69,  2,   33,  0,   223, 164, 237, 209, 251, 123,
    197, 135, 235, 39,  125, 217, 150, 171, 13,  222, 115, 220, 73,  66,  162,
    147, 229, 99,  75,  212, 139, 233, 199, 210, 88,  128, 2,   32,  37,  201,
    31,  48,  200, 143, 73,  188, 62,  215, 118, 20,  116, 156, 12,  67,  159,
    7,   89,  69,  122, 75,  242, 46,  213, 201, 127, 51,  134, 89,  204, 238 };

////////////////////////////////////////////////////////////////////////////////
// +034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192
constexpr uint8_t TYPE_3_VOTE[] = {
    1,  3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,
    10, 99,  57,  79,  134, 53,  135, 209, 188, 151, 72,  59,
    27, 108, 112, 235, 88,  231, 240, 174, 209, 146 };

////////////////////////////////////////////////////////////////////////////////
// 3045022100dfa4edd1fb7bc587eb277dd996ab0dde73dc4942a293e5634bd48be9c7d25880022025c91f30c88f49bc3ed77614749c0c439f0759457a4bf22ed5c97f338659ccee
constexpr uint8_t TYPE_3_SIGNATURE[] = {
    48,  69,  2,   33,  0,   223, 164, 237, 209, 251, 123, 197, 135, 235, 39,
    125, 217, 150, 171, 13,  222, 115, 220, 73,  66,  162, 147, 229, 99,  75,
    212, 139, 233, 199, 210, 88,  128, 2,   32,  37,  201, 31,  48,  200, 143,
    73,  188, 62,  215, 118, 20,  116, 156, 12,  67,  159, 7,   89,  69,  122,
    75,  242, 46,  213, 201, 127, 51,  134, 89,  204, 238 };

#endif