/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef TYPES_H
#define TYPES_H

namespace Ark {
namespace Crypto {
namespace Enums {
/**/
enum Types : unsigned {
  TRANSFER = 0U,
  SECOND_SIGNATURE_REGISTRATION = 1U,
  DELEGATE_REGISTRATION = 2U,
  VOTE = 3U,
  MULTI_SIGNATURE_REGISTRATION = 4U,
  IPFS = 5U,
  TIMELOCK_TRANSFER = 6U,
  MULTI_PAYMENT = 7U,
  DELEGATE_RESIGNATION = 8U
};
/**/
};  // namespace Enums
};  // namespace Crypto
};  // namespace Ark

#endif
