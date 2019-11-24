/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDER_COMMON_HPP
#define ARK_TRANSACTIONS_BUILDER_COMMON_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "common/configuration.hpp"

#include "transactions/transaction.hpp"

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Internal Common Transaction Builder Class
template<class T> class Common {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Version
    T &version(const uint8_t version) {
        this->transaction.data.version = version;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Network
    //
    // - Devnet: 30
    // - Mainnet: 23
    //
    // ---
    T &network(const uint8_t network) {
        this->transaction.data.network = network;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // TypeGroup
    T &typeGroup(const uint16_t typeGroup) {
        this->transaction.data.typeGroup = typeGroup;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Transaction Type
    T &type(const uint16_t type) {
        this->transaction.data.type = type;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Nonce - v2 Only
    T &nonce(const uint64_t nonce) {
        this->transaction.data.nonce = nonce;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Timestamp - v1 Only
    T &timestamp(const uint32_t timestamp) {
        this->transaction.data.timestamp = timestamp;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Sender PublicKey
    T &senderPublicKey(const uint8_t *senderPublicKey) {
        std::move(senderPublicKey,
                  senderPublicKey + PUBLICKEY_COMPRESSED_LEN,
                  this->transaction.data.senderPublicKey.begin());

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Fee
    T &fee(const uint64_t fee) {
        this->transaction.data.fee = fee;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // VendorField - std::vector<uint8_t>
    T &vendorFieldHex(const uint8_t *vendorField, const size_t length) {
        this->transaction.data.vendorField.insert(
            this->transaction.data.vendorField.begin(),
            vendorField,
            vendorField + length);

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // VendorField - std::string
    T &vendorField(const std::string &vendorField) {
        const auto vf = reinterpret_cast<const char *>(vendorField.c_str());

        this->transaction.data.vendorField.insert(
            this->transaction.data.vendorField.begin(),
            vf,
            vendorField.size());

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Signature
    T &signature(const uint8_t *signature, const size_t length) {
        this->transaction.data.signature.insert(
            this->transaction.data.signature.begin(),
            signature,
            signature + length);

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Second Signature
    T &secondSignature(const uint8_t *secondSignature, const size_t length) {
        this->transaction.data.secondSignature.insert(
            this->transaction.data.secondSignature.begin(),
            secondSignature,
            secondSignature + length);

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Sign
    T &sign(const std::string &passphrase) {
        this->transaction.sign(passphrase);
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Second Sign
    T &secondSign(const std::string &secondPassphrase) {
        this->transaction.secondSign(secondPassphrase);
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Build
    // 
    // If calling 'builder::sign()' before calling 'build()',
    // ensure the Fees and Network are properly configured first.
    //
    // ---
    Transaction &build(const Configuration &config = {}) {
        // if the transaction fee is the default of '0', use the config fees.
        if (this->transaction.data.fee == 0ULL) {
            this->transaction.data.fee = config.getFee(this->transaction.data.type);
        }

        // If either network is not the default, use the config version.
        if (this->transaction.data.network != Devnet.version &&
            config.getNetwork().version != Devnet.version) {
            this->transaction.data.network = config.getNetwork().version;
        }

        return this->transaction;
    }

  protected:
    ////////////////////////////////////////////////////////////////////////////
    Transaction transaction;
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
