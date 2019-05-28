/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef WIF_H
#define WIF_H

#include "identities/privatekey.h"

#include <cstdint>
#include <string>

namespace Ark {
namespace Crypto {
namespace Identities {
/**/
class WIF {
private:
  uint8_t bytes_[WIF_SIZE] {};

public:
  WIF() : bytes_() {};
  WIF(const char* newWIFStr);
  WIF(const uint8_t* newWIFBytes);

  const uint8_t *toBytes();
  std::string toString() const;

  static WIF fromPassphrase(const char* passphrase, uint8_t wifByte);

  static bool validate(WIF wif);

};
/**/
};  // namespace Identities
};  // namespace Crypto
};  // namespace Ark

#endif
