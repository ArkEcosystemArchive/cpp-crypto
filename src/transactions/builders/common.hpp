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

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "common/configuration.hpp"

#include "identities/keys.hpp"

#include "transactions/transaction.hpp"

#include "interfaces/identities.hpp"

#include "utils/str.hpp"

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
    T &version(uint8_t version) {
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
    T &network(uint8_t network) {
        this->transaction.data.network = network;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // TypeGroup
    T &typeGroup(uint16_t typeGroup) {
        this->transaction.data.typeGroup = typeGroup;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Transaction Type
    T &type(uint16_t type) {
        this->transaction.data.type = type;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Nonce - v2 Only
    T &nonce(uint64_t nonce) {
        this->transaction.data.nonce = nonce;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Timestamp - v1 Only
    T &timestamp(uint32_t timestamp) {
        this->transaction.data.timestamp = timestamp;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Sender PublicKey
    //
    // This builder item is unecessary when signing the builder inline.
    // - e.g `.sign(passphrase)`
    //
    // `Transaction::sign(passphrase)` adds this automatically.
    //
    // ---
    T &senderPublicKey(const uint8_t *senderPublicKey) {
        std::copy_n(senderPublicKey,
                    PUBLICKEY_COMPRESSED_LEN,
                    this->transaction.data.senderPublicKey.begin());

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Fee
    T &fee(uint64_t fee) {
        this->transaction.data.fee = fee;
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // VendorField - std::vector<uint8_t>
    T &vendorFieldHex(const uint8_t *vendorField, const size_t &length) {
        this->transaction.data.vendorField.insert(
            this->transaction.data.vendorField.begin(),
            vendorField,
            vendorField + length);

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // VendorField - std::string
    T &vendorField(const std::string &vendorField) {
        const auto vf = StringToBytes(vendorField);

        this->transaction.data.vendorField.insert(
            this->transaction.data.vendorField.begin(),
            vf.begin(),
            vf.end());

        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Signature
    T &signature(const uint8_t *signature, const size_t &length) {
        this->transaction.data.signature.resize(length);
        std::copy_n(signature,
                    length,
                    this->transaction.data.signature.begin());
        return reinterpret_cast<T&>(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Second Signature
    T &secondSignature(const uint8_t *secondSignature, const size_t &length) {
        this->transaction.data.signature.resize(length);
        std::copy_n(secondSignature,
                    length,
                    this->transaction.data.signature.begin());
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
    // Finish the build pattern
    // !! should always be the last call !!
    Transaction &build() {
        return this->transaction;
    }

  protected:
    ////////////////////////////////////////////////////////////////////////////
    void configure(const Configuration &config) {
        this->transaction.data.fee = config.getFee(this->transaction.data.type);
        this->transaction.data.network = config.getNetwork().version;
    }

    ////////////////////////////////////////////////////////////////////////////
    Transaction transaction;
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
