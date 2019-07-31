/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/privatekey.hpp"

#include <string>

#include "interfaces/identities.hpp"
#include "identities/keys.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

// Construct a PrivateKey object directly from a 32-byte PrivateKey array.
PrivateKey::PrivateKey(PrivateKeyBytes privateKeyBytes)
    : privateKeyBytes_(privateKeyBytes) {}

/**/

// Returns the 32-byte PrivateKey representation.
PrivateKeyBytes PrivateKey::toBytes() const { return this->privateKeyBytes_; }

/**/

// Returns a 64-character Hex-represented-string of a PrivateKey.
std::string PrivateKey::toString() const {
  return BytesToHex(this->privateKeyBytes_.begin(),
                    this->privateKeyBytes_.end());
}

/**/

// Returns a PrivateKey object from a Passphrase.
PrivateKey PrivateKey::fromPassphrase(const char* passphrase) {
  return Keys::fromPassphrase(passphrase).privateKey;
}

/**/

// Returns a PrivateKey object from a 64-char PrivateKey Hex string.
PrivateKey PrivateKey::fromHex(const char* privateKeyHex) {
  return strlenSafe(privateKeyHex) == PRIVATEKEY_STRING_LEN
            ? HexToBytesArray<>(privateKeyHex)
            : PrivateKey({});
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
