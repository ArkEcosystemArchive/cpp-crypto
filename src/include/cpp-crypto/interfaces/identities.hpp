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
#include <utility>

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Hash
using Hash32 = std::array<uint8_t, HASH_32_LEN>;

////////////////////////////////////////////////////////////////////////////////
// PubkeyHash
// A 20 Byte Array.
// Used by Ripemd160 as a hash of the PublicKey.
// An Address is derived using a Network Version-byte and a PubkeyHash.
using PubkeyHash = std::array<uint8_t, HASH_20_LEN>;

////////////////////////////////////////////////////////////////////////////////
// PubkeyHashPair
//
// Base58 version byte.
// Ripemd160 PubkeyHash.
struct PubkeyHashPair {
    uint8_t         version     { };
    PubkeyHash      pubkeyHash  { };

    PubkeyHashPair() = default;
    PubkeyHashPair(uint8_t version, const PubkeyHash &pubkeyHash)
        : version(version) {
        std::move(pubkeyHash.begin(),
                  pubkeyHash.end(),
                  this->pubkeyHash.begin());
    }
};

////////////////////////////////////////////////////////////////////////////////
// AddressHash - 21 Bytes
// NetworkVersion + PubkeyHash
//
// ex: 171dfc69b54c7fe901e91d5a9ab78388645e2427ea
using AddressHash = std::array<uint8_t, ADDRESS_HASH_LEN>;

////////////////////////////////////////////////////////////////////////////////
// Privatekey
using PrivateKeyBytes = std::array<uint8_t, PRIVATEKEY_BYTE_LEN>;

////////////////////////////////////////////////////////////////////////////////
// PublicKey
using PublicKeyBytes = std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN>;
using PublicKeyPoint = std::array<uint8_t, PUBLICKEY_UNCOMPRESSED_LEN>;

////////////////////////////////////////////////////////////////////////////////
// KeyPair
struct KeyPair {
    ////////////////////////////////////////////////////////////////////////////
    PrivateKeyBytes     privateKey  { };
    PublicKeyBytes      publicKey   { };

    ////////////////////////////////////////////////////////////////////////////
    KeyPair() = default;
    KeyPair(const PrivateKeyBytes &privateKey, const PublicKeyBytes &publicKey) {
        std::move(privateKey.begin(),
                  privateKey.end(),
                  this->privateKey.begin());

        std::move(publicKey.begin(),
                  publicKey.end(),
                  this->publicKey.begin());
    }
};

}  // namespace Crypto
}  // namespace Ark

#endif
