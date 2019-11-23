/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_INTERFACE_IDENTITIES_HPP
#define ARK_INTERFACE_IDENTITIES_HPP

#include <array>
#include <cstdint>

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Hash
typedef std::array<uint8_t, HASH_32_LEN> Hash32;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// PubkeyHash
// A 20 Byte Array.
// Used by Ripemd160 as a hash of the PublicKey.
// An Address is derived using a Network Version-byte and a PubkeyHash.
typedef std::array<uint8_t, HASH_20_LEN> PubkeyHash;

////////////////////////////////////////////////////////////////////////////////

// PubkeyHashPair
//
// Base58 version byte.
// Ripemd160 PubkeyHash.
struct PubkeyHashPair {
    uint8_t version;
    PubkeyHash pubkeyHash;

    PubkeyHashPair() : version(), pubkeyHash() {}
    PubkeyHashPair(const uint8_t version, const PubkeyHash &pubkeyHash)
        : version(version) {
        memmove(this->pubkeyHash.data(), pubkeyHash.data(), HASH_20_LEN);
    }
};

////////////////////////////////////////////////////////////////////////////////

// AddressHash - 21 Bytes
// NetworkVersion + PubkeyHash
//
// ex: 171dfc69b54c7fe901e91d5a9ab78388645e2427ea
typedef std::array<uint8_t, ADDRESS_HASH_LEN> AddressHash;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Privatekey
typedef std::array<uint8_t, PRIVATEKEY_BYTE_LEN> PrivateKeyBytes;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// PublicKey
typedef std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN>   PublicKeyBytes;
typedef std::array<uint8_t, PUBLICKEY_UNCOMPRESSED_LEN> PublicKeyPoint;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// KeyPair
struct KeyPair {
    PrivateKeyBytes privateKey;
    PublicKeyBytes publicKey;

    KeyPair() : privateKey(), publicKey() {}
    KeyPair(const PrivateKeyBytes &privateKey, const PublicKeyBytes &publicKey) {
        memmove(this->privateKey.data(), privateKey.data(), HASH_32_LEN);
        memmove(this->publicKey.data(), publicKey.data(), PUBLICKEY_COMPRESSED_LEN);
    }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}  // namespace Crypto
}  // namespace Ark

#endif
