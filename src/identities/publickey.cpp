/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/publickey.hpp"

#include <string>

#include "interfaces/identities.hpp"
#include "identities/keys.hpp"
#include "crypto/curve.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

// Construct a PublicKey object from a 33-byte PublicKey array.
PublicKey::PublicKey(const PublicKeyBytes publicKeyBytes)
    : publicKeyBytes_(publicKeyBytes) {}

/**/

// Returns a 33-byte Compressed PublicKey array.
PublicKeyBytes PublicKey::toBytes() const { return this->publicKeyBytes_; }

/**/

// Returns a 32-character Hex-represented-string of a PublicKey.
std::string PublicKey::toString() const {
  return BytesToHex(this->publicKeyBytes_.begin(),
                    this->publicKeyBytes_.end());
}

/**/

// Returns a PublicKey object from a given Passphrase string.
PublicKey PublicKey::fromPassphrase(const char* passphrase) {
  return PublicKey(Keys::PublicKey::fromPrivateKey(
      Keys::PrivateKey::fromPassphrase(passphrase).data()));
}

/**/

// Returns a PublicKey object from a 64-char PublicKey Hex string.
PublicKey PublicKey::fromHex(const char* publicKeyHex) {
  if (strlenSafe(publicKeyHex) != PUBLICKEY_COMPRESSED_STRING_LEN) {
    return PublicKey({});
  };

  const auto publicKeyBytes =
      HexToBytesArray<PUBLICKEY_COMPRESSED_BYTE_LEN>(publicKeyHex);

  return Curve::PublicKey::validate(publicKeyBytes.data())
            ? PublicKey(publicKeyBytes)
            : PublicKey({});
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
