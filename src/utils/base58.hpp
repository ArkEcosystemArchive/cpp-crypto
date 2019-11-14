/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef UTILS_BASE58_HPP
#define UTILS_BASE58_HPP

#include "interfaces/identities.hpp"

#include <string>
#include <cstdint>

namespace Ark {
namespace Crypto {

struct Base58 {
  static PubkeyHashPair getHashPair(const char* address);
  static std::string parseHash(const uint8_t* pubkeyHash, uint8_t version);
  static std::string getWif(const uint8_t* privateKeyBytes, uint8_t version);
  static PrivateKeyBytes parseWif(const char* wif, uint8_t* outVersion);

  static bool validate(const char* str, size_t size);
};

}  // namespace Crypto
}  // namespace Ark

#endif
