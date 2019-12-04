/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_MAPPING_HPP
#define ARK_TRANSACTIONS_MAPPING_HPP

#include <map>
#include <string>

#include "transactions/transaction_data.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Transaction Mapping
//
// Derive a Map<string, string> of a given Transaction's data.
// Derive a Json-serialized string of a given Transaction's data.
//
//--
struct Mapping {
    ////////////////////////////////////////////////////////////////////////////
    static std::map<std::string, std::string> getMap(
            const TransactionData &data);

    ////////////////////////////////////////////////////////////////////////////
    static std::string toJson(const std::map<std::string, std::string> &map);
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
