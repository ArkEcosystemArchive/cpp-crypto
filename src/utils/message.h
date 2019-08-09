/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "helpers/crypto.h"
#include "helpers/crypto_helpers.h"

#include "identities/privatekey.hpp"
#include "identities/publickey.hpp"

#include "bcl/CurvePoint.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Sha256Hash.hpp"
#include "bcl/Uint256.hpp"

#include <map>
#include <string>
#include <vector>

using namespace Ark::Crypto::identities;

namespace Ark {
namespace Crypto {
namespace Utils {
/**/
class Message {
 public:
  std::string message;
  PublicKey publicKey;
  std::vector<uint8_t> signature;

  Message(std::string msg, PublicKey pubKey, std::vector<uint8_t> sig);
  Message() : publicKey({}) {};

  bool sign(std::string newMessage, const char *const passphrase);
  bool verify() const;

  std::map<std::string, std::string> toArray() const;
  std::string toJson() const;
};
/**/
};  // namespace Utils
};  // namespace Crypto
};  // namespace Ark

#endif
