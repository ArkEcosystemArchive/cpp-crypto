/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include "helpers/encoding/hex.h"
#include "helpers/crypto_helpers.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"

namespace Ark {
namespace Crypto {
namespace Identities {

/**
 * This is the address class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class Address {
 protected:
  uint8_t bytes_[ADDRESS_LENGTH];

 public:
  Address() : bytes_(){};
  Address(const char *const newAddressStr);
  Address(const uint8_t *newAddressBytes);

  const uint8_t *toBytes();
  std::string toString() const;

  static Address fromPassphrase(const char *const passphrase, uint8_t networkVersion);
  static Address fromPrivateKey(PrivateKey privateKey, uint8_t networkVersion);
  static Address fromPublicKey(PublicKey publicKey, uint8_t networkVersion);

  static bool validate(Address address, uint8_t networkVersion);
  static bool validate(const char *const addressStr, uint8_t networkVersion);
  static bool validate(const uint8_t *addressBytes, uint8_t networkVersion);
  static std::string base58encode(const uint8_t *source);
  static std::vector<uint8_t> bytesFromBase58Check(const char *const address);
};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
