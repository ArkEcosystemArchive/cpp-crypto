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

#include "identities/privatekey.h"
#include "identities/publickey.h"

#include "helpers/crypto_helpers.h"

#include <cstdint>
#include <string>

namespace Ark {
namespace Crypto {
namespace Identities {
/**/
class PublicKey {
private:
  uint8_t bytes_[COMPRESSED_PUBLICKEY_SIZE] {};

public:
  PublicKey() : bytes_() {};
  PublicKey(const char* newPublicKeyStr);
  PublicKey(const uint8_t* newPublicKeyBytes);

  const uint8_t *toBytes();

  bool isValid();
  std::string toString() const;

  static PublicKey fromPassphrase(const char* passphrase);
  static PublicKey fromPrivateKey(PrivateKey privateKey);
  static PublicKey fromHex(const char* publicKey);

  static bool validate(PublicKey publicKey);
  static bool validate(const char* publicKeyStr);
  static bool validate(const uint8_t* publicKeyBytes);
};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
