/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_SERIALIZER_HPP
#define ARK_TRANSACTIONS_SERIALIZER_HPP

#include <cstdint>
#include <vector>

#include "transactions/transaction_data.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Serializer Options
// Configure whether Signatures should be included during serialization.
struct SerializerOptions {
    ////////////////////////////////////////////////////////////////////////////
    bool excludeSignature;
    bool excludeSecondSignature;
};

////////////////////////////////////////////////////////////////////////////////
// Transaction Serializer Class
class Serializer {
  public:
    ////////////////////////////////////////////////////////////////////////////
    static std::vector<uint8_t> serialize(
            const TransactionData &data,
            const SerializerOptions &options = { false, false });
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
