/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef COMMON_NETWORK_H
#define COMMON_NETWORK_H

#include <cstdint>
#include <string>

namespace Ark {
namespace Crypto {
/**/
// Abstract Network class
//
// Default initialization is ARK Devnet
class Network final {
 public:
  Network();
  Network(std::string nethash,
          uint8_t slip44,
          uint8_t wif,
          uint8_t version,
          std::string epoch)
      : nethash_(std::move(nethash)),
        slip44_(slip44),
        wif_(wif),
        version_(version),
        epoch_(std::move(epoch)) {}

  std::string nethash() const;
  uint8_t slip44() const;
  uint8_t wif() const;
  uint8_t version() const;
  std::string epoch() const;

  bool operator==(const Network& rhs) const;
  bool operator!=(const Network& rhs) const;

 private:
  std::string nethash_;
  uint8_t slip44_;
  uint8_t wif_;
  uint8_t version_;
  std::string epoch_;
};
/**/
}  // namespace Crypto
}  // namespace Ark

#endif
