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

////////////////////////////////////////////////////////////////////////////////
// Construct a PrivateKey object directly from a 32-byte PrivateKey array.
PrivateKey::PrivateKey(const PrivateKeyBytes &privateKeyBytes)
        : privateKeyBytes_(privateKeyBytes) {}

////////////////////////////////////////////////////////////////////////////////
// Returns the 32-byte PrivateKey representation.
auto PrivateKey::toBytes() const noexcept -> PrivateKeyBytes {
    return this->privateKeyBytes_;
}

////////////////////////////////////////////////////////////////////////////////
// Returns a 64-character Hex-represented-string of a PrivateKey.
auto PrivateKey::toString() const -> std::string {
    return BytesToHex(this->privateKeyBytes_.begin(),
                      this->privateKeyBytes_.end());
}

////////////////////////////////////////////////////////////////////////////////
// Returns a PrivateKey object from a Passphrase.
auto PrivateKey::fromPassphrase(const char *passphrase) -> PrivateKey {
    return PrivateKey(Keys::fromPassphrase(passphrase).privateKey);
}

////////////////////////////////////////////////////////////////////////////////
// Returns a PrivateKey object from a 64-char PrivateKey Hex string.
auto PrivateKey::fromHex(const char *privateKeyHex) -> PrivateKey {
    return strlenSafe(privateKeyHex) == PRIVATEKEY_STRING_LEN
            ? PrivateKey(HexToBytesArray<>(privateKeyHex))
            : PrivateKey(PrivateKeyBytes());
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
