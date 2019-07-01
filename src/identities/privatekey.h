/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef PRIVATEKEY_H
#define PRIVATEKEY_H

#include "helpers/crypto_helpers.h"

#include <cstdint>
#include <string>

namespace Ark {
namespace Crypto {
namespace Identities {
/**/
class PrivateKey {
private:
  uint8_t bytes_[PRIVATEKEY_SIZE] {};

public:
  PrivateKey() : bytes_() {};
  PrivateKey(const char* newPrivateKeyStr);
  PrivateKey(const uint8_t* newPrivateKeyBytes);

  const uint8_t *toBytes();
  std::string toString() const;

  static PrivateKey fromPassphrase(const char* passphrase);
  static PrivateKey fromHex(const char* privateKey);
  static PrivateKey fromWIFString(const char* wifStr, uint8_t wifByte);

  static bool validate(PrivateKey privateKey);
  static bool validate(const char* privateKeyStr);
  static bool validate(const uint8_t* privateKeyBytes);
};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
