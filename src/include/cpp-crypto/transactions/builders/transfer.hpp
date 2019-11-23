/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_TRANSFER_HPP
#define ARK_TRANSACTIONS_BUILDERS_TRANSFER_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

#include "utils/base58.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////

class Transfer;

////////////////////////////////////////////////////////////////////////////////

class Transfer : public Common<Transfer> {
  public:

////////////////////////////////////////////////////////////////////////////////

    // Amount
    Transfer &amount(uint8_t amount) {
        this->transaction.data.asset.transfer.amount = amount;
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    // Expiration
    Transfer &expiration(uint32_t expiration) {
        this->transaction.data.asset.transfer.expiration = expiration;
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    // RecipientId - uint8_t[21] (network.version + pubkeyHash)
    Transfer &recipientId(const uint8_t *addressHash) {
        memmove(this->transaction.data.asset.transfer.recipientId.data(),
                addressHash,
                ADDRESS_HASH_LEN);
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    // RecipientId - std::string
    Transfer &recipientId(std::string recipientId) {
        const auto hashPair = Base58::getHashPair(recipientId.c_str());
        this->transaction.data.asset.transfer.recipientId.at(0) = hashPair.version;
        memmove(&this->transaction.data.asset.transfer.recipientId.at(1),
                hashPair.pubkeyHash.data(),
                ADDRESS_HASH_LEN);
        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
