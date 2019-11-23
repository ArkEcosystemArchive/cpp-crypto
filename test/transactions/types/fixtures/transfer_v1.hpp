/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_TRANSFER_V1_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_TRANSFER_V1_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

namespace v1 {

////////////////////////////////////////////////////////////////////////////////

// {
//     "data": {
//         "version": 1,
//         "network": 23,
//         "type": 0,
//         "timestamp": 83506126,
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "10000000",
//         "amount": "1",
//         "expiration": 0,
//         "recipientId": "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff",
//         "signature": "3045022100f8783a2d1b58271a444e3f39e9f58343c622c15e24dcf982c22a656b6d20a701022052501b5af702bdc59cb90ffea4546e767ca01c4c8f1e07a3483ed96a57eea250",
//         "id": "bf89cf279289ca668d29fbb15ccedb24933f4a4a4c4381a7ef7760634c3a5b89"
//     },
//     "serialized": "ff011700ce33fa04034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100f8783a2d1b58271a444e3f39e9f58343c622c15e24dcf982c22a656b6d20a701022052501b5af702bdc59cb90ffea4546e767ca01c4c8f1e07a3483ed96a57eea250"
// }

////////////////////////////////////////////////////////////////////////////////

// {
//     "data": {
//         "version": 1,
//         "network": 23,
//         "type": 0,
//         "timestamp": 83506245,
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "10000000",
//         "amount": "1",
//         "vendorField": "Hello World",
//         "expiration": 0,
//         "recipientId": "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff",
//         "signature": "304402204209261f274cb4d71b0504a3827d9670ac8cca1cb4aab6b3fc55b0b63a9f03e502205cbb25435d7279e536958cf8fa588c86ebe2a00571073a96a79084906ee0d509",
//         "id": "374ecda42eadb02839ccb7d8fa9d73df8b0b4159dca29248bc38deae0cfd0c69"
//     },
//     "serialized": "ff0117004534fa04034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f20576f726c64010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea304402204209261f274cb4d71b0504a3827d9670ac8cca1cb4aab6b3fc55b0b63a9f03e502205cbb25435d7279e536958cf8fa588c86ebe2a00571073a96a79084906ee0d509"
// }

////////////////////////////////////////////////////////////////////////////////

static constexpr const uint8_t TYPE_0_TYPE              = 0U;
static constexpr const uint32_t TYPE_0_TIMESTAMP        = 83506126UL;
static constexpr const uint32_t TYPE_0_VF_TIMESTAMP     = 83506245;
static constexpr const uint64_t TYPE_0_FEE              = 10000000ULL;
static constexpr const uint64_t TYPE_0_AMOUNT           = 1ULL;
static constexpr const uint32_t TYPE_0_EXPIRATION       = 0UL;

////////////////////////////////////////////////////////////////////////////////

// ff011700ce33fa04034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100f8783a2d1b58271a444e3f39e9f58343c622c15e24dcf982c22a656b6d20a701022052501b5af702bdc59cb90ffea4546e767ca01c4c8f1e07a3483ed96a57eea250
static const std::vector<uint8_t> TYPE_0_BYTES = {
    255, 1,   23,  0,   206, 51,  250, 4,   3,   65,  81,  163, 236, 70,
    181, 103, 10,  104, 43,  10,  99,  57,  79,  134, 53,  135, 209, 188,
    151, 72,  59,  27,  108, 112, 235, 88,  231, 240, 174, 209, 146, 128,
    150, 152, 0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   23,  29,  252, 105, 181, 76,  127, 233,
    1,   233, 29,  90,  154, 183, 131, 136, 100, 94,  36,  39,  234, 48,
    69,  2,   33,  0,   248, 120, 58,  45,  27,  88,  39,  26,  68,  78,
    63,  57,  233, 245, 131, 67,  198, 34,  193, 94,  36,  220, 249, 130,
    194, 42,  101, 107, 109, 32,  167, 1,   2,   32,  82,  80,  27,  90,
    247, 2,   189, 197, 156, 185, 15,  254, 164, 84,  110, 118, 124, 160,
    28,  76,  143, 30,  7,   163, 72,  62,  217, 106, 87,  238, 162, 80 };

// ff0117004534fa04034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f20576f726c64010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea304402204209261f274cb4d71b0504a3827d9670ac8cca1cb4aab6b3fc55b0b63a9f03e502205cbb25435d7279e536958cf8fa588c86ebe2a00571073a96a79084906ee0d509
static const std::vector<uint8_t> TYPE_0_BYTES_VF = {
    255, 1,   23,  0,   69,  52,  250, 4,   3,   65,  81,  163, 236, 70,  181,
    103, 10,  104, 43,  10,  99,  57,  79,  134, 53,  135, 209, 188, 151, 72,
    59,  27,  108, 112, 235, 88,  231, 240, 174, 209, 146, 128, 150, 152, 0,
    0,   0,   0,   0,   11,  72,  101, 108, 108, 111, 32,  87,  111, 114, 108,
    100, 1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  29,
    252, 105, 181, 76,  127, 233, 1,   233, 29,  90,  154, 183, 131, 136, 100,
    94,  36,  39,  234, 48,  68,  2,   32,  66,  9,   38,  31,  39,  76,  180,
    215, 27,  5,   4,   163, 130, 125, 150, 112, 172, 140, 202, 28,  180, 170,
    182, 179, 252, 85,  176, 182, 58,  159, 3,   229, 2,   32,  92,  187, 37,
    67,  93,  114, 121, 229, 54,  149, 140, 248, 250, 88,  140, 134, 235, 226,
    160, 5,   113, 7,   58,  150, 167, 144, 132, 144, 110, 224, 213, 9 };

// "Hello World"
static constexpr const uint8_t TYPE_0_VF[] = {
    72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

// base58Decode(AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff) | 171dfc69b54c7fe901e91d5a9ab78388645e2427ea
static constexpr const uint8_t TYPE_0_RECIPIENT[] = {
    23, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
    90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

// 3045022100f8783a2d1b58271a444e3f39e9f58343c622c15e24dcf982c22a656b6d20a701022052501b5af702bdc59cb90ffea4546e767ca01c4c8f1e07a3483ed96a57eea250
static constexpr const uint8_t TYPE_0_SIGNATURE[] = {
    48,  69,  2,   33,  0,   248, 120, 58, 45,  27,  88,  39,  26,  68,  78,
    63,  57,  233, 245, 131, 67,  198, 34, 193, 94,  36,  220, 249, 130, 194,
    42,  101, 107, 109, 32,  167, 1,   2,  32,  82,  80,  27,  90,  247, 2,
    189, 197, 156, 185, 15,  254, 164, 84, 110, 118, 124, 160, 28,  76,  143,
    30,  7,   163, 72,  62,  217, 106, 87, 238, 162, 80 };

// 3045022100f8783a2d1b58271a444e3f39e9f58343c622c15e24dcf982c22a656b6d20a701022052501b5af702bdc59cb90ffea4546e767ca01c4c8f1e07a3483ed96a57eea250
static constexpr const uint8_t TYPE_0_VF_SIGNATURE[] = {
    48,  68,  2,   32,  66,  9,   38,  31,  39,  76,  180, 215, 27,  5,
    4,   163, 130, 125, 150, 112, 172, 140, 202, 28,  180, 170, 182, 179,
    252, 85,  176, 182, 58,  159, 3,   229, 2,   32,  92,  187, 37,  67,
    93,  114, 121, 229, 54,  149, 140, 248, 250, 88,  140, 134, 235, 226,
    160, 5,   113, 7,   58,  150, 167, 144, 132, 144, 110, 224, 213, 9 };

////////////////////////////////////////////////////////////////////////////////

}  // namespace v1

#endif
