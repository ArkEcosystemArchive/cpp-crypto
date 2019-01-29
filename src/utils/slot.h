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

#include "configuration/network.h"

namespace Ark {
namespace Crypto {
namespace Utils {

class Slot {
public:
  static uint64_t epoch(Crypto::Networks::AbstractNetwork network);
  static uint64_t time(Crypto::Networks::AbstractNetwork network);

private:
  static uint64_t now();
};

}  // namespace Utils
}  // namespace Crypto
}  // namespace Ark

#endif
