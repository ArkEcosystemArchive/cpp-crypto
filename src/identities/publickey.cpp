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

////////////////////////////////////////////////////////////////////////////////

// Construct a PublicKey object from a 33-byte PublicKey array.
PublicKey::PublicKey(const PublicKeyBytes &publicKeyBytes)
        : publicKeyBytes_(publicKeyBytes) {}

////////////////////////////////////////////////////////////////////////////////

// Returns a 33-byte Compressed PublicKey array.
auto PublicKey::toBytes() const noexcept -> PublicKeyBytes {
    return this->publicKeyBytes_;
}

////////////////////////////////////////////////////////////////////////////////

// Returns a 32-character Hex-represented-string of a PublicKey.
auto PublicKey::toString() const -> std::string {
    return BytesToHex(this->publicKeyBytes_.begin(),
                      this->publicKeyBytes_.end());
}

////////////////////////////////////////////////////////////////////////////////

// Returns a PublicKey object from a given Passphrase string.
auto PublicKey::fromPassphrase(const char *passphrase) -> PublicKey {
    return PublicKey(
            Keys::PublicKey::fromPrivateKey(
                Keys::PrivateKey::fromPassphrase(passphrase).data()));
}

////////////////////////////////////////////////////////////////////////////////

// Returns a PublicKey object from a 64-char PublicKey Hex string.
auto PublicKey::fromHex(const char *publicKeyHex) -> PublicKey {
    if (strlenSafe(publicKeyHex) != PUBLICKEY_COMPRESSED_STR_LEN) {
        return PublicKey(PublicKeyBytes());
    }

    const auto publicKeyBytes =
            HexToBytesArray<PUBLICKEY_COMPRESSED_LEN>(publicKeyHex);

    return Curve::PublicKey::validate(publicKeyBytes.data())
            ? PublicKey(publicKeyBytes)
            : PublicKey(PublicKeyBytes());
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
