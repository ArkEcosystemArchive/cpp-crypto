/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef INTERFACE_IDENTITIES_HPP
#define INTERFACE_IDENTITIES_HPP

#include <array>
#include <cstdint>

namespace Ark {
namespace Crypto {

////////// Misc //////////

const size_t BASE58_ALPHABET_LEN  = 58U;
const size_t HASH_20_BYTE_LEN     = 20U;
const size_t HASH_32_BYTE_LEN     = 32U;
const size_t HASH_64_BYTE_LEN     = 64U;

typedef std::array<uint8_t, HASH_32_BYTE_LEN> Hash32;

////////// Identities //////////

// Address
const uint8_t ADDRESS_DEFAULT_VERSION = 0x1e;  // (30) Base58 'D' | Devnet
const size_t  ADDRESS_STRING_LEN      = 34U;

// PubkeyHash
// A 20 Byte Array.
// Used by Ripemd160 as a hash of the PublicKey.
// An Address is derived using a Network Version-byte and a PubkeyHash.
typedef std::array<uint8_t, HASH_20_BYTE_LEN> PubkeyHash;

// PubkeyHashPair
//
// Base58 version byte.
// Ripemd160 PubkeyHash.
struct PubkeyHashPair {
  uint8_t version;
  PubkeyHash pubkeyHash;
};

// Privatekey
const size_t PRIVATEKEY_BYTE_LEN    = 32U;
const size_t PRIVATEKEY_STRING_LEN  = 64U;
typedef std::array<uint8_t, PRIVATEKEY_BYTE_LEN> PrivateKeyBytes;

// PublicKey
const size_t PUBLICKEY_COMPRESSED_BYTE_LEN    = 33U;
const size_t PUBLICKEY_COMPRESSED_STRING_LEN  = 66U;
const size_t PUBLICKEY_UNCOMPRESSED_BYTE_LEN  = 65U;
typedef std::array<uint8_t, PUBLICKEY_COMPRESSED_BYTE_LEN> PublicKeyBytes;
typedef std::array<uint8_t, PUBLICKEY_UNCOMPRESSED_BYTE_LEN> PublicKeyPoint;

// Wif
const size_t WIF_DEFAULT_VERSION  = 0xaa;  // (170) Base58 'S'
const size_t WIF_STRING_LEN       = 52U;

// KeyPair
struct KeyPair {
  PrivateKeyBytes privateKey;
  PublicKeyBytes publicKey;
};

}  // namespace Crypto
}  // namespace Ark

#endif
