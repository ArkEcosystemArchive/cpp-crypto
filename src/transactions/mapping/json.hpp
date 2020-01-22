/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_MAPPING_JSON_HPP
#define ARK_TRANSACTIONS_MAPPING_JSON_HPP

#include <map>
#include <string>

#include "transactions/transaction_data.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Transaction Mapping
// Extract a Json-serialized string of a given Transaction map.
struct Json {  // NOLINT
    static std::string fromTransactionMap(const std::map<std::string, std::string> &map);
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif  // #define ARK_TRANSACTIONS_MAPPING_JSON_HPP
