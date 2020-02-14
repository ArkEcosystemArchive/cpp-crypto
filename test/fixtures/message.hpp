/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef CRYPTO_FIXTURES_MESSAGE_HPP
#define CRYPTO_FIXTURES_MESSAGE_HPP

#include <array>

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace fixtures {  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// ARK Message Fixtures
//
// {
//     "data": {
//         "publickey": "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//         "signature": "304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8",
//         "message": "Hello World"
//     },
//     "passphrase": "this is a top secret passphrase"
// }
// https://raw.githubusercontent.com/ArkEcosystem/swift-crypto/develop/Crypto/CryptoTests/Fixtures/message.json
//

////////////////////////////////////////////////////////////////////////////////
// ARK Message: Strings
constexpr auto MessageString                    = "Hello World";
constexpr auto MessageSignatureString           = "304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8";
constexpr auto MessageSignatureStringSpaces     = "30 44 02 20 0f b4 ad dd d1 f1 d6 52 b5 44 ea 6a b6 28 28 a0 a6 5b 71 2e d4 47 e2 53 8d b0 ca eb fa 68 92 9e 02 20 5e cb 2e 1c 63 b2 98 79 c2 ec f1 25 5d b5 06 d6 71 c8 b3 fa 60 17 f6 7c fd 1b f0 7e 6e dd 1c c8";
constexpr auto MessageJsonString                = R"({"message":"Hello World","publickey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","signature":"304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8"})";

////////////////////////////////////////////////////////////////////////////////
// ARK Message: Bytes
const std::array<uint8_t, 11> MessageBytes = {
    { 72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100 }};

////////////////////////////////////////////////////////////////////////////////
const std::array<uint8_t, HASH_32_LEN> MessageSha256Bytes = {
    { 165, 145, 166, 212, 11, 244, 32, 64, 74, 1, 23, 51, 207, 183, 177, 144,
      214, 44, 101, 191, 11, 205, 163, 43, 87, 178, 119, 217, 173, 159, 20,
      110 }};

////////////////////////////////////////////////////////////////////////////////
const std::array<uint8_t, 70> MessageSignatureBytes = {
    {  48, 68, 2, 32, 15, 180, 173, 221, 209, 241, 214, 82, 181, 68, 234, 106,
      182, 40, 40, 160, 166, 91, 113, 46, 212, 71, 226, 83, 141, 176, 202, 235,
      250, 104, 146, 158, 2, 32, 94, 203, 46, 28, 99, 178, 152, 121, 194, 236,
      241, 37, 93, 181, 6, 214, 113, 200, 179, 250, 96, 23, 246, 124, 253, 27,
      240, 126, 110, 221, 28, 200 }};

}  // fixtures
}  // Crypto
}  // Ark

#endif
