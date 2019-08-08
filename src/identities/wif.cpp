/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/wif.hpp"

#include <string>

#include "interfaces/identities.hpp"
#include "identities/keys.hpp"
#include "utils/base58.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

// Constructs a Wif object using a PrivateKey and Wif Version-byte.
Wif::Wif(PrivateKeyBytes privateKeyBytes, uint8_t version)
    : privateKeyBytes_(privateKeyBytes), version_(version) {}

/**/

// Constructs a Wif object from a 52(+ 1)-char string and Wif Version-byte.
Wif::Wif(const char* wif) : privateKeyBytes_(), version_() {
  if (Base58::validate(wif, WIF_STRING_LEN)) {
    this->privateKeyBytes_ = Keys::PrivateKey::fromWif(wif, &this->version_);
  };
}

/**/

// Returns the Wif Network Version-byte.
uint8_t Wif::version() const { return this->version_; };

/**/

// Returns the Wifs internal privateKey 
PrivateKeyBytes Wif::toBytes() const {
  return this->privateKeyBytes_;
}

/**/

// Returns the 52(+ 1)-char Base58-encoded Wif string.
std::string Wif::toString() const {
  return Base58::getWif(this->privateKeyBytes_.data(), this->version_);
}

/**/

// Returns a Wif object from a Passphrase and Wif Version-byte.
Wif Wif::fromPassphrase(const char* passphrase, uint8_t version) {
  return { Keys::PrivateKey::fromPassphrase(passphrase), version };
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
