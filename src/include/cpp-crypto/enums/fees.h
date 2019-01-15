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
/**
 * This is the transaction fees class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
struct Fees {
 public:
  static const uint64_t TRANSFER = 10000000;
  static const uint64_t SECOND_SIGNATURE_REGISTRATION = 500000000;
  static const uint64_t DELEGATE_REGISTRATION = 2500000000;
  static const uint64_t VOTE = 100000000;
  static const uint64_t MULTI_SIGNATURE_REGISTRATION = 500000000;
  static const uint64_t IPFS = 0;
  static const uint64_t TIMELOCK_TRANSFER = 0;
  static const uint64_t MULTI_PAYMENT = 0;
  static const uint64_t DELEGATE_RESIGNATION = 0;
};
/**/
};  // namespace Enums
};  // namespace Crypto
};  // namespace Ark

#endif
