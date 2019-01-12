/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef FEE_H
#define FEE_H

#include "enums/fees.h"
#include "enums/types.h"
using namespace Ark::Crypto::Enums;

#include <cstdint>

namespace Ark {
namespace Crypto {
namespace Configuration {
/**
 * This is the fee configuration class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class Fee {
 private:
  /**
   * @brief The default transaction fees array.
   **/
  uint64_t fees_[9] = {Fees::TRANSFER,
                       Fees::SECOND_SIGNATURE_REGISTRATION,
                       Fees::DELEGATE_REGISTRATION,
                       Fees::VOTE,
                       Fees::MULTI_SIGNATURE_REGISTRATION,
                       Fees::IPFS,
                       Fees::TIMELOCK_TRANSFER,
                       Fees::MULTI_PAYMENT,
                       Fees::DELEGATE_RESIGNATION};
  /**/
 public:
  Fee() = default;
  uint64_t get(int type);
  void set(int type, uint64_t fee);
};
/**/

};  // namespace Configuration
};  // namespace Crypto
};  // namespace Ark

#endif
