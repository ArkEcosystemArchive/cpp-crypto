/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/keys.hpp"

#include <algorithm>

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"
#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

// Returns KeyPair from a given passphrase.
KeyPair Keys::fromPassphrase(const char* passphrase) {
  return fromPrivateKey(PrivateKey::fromPassphrase(passphrase).data());
}

/**/

// Returns KeyPair from PrivateKey bytes.
KeyPair Keys::fromPrivateKey(const uint8_t* privateKeyBytes) {
  PrivateKeyBytes byteArray {};
  std::copy_n(privateKeyBytes, PRIVATEKEY_BYTE_LEN, byteArray.begin());
  return { byteArray, PublicKey::fromPrivateKey(privateKeyBytes) };
}

/**/ 

// Returns KeyPair from a given WIF string.
KeyPair Keys::fromWif(const char* wif) {
  return fromPrivateKey(Keys::PrivateKey::fromWif(wif, nullptr).data());
}

/**/

// Returns a PrivateKey 32-byte array from a passphrase.
PrivateKeyBytes Keys::PrivateKey::fromPassphrase(
    const char* passphrase) {
  return Hash::sha256(StringToBytes(passphrase).data(), strlenSafe(passphrase));
}

/**/

// Returns a PrivateKey 32-byte array from a 52-char WIF string.
PrivateKeyBytes Keys::PrivateKey::fromWif(const char* wif,
                                          uint8_t* outVersion) {
  return Base58::parseWif(wif, outVersion);
}

/**/

// Returns a 33-byte PublicKey array from a 32-byte PrivateKey.
PublicKeyBytes Keys::PublicKey::fromPrivateKey(
    const uint8_t* privateKeyBytes) {
   return Curve::PublicKey::compute(privateKeyBytes);
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
