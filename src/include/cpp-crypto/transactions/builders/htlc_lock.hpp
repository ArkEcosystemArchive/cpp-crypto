/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_HTLC_LOCK_HPP
#define ARK_TRANSACTIONS_BUILDERS_HTLC_LOCK_HPP

#include <algorithm>
#include <cstdint>
#include <string>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

#include "utils/base58.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class HtlcLock;

////////////////////////////////////////////////////////////////////////////////
class HtlcLock : public Common<HtlcLock> {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Amount
    HtlcLock &amount(uint64_t amount) {
        this->transaction.data.asset.htlcLock.amount = amount;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Secret Hash
    HtlcLock &secretHash(const uint8_t *secretHash) {
        std::copy_n(secretHash,
                    HASH_32_LEN,
                    this->transaction.data.asset.htlcLock.secretHash.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Expiration Type
    HtlcLock &expirationType(uint8_t expirationType) {
        this->transaction.data.asset.htlcLock.expirationType = expirationType;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Expiration
    HtlcLock &expiration(uint32_t expiration) {
        this->transaction.data.asset.htlcLock.expiration = expiration;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // RecipientId - uint8_t[21] (network.version + pubkeyHash)
    HtlcLock &recipientId(const uint8_t *addressHash) {
        std::copy_n(addressHash,
                    ADDRESS_HASH_LEN,
                    this->transaction.data.asset.htlcLock.recipientId.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // RecipientId - std::string
    HtlcLock &recipientId(const std::string &recipientId) {
        const auto hashPair = Base58::getHashPair(recipientId.c_str());
        this->transaction.data.asset
                .htlcLock.recipientId.at(0) = hashPair.version;

        std::copy(hashPair.pubkeyHash.begin(),
                  hashPair.pubkeyHash.end(),
                  &this->transaction.data.asset.htlcLock.recipientId.at(1));

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    HtlcLock(const Configuration &config = {}) {
        this->transaction.data.type = HTLC_LOCK_TYPE;
        this->configure(config);
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
