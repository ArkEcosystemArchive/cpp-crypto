/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef CRYPTO_MESSAGE_HPP
#define CRYPTO_MESSAGE_HPP

#include <map>
#include <string>
#include <vector>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {

class Message {
 public:
  std::string message;
  PublicKeyBytes publicKey;
  std::vector<uint8_t> signature;

  Message();
  Message(std::string message,
          const PublicKeyBytes& publicKeyBytes,
          std::vector<uint8_t> signature);

  bool sign(const std::string& message, const std::string& passphrase);
  bool verify() const;

  std::map<std::string, std::string> toArray() const;
  std::string toJson() const;
};

}  // namespace Crypto
}  // namespace Ark

#endif
