/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef FEES_H
#define FEES_H

#include <cstdint>

namespace Ark {
namespace Crypto {
namespace Enums {
/**/
struct Fees {
  static const uint64_t TRANSFER = 10000000ULL;
  static const uint64_t SECOND_SIGNATURE_REGISTRATION = 500000000ULL;
  static const uint64_t DELEGATE_REGISTRATION = 2500000000ULL;
  static const uint64_t VOTE = 100000000ULL;
  static const uint64_t MULTI_SIGNATURE_REGISTRATION = 500000000ULL;
  static const uint64_t IPFS = 0ULL;
  static const uint64_t TIMELOCK_TRANSFER = 0ULL;
  static const uint64_t MULTI_PAYMENT = 0ULL;
  static const uint64_t DELEGATE_RESIGNATION = 0ULL;
};
/**/
};  // namespace Enums
};  // namespace Crypto
};  // namespace Ark

#endif
