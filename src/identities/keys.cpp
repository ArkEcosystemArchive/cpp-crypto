/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/keys.hpp"

#include <utility>

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

////////////////////////////////////////////////////////////////////////////////
// Returns KeyPair from a given passphrase.
auto Keys::fromPassphrase(const char *passphrase) -> KeyPair {
    return fromPrivateKey(PrivateKey::fromPassphrase(passphrase).data());
}

////////////////////////////////////////////////////////////////////////////////
// Returns KeyPair from PrivateKey bytes.
auto Keys::fromPrivateKey(const uint8_t *privateKeyBytes) -> KeyPair {
    PrivateKeyBytes privateKey {};
    std::copy_n(privateKeyBytes,
                PRIVATEKEY_BYTE_LEN,
                privateKey.begin());

    return { privateKey, PublicKey::fromPrivateKey(privateKeyBytes) };
}

////////////////////////////////////////////////////////////////////////////////
// Returns KeyPair from a given WIF string.
auto Keys::fromWif(const char *wif) -> KeyPair {
    return fromPrivateKey(Keys::PrivateKey::fromWif(wif, nullptr).data());
}

////////////////////////////////////////////////////////////////////////////////
// Returns a PrivateKey 32-byte array from a passphrase.
auto Keys::PrivateKey::fromPassphrase(const char *passphrase)
        -> PrivateKeyBytes {
    return Hash::sha256(StringToBytes(passphrase).data(), strlenSafe(passphrase));
}

////////////////////////////////////////////////////////////////////////////////
// Returns a PrivateKey 32-byte array from a 52-char WIF string.
auto Keys::PrivateKey::fromWif(const char *wif,
                               uint8_t *outVersion) -> PrivateKeyBytes {
    return Base58::parseWif(wif, outVersion);
}

////////////////////////////////////////////////////////////////////////////////
// Returns a 33-byte PublicKey array from a 32-byte PrivateKey.
auto Keys::PublicKey::fromPrivateKey(const uint8_t *privateKeyBytes)
        -> PublicKeyBytes {
    return Curve::PublicKey::compute(privateKeyBytes);
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
