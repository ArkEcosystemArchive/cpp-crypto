/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_SECOND_SIGNATURE_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_SECOND_SIGNATURE_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////

// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 1,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "500000000",
//         "asset": {
//             "signature": {
//                 "publicKey": "02877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9"
//             }
//         },
//         "signature": "304402201786b482215f6f63e3a9414324283decffc64b829209640024a4e78d7ed557f50220197e53c8e8b7f8a645eb82712587926ad930695a8ca43a2308ca0a9dbeabb65b",
//         "id": "6934f7a73846b2daeb94e70b3b8a23118410cb552ada5993bf1b47b10e168916"
//     },
//     "serialized": "ff02170100000001000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000002877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9304402201786b482215f6f63e3a9414324283decffc64b829209640024a4e78d7ed557f50220197e53c8e8b7f8a645eb82712587926ad930695a8ca43a2308ca0a9dbeabb65b"
// }

////////////////////////////////////////////////////////////////////////////////

static constexpr const uint8_t TYPE_1_TYPE              = 1U;
static constexpr const uint64_t TYPE_1_FEE              = 500000000ULL;
static constexpr const uint64_t TYPE_1_VF_LENGTH        = 0U;

////////////////////////////////////////////////////////////////////////////////

static constexpr const char* TYPE_1_PUBLICKEY_STRING    = "02877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9";

////////////////////////////////////////////////////////////////////////////////

// ff02170100000001000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000002877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9304402201786b482215f6f63e3a9414324283decffc64b829209640024a4e78d7ed557f50220197e53c8e8b7f8a645eb82712587926ad930695a8ca43a2308ca0a9dbeabb65b
static const std::vector<uint8_t> TYPE_1_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   1,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 0,   101, 205, 29,  0,   0,   0,   0,   0,   2,
    135, 126, 79,  53,  199, 106, 186, 235, 21,  43,  18,  134, 112, 219, 10,
    122, 225, 11,  57,  153, 175, 205, 40,  164, 41,  56,  182, 83,  251, 248,
    122, 233, 48,  68,  2,   32,  23,  134, 180, 130, 33,  95,  111, 99,  227,
    169, 65,  67,  36,  40,  61,  236, 255, 198, 75,  130, 146, 9,   100, 0,
    36,  164, 231, 141, 126, 213, 87,  245, 2,   32,  25,  126, 83,  200, 232,
    183, 248, 166, 69,  235, 130, 113, 37,  135, 146, 106, 217, 48,  105, 90,
    140, 164, 58,  35,  8,   202, 10,  157, 190, 171, 182, 91 };

// 02877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9
static constexpr const uint8_t TYPE_1_SECOND_PUBLICKEY[] = {
    2,   135, 126, 79,  53, 199, 106, 186, 235, 21,  43,
    18,  134, 112, 219, 10, 122, 225, 11,  57,  153, 175,
    205, 40,  164, 41,  56, 182, 83,  251, 248, 122, 233 };

// 304402201786b482215f6f63e3a9414324283decffc64b829209640024a4e78d7ed557f50220197e53c8e8b7f8a645eb82712587926ad930695a8ca43a2308ca0a9dbeabb65b
static constexpr const uint8_t TYPE_1_SIGNATURE[] = {
    48,  68,  2,   32,  23,  134, 180, 130, 33, 95,  111, 99,  227, 169,
    65,  67,  36,  40,  61,  236, 255, 198, 75, 130, 146, 9,   100, 0,
    36,  164, 231, 141, 126, 213, 87,  245, 2,  32,  25,  126, 83,  200,
    232, 183, 248, 166, 69,  235, 130, 113, 37, 135, 146, 106, 217, 48,
    105, 90,  140, 164, 58,  35,  8,   202, 10, 157, 190, 171, 182, 91 };

////////////////////////////////////////////////////////////////////////////////

#endif
