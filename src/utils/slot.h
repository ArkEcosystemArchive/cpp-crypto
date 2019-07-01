/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILITIES_SLOTS_H
#define ARK_UTILITIES_SLOTS_H

#include <cstdint>

#include "common/network.hpp"

namespace Ark {
namespace Crypto {
namespace Utils {
/**/
class Slot {
public:
  static uint64_t epoch(const Network& network);
  static uint64_t time(const Network& network);

private:
  static uint64_t now();
};
/**/
};  // namespace Utils
};  // namespace Crypto
};  // namespace Ark

#endif
