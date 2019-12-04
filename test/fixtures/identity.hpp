/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_FIXTURES_IDENTITY_HPP
#define ARK_FIXTURES_IDENTITY_HPP

#include <array>

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace fixtures {  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// ARK Identity Fixtures
//
// {
//    "data": {
//      "privateKey":
//      "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712",
//      "publicKey":
//      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
//      "address": "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
//      "wif": "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA"
//    },
//    "passphrase": "this is a top secret passphrase"
// }
// https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
//

////////////////////////////////////////////////////////////////////////////////
// ARK Identities: Hex Strings
constexpr auto PrivateKeyHex        = "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712";
constexpr auto PublicKeyHex         = "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
constexpr auto AddressString        = "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib";
constexpr auto WifString            = "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA";
constexpr auto Passphrase           = "this is a top secret passphrase";
constexpr auto SecondPassphrase     = "this is a top secret passphrase too";

////////////////////////////////////////////////////////////////////////////////
// ARK Identities: Byte Arrays

////////////////////////////////////////////////////////////////////////////////
const std::array<uint8_t, PRIVATEKEY_BYTE_LEN> PrivateKeyBytes = {
    { 216, 131, 156, 36, 50, 191, 208, 166, 126, 241, 10, 128, 75, 169, 145, 234,
      187, 161, 159, 21, 74, 61, 112, 121, 23, 104, 29, 69, 130, 42, 87, 18 }};

////////////////////////////////////////////////////////////////////////////////
// PublicKeyBytes
const std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN> PublicKeyBytes = {
    {   3, 65, 81, 163, 236, 70, 181, 103, 10, 104, 43, 10, 99, 57, 79, 134, 53,
      135, 209, 188, 151, 72, 59, 27, 108, 112, 235, 88, 231, 240, 174, 209,
      146 }};

////////////////////////////////////////////////////////////////////////////////
// Uncompressed PublicKey Bytes
const std::array<uint8_t, PUBLICKEY_UNCOMPRESSED_LEN> PublicKeyUncompressedBytes = {
    {  65, 81, 163, 236, 70, 181, 103, 10, 104, 43, 10, 99, 57, 79, 134, 53, 135,
      209, 188, 151, 72, 59, 27, 108, 112, 235, 88, 231, 240, 174, 209, 146, 250,
       41, 206, 0, 251, 142, 217, 47, 52, 246, 140, 0, 24, 241, 45, 91, 104, 193,
       96, 144, 128, 171, 175, 51, 23, 70, 214, 216, 108, 96, 57, 229  }};

////////////////////////////////////////////////////////////////////////////////
// RIPEMD160 Hash bytes
const std::array<uint8_t, HASH_20_LEN> AddressBytes = {
    {  9, 149, 117, 2, 7, 236, 175, 12, 207, 37, 28, 18, 101, 185, 42, 216, 79,
      85, 54, 98  }};

////////////////////////////////////////////////////////////////////////////////
// RIPEMD160 Hash bytes
const std::array<uint8_t, 31> PassphraseBytes = {{
    116, 104, 105, 115,  32, 105, 115, 32,  97,  32, 116, 111, 112, 32, 115,
    101,  99, 114, 101, 116,  32, 112, 97, 115, 115, 112, 104, 114, 97, 115, 101
}};

////////////////////////////////////////////////////////////////////////////////
// ARK Identities: Base58 Versions
const uint8_t AddressVersion  = 0x1E;  // Base58: 'D' character
const uint8_t WifVersion      = 0xaa;  // Base58: 'S' character

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ARK Identities: Invalid Fixtures
namespace invalid {

////////////////////////////////////////////////////////////////////////////////
// Invalid characters
// 'h' and 'z' are not valid Hex characters.
constexpr auto PrivateKeyHex    = "d8839c2432bfd0a67ef10ah04ba991eabba19f154a3d707917681d45822a5712";
constexpr auto PublicKeyHex     = "034151a3ec46b5670a682b0a63394f863587d1bcz7483b1b6c70eb58e7f0aed192";

////////////////////////////////////////////////////////////////////////////////
// '0', 'O', 'l', and 'I' are not valid Base58 characters.
constexpr auto AddressString    = "D61mfSggzbvOgTUe6JhYKH2doHaqJ3Dyib";
constexpr auto WifString        = "SGq4xLgZKCGxslbjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA";

////////////////////////////////////////////////////////////////////////////////
// Empty arrays
const std::array<uint8_t, PRIVATEKEY_BYTE_LEN>          PrivateKeyBytes = {{}};
const std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN>     PublicKeyBytes = {{}};

}  // namespace invalid
}  // fixtures
}  // Crypto
}  // Ark

#endif
