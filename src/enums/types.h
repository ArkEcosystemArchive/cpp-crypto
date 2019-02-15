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
/**
 * This is the transaction types class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
enum Types : int {
  TRANSFER = 0,
  SECOND_SIGNATURE_REGISTRATION = 1,
  DELEGATE_REGISTRATION = 2,
  VOTE = 3,
  MULTI_SIGNATURE_REGISTRATION = 4,
  IPFS = 5,
  TIMELOCK_TRANSFER = 6,
  MULTI_PAYMENT = 7,
  DELEGATE_RESIGNATION = 8
};
/**/
};  // namespace Enums
};  // namespace Crypto
};  // namespace Ark

#endif
