/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_IPFS_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_IPFS_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 5,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "500000000",
//         "asset": {
//             "ipfs": "QmYSK2JyM3RyDyB52caZCTKFR3HKniEcMnNJYdk8DQ6KKB"
//         },
//         "signature": "30440220636aa75a15bcc59c9cf2db11ae7f9ed73f112b6ca14cc2aca1b6ed3d2daadaad02207434f5c6d17c98350942afafbaa57b6518ea4e78e8443f414398190183235787",
//         "id": "f68875f1fa80091ef42dec05c5c6a0ea77f4b83934f7eed0d1c72b910ddf6d03"
//     },
//     "serialized": "ff02170100000005000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000012209608184d6cee2b9af8e6c2a46fc9318adf73329aeb8a86cf8472829fff5bb89e30440220636aa75a15bcc59c9cf2db11ae7f9ed73f112b6ca14cc2aca1b6ed3d2daadaad02207434f5c6d17c98350942afafbaa57b6518ea4e78e8443f414398190183235787"
// }

////////////////////////////////////////////////////////////////////////////////
static constexpr const uint8_t TYPE_5_TYPE              = 5U;
static constexpr const uint64_t TYPE_5_FEE              = 500000000ULL;
static constexpr const uint64_t TYPE_5_VF_LENGTH        = 0U;
static constexpr const uint64_t TYPE_5_IPFS_LENGTH      = 34U;

////////////////////////////////////////////////////////////////////////////////
static constexpr const char* TYPE_5_IPFS_LEN_STRING     = "34";
static constexpr const char* TYPE_5_IPFS_STRING         = "QmYSK2JyM3RyDyB52caZCTKFR3HKniEcMnNJYdk8DQ6KKB";

////////////////////////////////////////////////////////////////////////////////
// ff02170100000005000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000012209608184d6cee2b9af8e6c2a46fc9318adf73329aeb8a86cf8472829fff5bb89e30440220636aa75a15bcc59c9cf2db11ae7f9ed73f112b6ca14cc2aca1b6ed3d2daadaad02207434f5c6d17c98350942afafbaa57b6518ea4e78e8443f414398190183235787
static const std::vector<uint8_t> TYPE_5_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   5,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 0,   101, 205, 29,  0,   0,   0,   0,   0,   18,
    32,  150, 8,   24,  77,  108, 238, 43,  154, 248, 230, 194, 164, 111, 201,
    49,  138, 223, 115, 50,  154, 235, 138, 134, 207, 132, 114, 130, 159, 255,
    91,  184, 158, 48,  68,  2,   32,  99,  106, 167, 90,  21,  188, 197, 156,
    156, 242, 219, 17,  174, 127, 158, 215, 63,  17,  43,  108, 161, 76,  194,
    172, 161, 182, 237, 61,  45,  170, 218, 173, 2,   32,  116, 52,  245, 198,
    209, 124, 152, 53,  9,   66,  175, 175, 186, 165, 123, 101, 24,  234, 78,
    120, 232, 68,  63,  65,  67,  152, 25,  1,   131, 35,  87,  135 };

////////////////////////////////////////////////////////////////////////////////
// QmYSK2JyM3RyDyB52caZCTKFR3HKniEcMnNJYdk8DQ6KKB
static constexpr const uint8_t TYPE_5_DAG[] = {
    18,  32,  150, 8,   24,  77,  108, 238, 43,  154, 248, 230,
    194, 164, 111, 201, 49,  138, 223, 115, 50,  154, 235, 138,
    134, 207, 132, 114, 130, 159, 255, 91,  184, 158 };

////////////////////////////////////////////////////////////////////////////////
// 30440220636aa75a15bcc59c9cf2db11ae7f9ed73f112b6ca14cc2aca1b6ed3d2daadaad02207434f5c6d17c98350942afafbaa57b6518ea4e78e8443f414398190183235787
static constexpr const uint8_t TYPE_5_SIGNATURE[] = {
    48,  68,  2,   32,  99,  106, 167, 90,  21,  188, 197, 156, 156, 242,
    219, 17,  174, 127, 158, 215, 63,  17,  43,  108, 161, 76,  194, 172,
    161, 182, 237, 61,  45,  170, 218, 173, 2,   32,  116, 52,  245, 198,
    209, 124, 152, 53,  9,   66,  175, 175, 186, 165, 123, 101, 24,  234,
    78,  120, 232, 68,  63,  65,  67,  152, 25,  1,   131, 35,  87,  135 };

#endif
