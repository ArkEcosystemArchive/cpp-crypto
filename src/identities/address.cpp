/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/address.hpp"

#include <string>

#include "interfaces/identities.hpp"
#include "identities/keys.hpp"
#include "crypto/hash.hpp"
#include "utils/base58.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

// Constructs an Address from a 20-byte PubkeyHash and Address Version.
Address::Address(PubkeyHash pubkeyHash, uint8_t version)
    : pubkeyHash_(pubkeyHash), version_(version) {}

/**/

// Constructs an Address from a 34-character Address string.
Address::Address(const char* addressString) : pubkeyHash_(), version_() {
  if (strlenSafe(addressString) == ADDRESS_STRING_LEN
      && Base58::validate(addressString, ADDRESS_STRING_LEN)) {
    const auto hashPair = Base58::getHashPair(addressString);
    this->pubkeyHash_ = hashPair.pubkeyHash;
    this->version_ = hashPair.version;
  };
}

/**/

// Returns the Base58 Address Version-byte.
uint8_t Address::version() const { return this->version_; }

/**/

// Returns the internal 20-byte Ripemd160 PublicKey Hash.
PubkeyHash Address::toBytes() const { return this->pubkeyHash_; }

/**/

// Returns a 34-character formatted Address string.
std::string Address::toString() const {
  return Base58::parseHash(this->pubkeyHash_.data(), this->version_);
}

/**/

// Returns an Address object from a given Passphrase and Address Version.
Address Address::fromPassphrase(const char* passphrase, uint8_t version) {
  return fromPublicKey(Keys::fromPassphrase(passphrase).publicKey.data(),
                       version);
}

/**/

// Returns an Address object from PublicKey-bytes and an Address Version.
Address Address::fromPublicKey(const uint8_t* publicKeyBytes,
                               uint8_t version) {
  return { Hash::ripemd160(publicKeyBytes), version };
}

/**/

// Returns an Address object from PrivateKey-bytes and an Address Version.
Address Address::fromPrivateKey(const uint8_t* privateKeyBytes,
                                uint8_t version) {
  return fromPublicKey(Keys::fromPrivateKey(privateKeyBytes).publicKey.data(),
                       version);
}

/**/

// Validates an Address object.
bool Address::validate(const Address& address, uint8_t version) {
  auto hashPair = Base58::getHashPair(address.toString().c_str());
  auto pubkeyHash = address.toBytes();

  for (auto i = 0; i < HASH_20_BYTE_LEN; ++i) {
    if (hashPair.pubkeyHash.at(i) != pubkeyHash.at(i)) {
      return false;
    };
  };

  return hashPair.version == version;
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
