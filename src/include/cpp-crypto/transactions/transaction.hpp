/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTION_HPP
#define ARK_TRANSACTION_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "interfaces/identities.hpp"

#include "transactions/transaction_data.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

class Transaction {
  public:
    Transaction() : data() {};

    Hash32 getId() const;

    bool sign(const std::string &passphrase);
    bool secondSign(const std::string &secondPassphrase);

    bool verify() const;

    bool secondVerify(const uint8_t *secondPublicKey) const;

    bool deserialize(const std::vector<uint8_t> &serialized);
    std::vector<uint8_t> serialize();

    std::vector<uint8_t> toBytes(bool excludeSignature = false,
                                 bool excludeSecondSignature = false) const;

    std::map<std::string, std::string> toMap() const;

    std::string toJson() const;

    TransactionData data;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
