/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef DEFAULTS_TRANSACTIONS_TYPES_HPP
#define DEFAULTS_TRANSACTIONS_TYPES_HPP

#include <cstdint>

namespace Ark {
namespace Crypto {

enum TransactionTypes : uint8_t {
  Transfer                    = 0,
  SecondSignatureRegistration = 1,
  DelegateRegistration        = 2,
  Vote                        = 3,
  MultiSignatureRegistration  = 4,
  Ipfs                        = 5,
  TimelockTransfer            = 6,
  MultiPayment                = 7,
  DelegateResignation         = 8
};

}  // namespace Crypto
}  // namespace Ark

#endif
