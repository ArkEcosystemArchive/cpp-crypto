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

#include <cassert>
#include <string>
#include "bcl/Base58Check.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Sha256Hash.hpp"
#include "helpers/encoding/hex.h"
#include "helpers/crypto_helpers.h"

namespace Ark {
namespace Crypto {
namespace Identities {

/**
 * This is the private key class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class PrivateKey {
 protected:
  uint8_t bytes_[PRIVATEKEY_SIZE];

 public:
  PrivateKey() : bytes_(){};
  PrivateKey(const char *const newPrivateKeyStr);
  PrivateKey(const uint8_t *newPrivateKeyBytes);

  const uint8_t *toBytes();
  std::string toString() const;

  static PrivateKey fromPassphrase(const char *const passphrase);
  static PrivateKey fromHex(const char *const privateKey);
  static PrivateKey fromWIFString(const char *wifStr, uint8_t wifByte);

  static bool validate(PrivateKey privateKey);
  static bool validate(const char *privateKeyStr);
  static bool validate(const uint8_t *privateKeyBytes);
};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
