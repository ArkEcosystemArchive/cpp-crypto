/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_TRANSFER_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_TRANSFER_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 0,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "10000000",
//         "amount": "1",
//         "expiration": 0,
//         "recipientId": "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff",
//         "signature": "3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d",
//         "id": "aafbacad9b75fa664c9cecae6de552833d4c2ab6f857573cf492eafcebfd1551"
//     },
//     "serialized": "ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d"
// }

////////////////////////////////////////////////////////////////////////////////
// {
//     "data": {
//         "version": 2,
//         "network": 23,
//         "type": 0,
//         "nonce": "1",
//         "senderPublicKey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "fee": "10000000",
//         "amount": "1",
//         "vendorFieldHex": "48656c6c6f20576f726c64",
//         "vendorField": "Hello World",
//         "expiration": 0,
//         "recipientId": "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff",
//         "signature": "3045022100a4d816cee480025ff9ae75fd31a8a6abb749a647c50220516e37cd8f79efa1c90220651060f6521b3d0a66b07dc2d0a943f96c9c3c2c6ad42c4396efbe42e6a6823b",
//         "id": "e35888115fccca7b850cd6e47bc67c55d4ad70245953825210ca90c3ae361153",
//     },
//     "serialized": "ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f20576f726c64010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100a4d816cee480025ff9ae75fd31a8a6abb749a647c50220516e37cd8f79efa1c90220651060f6521b3d0a66b07dc2d0a943f96c9c3c2c6ad42c4396efbe42e6a6823b"
// }

////////////////////////////////////////////////////////////////////////////////
static constexpr const uint8_t TYPE_0_TYPE              = 0U;
static constexpr const uint64_t TYPE_0_FEE              = 10000000ULL;
static constexpr const uint64_t TYPE_0_NVF_LENGTH       = 0U;
static constexpr const uint8_t TYPE_0_VF_LENGTH         = 11U;
static constexpr const uint64_t TYPE_0_AMOUNT           = 1ULL;
static constexpr const uint32_t TYPE_0_EXPIRATION       = 0UL;

////////////////////////////////////////////////////////////////////////////////
static constexpr const char* TYPE_0_TYPE_STRING                 = "0";
static constexpr const char* TYPE_0_FEE_STRING                  = "10000000";
static constexpr const char* TYPE_0_AMOUNT_STRING               = "1";
static constexpr const char* TYPE_0_EXPIRATION_STRING           = "0";
static constexpr const char* TYPE_0_RECIPIENT_ID_STRING         = "AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff";
static constexpr const char* TYPE_0_SENDER_SIGNATURE_STRING     = "3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d";
static constexpr const char* TYPE_0_ID_STRING                   = "aafbacad9b75fa664c9cecae6de552833d4c2ab6f857573cf492eafcebfd1551";

////////////////////////////////////////////////////////////////////////////////
// ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d
static const std::vector<uint8_t> TYPE_0_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 128, 150, 152, 0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  29,  252, 105,
    181, 76,  127, 233, 1,   233, 29,  90,  154, 183, 131, 136, 100, 94,  36,
    39,  234, 48,  69,  2,   33,  0,   213, 80,  81,  245, 174, 199, 216, 148,
    175, 185, 135, 213, 130, 230, 62,  1,   87,  183, 166, 224, 203, 142, 255,
    29,  112, 172, 129, 203, 187, 19,  130, 233, 2,   32,  41,  75,  137, 172,
    177, 6,   232, 17,  180, 138, 7,   42,  85,  89,  21,  190, 164, 170, 15,
    198, 60,  66,  16,  173, 144, 17,  93,  18,  32,  179, 27,  125 };

////////////////////////////////////////////////////////////////////////////////
// ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f20576f726c64010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100a4d816cee480025ff9ae75fd31a8a6abb749a647c50220516e37cd8f79efa1c90220651060f6521b3d0a66b07dc2d0a943f96c9c3c2c6ad42c4396efbe42e6a6823b
static const std::vector<uint8_t> TYPE_0_VF_BYTES = {
    255, 2,   23,  1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 128, 150, 152, 0,   0,   0,   0,   0,   11,  72,
    101, 108, 108, 111, 32,  87,  111, 114, 108, 100, 1,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   23,  29,  252, 105, 181, 76,  127, 233,
    1,   233, 29,  90,  154, 183, 131, 136, 100, 94,  36,  39,  234, 48,  69,
    2,   33,  0,   164, 216, 22,  206, 228, 128, 2,   95,  249, 174, 117, 253,
    49,  168, 166, 171, 183, 73,  166, 71,  197, 2,   32,  81,  110, 55,  205,
    143, 121, 239, 161, 201, 2,   32,  101, 16,  96,  246, 82,  27,  61,  10,
    102, 176, 125, 194, 208, 169, 67,  249, 108, 156, 60,  44,  106, 212, 44,
    67,  150, 239, 190, 66,  230, 166, 130, 59 };

////////////////////////////////////////////////////////////////////////////////
// base58Decode(AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff)
static constexpr const uint8_t TYPE_0_RECIPIENT[] = {
    23, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
    90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

////////////////////////////////////////////////////////////////////////////////
// "Hello World"
static constexpr const uint8_t TYPE_0_VF[] = {
    72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100 };

////////////////////////////////////////////////////////////////////////////////
// 3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d
static constexpr const uint8_t TYPE_0_SIGNATURE[] = {
    48,  69,  2,   33,  0,  213, 80,  81,  245, 174, 199, 216, 148, 175, 185,
    135, 213, 130, 230, 62, 1,   87,  183, 166, 224, 203, 142, 255, 29,  112,
    172, 129, 203, 187, 19, 130, 233, 2,   32,  41,  75,  137, 172, 177, 6,
    232, 17,  180, 138, 7,  42,  85,  89,  21,  190, 164, 170, 15,  198, 60,
    66,  16,  173, 144, 17, 93,  18,  32,  179, 27,  125 };

////////////////////////////////////////////////////////////////////////////////
// 3045022100a4d816cee480025ff9ae75fd31a8a6abb749a647c50220516e37cd8f79efa1c90220651060f6521b3d0a66b07dc2d0a943f96c9c3c2c6ad42c4396efbe42e6a6823b
static constexpr const uint8_t TYPE_0_VF_SIGNATURE[] = {
    48,  69,  2,   33,  0,   164, 216, 22,  206, 228, 128, 2,   95,  249, 174,
    117, 253, 49,  168, 166, 171, 183, 73,  166, 71,  197, 2,   32,  81,  110,
    55,  205, 143, 121, 239, 161, 201, 2,   32,  101, 16,  96,  246, 82,  27,
    61,  10,  102, 176, 125, 194, 208, 169, 67,  249, 108, 156, 60,  44,  106,
    212, 44,  67,  150, 239, 190, 66,  230, 166, 130, 59 };

////////////////////////////////////////////////////////////////////////////////
// aafbacad9b75fa664c9cecae6de552833d4c2ab6f857573cf492eafcebfd1551
static constexpr const uint8_t TYPE_0_TX_ID[] = {
    170, 251, 172, 173, 155, 117, 250, 102, 76,  156, 236,
    174, 109, 229, 82,  131, 61,  76,  42,  182, 248, 87,
    87,  60,  244, 146, 234, 252, 235, 253, 21,  81 };

#endif
