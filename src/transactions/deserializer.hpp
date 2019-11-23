/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_DESERIALIZER_HPP
#define ARK_TRANSACTIONS_DESERIALIZER_HPP

#include <cstdbool>
#include <cstdint>
#include <vector>

#include "transactions/transaction_data.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

class Deserializer {
    public:
      static bool deserialize(TransactionData *data, const std::vector<uint8_t> &buffer);
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
