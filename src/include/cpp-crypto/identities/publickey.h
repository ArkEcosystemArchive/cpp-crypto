/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef PUBLICKEY_H
#define PUBLICKEY_H

#include <string>
#include "helpers/encoding/hex.h"
#include "helpers/crypto_helpers.h"
#include "identities/privatekey.h"

namespace Ark {
namespace Crypto {
namespace Identities {
/**
 * This is the public key class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class PublicKey {
 protected:
  uint8_t bytes_[COMPRESSED_PUBLICKEY_SIZE];

 public:
  PublicKey() : bytes_(){};
  PublicKey(const char *const newPublicKeyStr);
  PublicKey(const uint8_t *newPublicKeyBytes);

  const uint8_t *toBytes();

  bool isValid();
  std::string toString() const;

  static PublicKey fromPassphrase(const char *const passphrase);
  static PublicKey fromPrivateKey(PrivateKey privateKey);
  static PublicKey fromHex(const char *const publicKey);

  static bool validate(PublicKey publicKey);
  static bool validate(const char *publicKeyStr);
  static bool validate(const uint8_t *publicKeyBytes);
};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
