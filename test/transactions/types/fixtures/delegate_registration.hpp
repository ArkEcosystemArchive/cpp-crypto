/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_DELEGATE_REGISTRATION_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_DELEGATE_REGISTRATION_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 2,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "2500000000",
//         "asset": {
//             "delegate": {
//                 "username": "arkdelegate"
//             }
//         },
//         "signature": "30440220281812ca558b3b032aaf724aeaba5e20733e87f20fefe1c78536cc523de7e475022038a2454ca2665f6c3d910b04ecdd5995a7d82904f9f4bf878402a31262d2db61",
//         "id": "668f5db0d99189ee7dd85c991360ca19372302a13e3046511a60d115dbf1864e"
//     },
//     'serialized': "ff02170100000002000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f9029500000000000b61726b64656c656761746530440220281812ca558b3b032aaf724aeaba5e20733e87f20fefe1c78536cc523de7e475022038a2454ca2665f6c3d910b04ecdd5995a7d82904f9f4bf878402a31262d2db61"
// }

////////////////////////////////////////////////////////////////////////////////
constexpr uint8_t TYPE_2_TYPE               = 2U;
constexpr uint64_t TYPE_2_FEE               = 2500000000ULL;
constexpr uint64_t TYPE_2_VF_LENGTH         = 0U;
constexpr uint64_t TYPE_2_USERNAME_LENGTH   = 11U;

////////////////////////////////////////////////////////////////////////////////
constexpr auto TYPE_2_USERNAME_LEN_STRING   = "11";
constexpr auto TYPE_2_USERNAME_STRING       = "arkdelegate";

////////////////////////////////////////////////////////////////////////////////
// ff02170100000002000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f9029500000000000b61726b64656c656761746530440220281812ca558b3b032aaf724aeaba5e20733e87f20fefe1c78536cc523de7e475022038a2454ca2665f6c3d910b04ecdd5995a7d82904f9f4bf878402a31262d2db61
const std::vector<uint8_t> TYPE_2_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   2,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 0,   249, 2,   149, 0,   0,   0,   0,   0,   11,
    97,  114, 107, 100, 101, 108, 101, 103, 97,  116, 101, 48,  68,  2,   32,
    40,  24,  18,  202, 85,  139, 59,  3,   42,  175, 114, 74,  234, 186, 94,
    32,  115, 62,  135, 242, 15,  239, 225, 199, 133, 54,  204, 82,  61,  231,
    228, 117, 2,   32,  56,  162, 69,  76,  162, 102, 95,  108, 61,  145, 11,
    4,   236, 221, 89,  149, 167, 216, 41,  4,   249, 244, 191, 135, 132, 2,
    163, 18,  98,  210, 219, 97 };

////////////////////////////////////////////////////////////////////////////////
// "arkdelegate"
constexpr uint8_t TYPE_2_USERNAME[] = {
    97, 114, 107, 100, 101, 108, 101, 103, 97, 116, 101 };

////////////////////////////////////////////////////////////////////////////////
// 30440220281812ca558b3b032aaf724aeaba5e20733e87f20fefe1c78536cc523de7e475022038a2454ca2665f6c3d910b04ecdd5995a7d82904f9f4bf878402a31262d2db61
constexpr uint8_t TYPE_2_SIGNATURE[] = {
    48,  68,  2,   32,  40,  24,  18,  202, 85,  139, 59, 3,   42,  175,
    114, 74,  234, 186, 94,  32,  115, 62,  135, 242, 15, 239, 225, 199,
    133, 54,  204, 82,  61,  231, 228, 117, 2,   32,  56, 162, 69,  76,
    162, 102, 95,  108, 61,  145, 11,  4,   236, 221, 89, 149, 167, 216,
    41,  4,   249, 244, 191, 135, 132, 2,   163, 18,  98, 210, 219, 97 };

#endif
