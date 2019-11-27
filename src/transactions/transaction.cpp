/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/transaction.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"

#include "identities/keys.hpp"

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "transactions/defaults/offsets.hpp"

#include "transactions/transaction_data.hpp"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/json.h"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Compute the unique transaction ID.
auto Transaction::getId() const -> Hash32 {
    const auto serialized = this->toBytes(false, false);
    return Hash::sha256(serialized.data(), serialized.size());
}

////////////////////////////////////////////////////////////////////////////////
// Sign the transaction using a passphrase.
auto Transaction::sign(const std::string &passphrase) -> bool {
    if (passphrase.empty()) {
        return false;
    }

    const auto keys = identities::Keys::fromPassphrase(passphrase.c_str());

    std::move(keys.publicKey.begin(),
              keys.publicKey.end(),
              this->data.senderPublicKey.begin());

    const auto serialized = this->toBytes(true, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    this->data.signature.reserve(SIGNATURE_ECDSA_MAX);

    return Curve::Ecdsa::sign(hash32.data(),
                              keys.privateKey.data(),
                              &this->data.signature);
}

////////////////////////////////////////////////////////////////////////////////
// Sign the Transaction using a Second Passphrase.
auto Transaction::secondSign(const std::string &secondPassphrase) -> bool {
    if (this->data.signature.empty() || secondPassphrase.empty()) {
        return false;
    }

    const auto keys = identities::Keys::fromPassphrase(secondPassphrase.c_str());

    const auto serialized = this->toBytes(false, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    this->data.secondSignature.reserve(SIGNATURE_ECDSA_MAX);
    
    return Curve::Ecdsa::sign(hash32.data(),
                              keys.privateKey.data(),
                              &this->data.secondSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Verify the Transaction.
auto Transaction::verify() const -> bool {
    // skip both signatures,
    // neither should be present in the signing hash.
    const auto serialized = this->toBytes(true, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    return Curve::Ecdsa::verify(hash32.data(),
                                this->data.senderPublicKey.data(),
                                this->data.signature);
}

////////////////////////////////////////////////////////////////////////////////
// Verify the Transaction using a Second PublicKey.
auto Transaction::secondVerify(const uint8_t *secondPublicKey) const -> bool {
    // include only the first signature,
    // that should be present signing hash for a second signing.
    const auto serialized = this->toBytes(false, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    return Curve::Ecdsa::verify(hash32.data(),
                                secondPublicKey,
                                this->data.secondSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Deserialize the given Hex string via AIP11.
auto Transaction::deserialize(const std::vector<uint8_t> &serialized) -> bool {
    return Deserializer::deserialize(&this->data, serialized);
}

////////////////////////////////////////////////////////////////////////////////
// Serialize the object via AIP11.
auto Transaction::serialize() -> std::vector<uint8_t> {
    return Serializer::serialize(this->data);
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into its byte representation.
auto Transaction::toBytes(bool excludeSignature,
                          bool excludeSecondSignature) const
                                -> std::vector<uint8_t> {
    return Serializer::serialize(this->data,
                                 { excludeSignature, excludeSecondSignature });
}

////////////////////////////////////////////////////////////////////////////////
// Turn the transaction into a standardized array.
//
// This concept of an array in is quite different compared to other ARK SDKs.
// C++11 doesn't have an 'Any' type, so we'll need to use a string map here.
//
// Json Sizes are approximated using 'https://arduinojson.org/v6/assistant/'
//
// --
auto Transaction::toMap() const -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    size_t txSize       = 0UL;
    size_t jsonSize     = 0UL;

    // Start with the Transaction's Asset.
    // Tranfer
    if (this->data.type == TRANSFER_TYPE) {
        map = Transfer::getMap(this->data.asset.transfer);
        txSize = TRANSACTION_TYPE_TRANSFER_SIZE;
        const auto extraBytes = 413;
        jsonSize = JSON_OBJECT_SIZE(11) + extraBytes;
    }

    // Second Signature Registration
    if (this->data.type == SECOND_SIGNATURE_TYPE) {
        map = SecondSignature::getMap(this->data.asset.secondSignature);
        txSize = PUBLICKEY_COMPRESSED_LEN;
        const auto extraBytes = 438;
        jsonSize = 2 * JSON_OBJECT_SIZE(1) +
                       JSON_OBJECT_SIZE(9) +
                       extraBytes;
    }

    // Delegate Registration
    if (this->data.type == DELEGATE_REGISTRATION_TYPE) {
        map = DelegateRegistration::getMap(
                this->data.asset.delegateRegistration);
        txSize = strtol(map["usernameLen"].c_str(), nullptr, BASE_10);
        const auto extraBytes = 382;
        jsonSize = 2 * JSON_OBJECT_SIZE(1) +
                       JSON_OBJECT_SIZE(9) +
                       extraBytes;
    }

    // Vote
    if (this->data.type == VOTE_TYPE) {
        map = Vote::getMap(this->data.asset.vote);
        txSize = VOTES_LEN;
        const auto extraBytes = 427;
        jsonSize = JSON_ARRAY_SIZE(1) +
                   JSON_OBJECT_SIZE(1) +
                   JSON_OBJECT_SIZE(9) +
                   extraBytes;
    }

    // MultiSignature Registration
    // if (this->data.type == MULTI_SIGNATURE_TYPE) {}  // TODO

    // Ipfs
    if (this->data.type == IPFS_TYPE) {
        map = Ipfs::getMap(this->data.asset.ipfs);
        txSize = strtol(map["ipfsLen"].c_str(), nullptr, BASE_10);
        const auto extraBytes = 403;
        jsonSize = 2 * JSON_OBJECT_SIZE(1) +
                       JSON_OBJECT_SIZE(9) +
                       extraBytes;
    }

    // MultiPayment
    if (this->data.type ==  MULTI_PAYMENT_TYPE) {
        map = MultiPayment::getMap(this->data.asset.multiPayment);
        const auto n_payments = strtol(map["n_payments"].c_str(),
                                       nullptr,
                                       BASE_10);
        txSize = n_payments * (sizeof(uint64_t) + ADDRESS_STR_LEN);
        const auto extraBytes = (40 * n_payments);
        jsonSize = JSON_ARRAY_SIZE(n_payments) +
                   JSON_OBJECT_SIZE(1) +
                   (n_payments * JSON_OBJECT_SIZE(2)) +
                   JSON_OBJECT_SIZE(9) +
                   extraBytes;
    }

    // Delegate Resignation
    if (this->data.type == DELEGATE_RESIGNATION_TYPE) {
        const auto extraBytes = 348;
        jsonSize = JSON_OBJECT_SIZE(8) + extraBytes;
    }

    // Htlc Lock
    if (this->data.type == HTLC_LOCK_TYPE) {
        map = HtlcLock::getMap(this->data.asset.htlcLock);
        txSize = HTLC_LOCK_SIZE;
        const auto extraBytes = 509;
        jsonSize = JSON_OBJECT_SIZE(1) +
                   (2 * JSON_OBJECT_SIZE(2)) +
                   JSON_OBJECT_SIZE(11) +
                   extraBytes;
    }

    // Htlc Claim
    if (this->data.type == HTLC_CLAIM_TYPE) {
        map = HtlcClaim::getMap(this->data.asset.htlcClaim);
        txSize = HASH_64_LEN;
        const auto extraBytes = 480;
        jsonSize = JSON_OBJECT_SIZE(1) +
                   JSON_OBJECT_SIZE(2) +
                   JSON_OBJECT_SIZE(9) +
                   extraBytes;
    }

    // Htlc Refund
    if (this->data.type == HTLC_REFUND_TYPE) {
        map = HtlcRefund::getMap(this->data.asset.htlcRefund);
        txSize = HASH_32_LEN;
        const auto extraBytes = 435;
        jsonSize = 2 * JSON_OBJECT_SIZE(1) +
                       JSON_OBJECT_SIZE(9) +
                       extraBytes;
    }

    // Continue with the Common variables
    //  Version
    map.emplace("version", UintToString(this->data.version));

    //  Network
    map.emplace("network", UintToString(this->data.network));

    //  Type
    map.emplace("type", UintToString(this->data.type));

    if (this->data.version == TRANSACTION_VERSION_TYPE_2) {
        // Nonce
        map.emplace("nonce", UintToString(this->data.nonce));
    }
    else if (this->data.version == TRANSACTION_VERSION_TYPE_1) {
        // Timestamp
        map.emplace("timestamp", UintToString(this->data.timestamp));
    }

    // Sender PublicKey
    map.emplace("senderPublicKey", BytesToHex(this->data.senderPublicKey));

    //  Fee
    map.emplace("fee", UintToString(this->data.fee));

    // VendorField
    if (!this->data.vendorField.empty()) {
        const auto vf = reinterpret_cast<const char *>(
                this->data.vendorField.data());

        map.emplace("vendorField",
                    std::string(vf, vf + this->data.vendorField.size()));
        txSize += this->data.vendorField.size();
    }

    // Signature
    if (!this->data.signature.empty()) {
        map.emplace("signature", BytesToHex(this->data.signature));
    }

    // Second Signature
    if (!this->data.secondSignature.empty()) {
        map.emplace("secondSignature", BytesToHex(this->data.secondSignature));
    }

    // Transaction Id
    map.emplace("id", BytesToHex(this->getId()));

    if (this->data.version == TRANSACTION_VERSION_TYPE_2) {
        txSize += VF_OFFSET;
    }
    else if (this->data.version == TRANSACTION_VERSION_TYPE_1) {
        txSize += v1::VF_OFFSET;
    }

    map.emplace("txSize", UintToString(txSize));
    map.emplace("jsonSize", UintToString(jsonSize));

    return map;
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into a JSON string using `toMap` as the source.
auto Transaction::toJson() const -> std::string {
    auto txArray = this->toMap();

    const auto jsonSize = strtol(txArray["jsonSize"].c_str(), nullptr, BASE_10);
    const auto docCapacity = jsonSize;
    DynamicJsonDocument doc(docCapacity);

    // Version
    doc["version"] = strtol(txArray["version"].c_str(), nullptr, BASE_10);

    // Network
    doc["network"] = strtol(txArray["network"].c_str(), nullptr, BASE_10);

    // Type
    doc["type"] = strtol(txArray["type"].c_str(), nullptr, BASE_10);

    if (this->data.version == TRANSACTION_VERSION_TYPE_2) {
        // Nonce
        doc["nonce"] = txArray["nonce"];
    }
    else if (this->data.version == TRANSACTION_VERSION_TYPE_1) {
        // Timestamp
        doc["timestamp"] = txArray["timestamp"];
    }

    // Sender PublicKey
    doc["senderPublicKey"] = txArray["senderPublicKey"];

    // Fee
    doc["fee"] = txArray["fee"];

    // VendorField
    if (!this->data.vendorField.empty()) {
        doc["vendorField"] = txArray["vendorField"];
    }

    // Assets
    // Transfer
    if (this->data.type == TRANSFER_TYPE) {
        // Amount
        doc["amount"] = txArray["amount"];

        // Expiration
        doc["expiration"] = strtol(txArray["expiration"].c_str(),
                                   nullptr,
                                   BASE_10);
        // RecipientId
        doc["recipientId"] = txArray["recipientId"];
    }

    // Second Signature Registration
    if (this->data.type == SECOND_SIGNATURE_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonObject secondSignature = asset.createNestedObject("signature");

        // Second PublicKey
        secondSignature["publicKey"] = txArray["publicKey"];
    }

    // Delegate Registration
    if (this->data.type == DELEGATE_REGISTRATION_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonObject registration = asset.createNestedObject("delegate");

        // Username
        registration["username"] = txArray["username"];
    }

    // Vote
    if (this->data.type == VOTE_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonArray votes = asset.createNestedArray("votes");

        // Votes
        votes.add(txArray["votes"]);
    }

    // MultiSignature Registration
    // if (this->data.type == MULTI_SIGNATURE_TYPE) {}  // TODO

    // Ipfs
    if (this->data.type == IPFS_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");

        // Ipfs DAG
        asset["ipfs"] = txArray["ipfs"];
    }

    // MultiPayment
    if (this->data.type == MULTI_PAYMENT_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonArray payments = asset.createNestedArray("payments");

        const auto paymentsStr = txArray["amounts"];
        const auto addressesStr = txArray["addresses"];
        const auto n_payments = strtol(txArray["n_payments"].c_str(),
                                       nullptr,
                                       BASE_10);

        for (uint8_t i = 0U; i < n_payments; ++i) {
            JsonObject payment_n = payments.createNestedObject();

            // Ammount(N)
            payment_n["amount"] = paymentsStr
                    .substr(0, paymentsStr.find(',', 0));

            // RecipientId(N)
            payment_n["recipientId"] = addressesStr
                .substr(i + (i * ADDRESS_STR_LEN), ADDRESS_STR_LEN);
        }
    }

    // Delegate Resignation
    // No Asset Needed.

    // HTLC Lock
    if (this->data.type == HTLC_LOCK_TYPE) {
        // Amount
        doc["amount"] = txArray["amount"];

        // RecipientId
        doc["recipientId"] = txArray["recipientId"];

        JsonObject asset = doc.createNestedObject("asset");
        JsonObject lock = asset.createNestedObject("lock");

        // Secret Hash
        lock["secretHash"] = txArray["secretHash"];

        JsonObject expiration = lock.createNestedObject("expiration");

        // Expiration Type
        expiration["type"] = strtol(txArray["expirationType"].c_str(),
                                    nullptr,
                                    BASE_10);
        // Expiration Value
        expiration["value"] = strtol(txArray["expiration"].c_str(),
                                     nullptr,
                                     BASE_10);
    }

    // HTLC Claim
    if (this->data.type == HTLC_CLAIM_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonObject claim = asset.createNestedObject("claim");

        // Lock Transaction Id
        claim["lockTransactionId"] = txArray["lockTransactionId"];

        // Unlock Secret
        claim["unlockSecret"] = txArray["unlockSecret"];
    }

    // HTLC Refund
    if (this->data.type == HTLC_REFUND_TYPE) {
        JsonObject asset = doc.createNestedObject("asset");
        JsonObject refund = asset.createNestedObject("refund");

        // Lock Transaction Id
        refund["lockTransactionId"] = txArray["lockTransactionId"];
    }

    // Signature
    if (!this->data.signature.empty()) {
        doc["signature"] = txArray["signature"];
    }

    // Second Signature
    if (!this->data.secondSignature.empty()) {
        doc["secondSignature"] = txArray["secondSignature"];
    }

    // Transaction Id
    doc["id"] = txArray["id"];

    std::string jsonStr;
    jsonStr.reserve(docCapacity);
    serializeJson(doc, jsonStr);

    return jsonStr;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
