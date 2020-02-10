/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/mapping/json.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "transactions/defaults/types.hpp"

#include "transactions/mapping/labels.hpp"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Calculate the ArduinoJson Capacity of the Common Transaction Data.
//
// Json Sizes are calculated using 'https://arduinojson.org/v6/assistant/'
//
// - Version
// - Network
// - TypeGroup          // v2
// - Type
// - Nonce              // v2
// - Timestamp          // v1
// - Sender PublicKey
// - Fee
// - VendorField
//
// ---
static auto getCommonJsonCapacity(
        const std::map<std::string, std::string> &map) -> size_t {
    auto commonCapacity =
            JSON_OBJECT_SIZE(1) +
                KEY_VERSION_SIZE + UINT8_MAX_CHARS +
            JSON_OBJECT_SIZE(1) +
                KEY_NETWORK_SIZE + UINT8_MAX_CHARS +
            JSON_OBJECT_SIZE(1) +
                KEY_SENDER_PUBLICKEY_SIZE + PUBLICKEY_COMPRESSED_LEN +
            JSON_OBJECT_SIZE(1) +
                KEY_FEE_SIZE + UINT64_MAX_CHARS;

    const uint16_t transactionVersion = static_cast<uint16_t>(
            strtoul(map.at(KEY_VERSION_LABEL).c_str(), nullptr, BASE_10));

    // v2
    if (transactionVersion == TRANSACTION_VERSION_TYPE_2) {
        commonCapacity += JSON_OBJECT_SIZE(1) +
                                KEY_TYPEGROUP_SIZE + UINT32_MAX_CHARS +
                          JSON_OBJECT_SIZE(1) +
                                KEY_TYPE_SIZE + UINT16_MAX_CHARS +
                          JSON_OBJECT_SIZE(1) +
                                KEY_NONCE_SIZE + UINT64_MAX_CHARS;
    }
    // v1
    else if (transactionVersion == TRANSACTION_VERSION_TYPE_1) {
        commonCapacity += JSON_OBJECT_SIZE(1) +
                            KEY_TYPE_SIZE + UINT8_MAX_CHARS +
                          JSON_OBJECT_SIZE(1) +
                            KEY_TIMESTAMP_SIZE + UINT32_MAX_CHARS;
    }

    // Amount
    if (transactionVersion == TRANSACTION_VERSION_TYPE_2) {
        commonCapacity += JSON_OBJECT_SIZE(1) +
                            KEY_AMOUNT_SIZE + UINT64_MAX_CHARS;
    }

    // Vendorfield
    if (map.find(KEY_VENDORFIELD_LABEL) != map.end()) {
        commonCapacity += JSON_OBJECT_SIZE(1) +
                          KEY_VENDORFIELD_SIZE +
                          map.at(KEY_VENDORFIELD_LABEL).size();
    }

    return commonCapacity;
}

////////////////////////////////////////////////////////////////////////////////
// Calculate the ArduinoJson Capacity of the Transaction Asset Data.
//
// Json Sizes are calculated using 'https://arduinojson.org/v6/assistant/'
//
// - n_payments only needed for MultiPayment Capacity calculation.
//
// - Transfer
// - SecondSignature
// - Delegate Registration
// - Vote
// - MultiSignature Registration  // TODO
// - Ipfs
// - MultiPayment
// - Delegate Resignation  // No Asset Needed
// - Htlc Lock
// - Htlc Claim
// - Htlc Refund
//
// ---
static auto getAssetJsonCapacity(uint16_t type, const size_t &n_payments = 0UL)
        -> size_t {
    switch(type) {
        // Transfer
        case TRANSFER_TYPE:
            return Transfer::getJsonCapacity();

        // Second Signature Registration
        case SECOND_SIGNATURE_TYPE:
            return SecondSignature::getJsonCapacity();

        // Delegate Registration
        case DELEGATE_REGISTRATION_TYPE:
            return DelegateRegistration::getJsonCapacity();

        // Vote
        case VOTE_TYPE:
            return Vote::getJsonCapacity();

        // // MultiSignature Registration
        // case MULTI_SIGNATURE_TYPE:  // TODO

        // Ipfs
        case IPFS_TYPE:
            return Ipfs::getJsonCapacity();

        // MultiPayment
        case MULTI_PAYMENT_TYPE:
            return MultiPayment::getJsonCapacity(n_payments);

        // Delegate Resignation
        // No Asset Needed. Return Default of '0'.
        // case DELEGATE_RESIGNATION_TYPE:

        // Htlc Lock
        case HTLC_LOCK_TYPE:
            return HtlcLock::getJsonCapacity();

        // Htlc Claim
        case HTLC_CLAIM_TYPE:
            return HtlcClaim::getJsonCapacity();

        // Htlc Refund
        case HTLC_REFUND_TYPE:
            return HtlcRefund::getJsonCapacity();
    
        default: return 0UL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Calculate the ArduinoJson Capacity of the Extra Transaction Data.
//
// Json Sizes are calculated using 'https://arduinojson.org/v6/assistant/'
//
// - Transaction Id
// - Signature          (if present)
// - Second Signature   (if present)
//
// ---
static auto getExtrasJsonCapacity(
        const std::map<std::string, std::string> &map) -> size_t {
    // start with the txId json size
    size_t commonExtrasCapacity = KEY_ID_SIZE + HASH_32_MAX_CHARS;

    // Signature
    if (map.find(KEY_SIGNATURE_LABEL) != map.end()) {
        commonExtrasCapacity +=
                JSON_OBJECT_SIZE(1) +
                        KEY_SIGNATURE_SIZE + SIGNATURE_ECDSA_MAX_CHARS;
    }

    // Second Signature
    if (map.find(KEY_SECOND_SIGNATURE_LABEL) != map.end()) {
        commonExtrasCapacity +=
                JSON_OBJECT_SIZE(1) +
                        KEY_SECOND_SIGNATURE_SIZE + SIGNATURE_ECDSA_MAX_CHARS;
    }

    return commonExtrasCapacity;
}

////////////////////////////////////////////////////////////////////////////////
// Add Common Transaction data to a 'DynamicJsonDocument'
//
// - Version
// - Network
// - TypeGroup          // v2
// - Type
// - Nonce              // v2
// - Timestamp          // v1
// - Sender PublicKey
// - Fee
// - VendorField
//
// ---
static void mapCommonJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map) {
    const uint16_t transactionVersion =
            static_cast<uint16_t>(strtoul(map.at(KEY_VERSION_LABEL).c_str(),
                                          nullptr,
                                          BASE_10));

    // Version
    jsonDoc[KEY_VERSION_LABEL] = transactionVersion;

    // Network
    jsonDoc[KEY_NETWORK_LABEL] = strtoul(
            map.at(KEY_NETWORK_LABEL).c_str(), nullptr, BASE_10);

    // v2
    if (transactionVersion == TRANSACTION_VERSION_TYPE_2) {
        // TypeGroup
        jsonDoc[KEY_TYPEGROUP_LABEL] =
            strtoul(map.at(KEY_TYPEGROUP_LABEL).c_str(),
                    nullptr,
                    BASE_10);
    }

    // Type
    jsonDoc[KEY_TYPE_LABEL] = strtoul(
            map.at(KEY_TYPE_LABEL).c_str(), nullptr, BASE_10);

    // v2
    if (transactionVersion == TRANSACTION_VERSION_TYPE_2) {
        // Nonce
        jsonDoc[KEY_NONCE_LABEL] = map.at(KEY_NONCE_LABEL);
    }
    // v1
    else if (transactionVersion == TRANSACTION_VERSION_TYPE_1) {
        // Timestamp
        jsonDoc[KEY_TIMESTAMP_LABEL] = map.at(KEY_TIMESTAMP_LABEL);
    }

    // Sender PublicKey
    jsonDoc[KEY_SENDER_PUBLICKEY_LABEL] = map.at(KEY_SENDER_PUBLICKEY_LABEL);

    // Fee
    jsonDoc[KEY_FEE_LABEL] = map.at(KEY_FEE_LABEL);

    // Amount
    jsonDoc[KEY_AMOUNT_LABEL] = map.find(KEY_AMOUNT_LABEL) == map.end() &&
                                transactionVersion == TRANSACTION_VERSION_TYPE_2
                                        ? "0"
                                        : map.at(KEY_AMOUNT_LABEL);

    // VendorField
    if (map.find(KEY_VENDORFIELD_LABEL) != map.end()) {
        jsonDoc[KEY_VENDORFIELD_LABEL] = map.at(KEY_VENDORFIELD_LABEL);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add Transaction Asset data to a 'DynamicJsonDocument'
//
// - Transfer
// - SecondSignature
// - Delegate Registration
// - Vote
// - MultiSignature Registration  // TODO
// - Ipfs
// - MultiPayment
// - Delegate Resignation  // No Asset Needed
// - Htlc Lock
// - Htlc Claim
// - Htlc Refund
//
// ---
static void mapAssetJson(uint16_t type,
                         DynamicJsonDocument &jsonDoc,
                         const std::map<std::string, std::string> &map) {
    switch (type) {
        // Transfer
        case TRANSFER_TYPE:
            Transfer::addToJson(jsonDoc, map);
            break;

        // SecondSignature
        case SECOND_SIGNATURE_TYPE:
            SecondSignature::addToJson(jsonDoc, map);
            break;

        // Delegate Registration
        case DELEGATE_REGISTRATION_TYPE:
            DelegateRegistration::addToJson(jsonDoc, map);
            break;

        // Vote
        case VOTE_TYPE:
            Vote::addToJson(jsonDoc, map);
            break;

        // // MultiSignature Registration
        // case MULTI_SIGNATURE_TYPE:  // TODO

        // Ipfs
        case IPFS_TYPE:
            Ipfs::addToJson(jsonDoc, map);
            break;

        // MultiPayment
        case MULTI_PAYMENT_TYPE:
            MultiPayment::addToJson(jsonDoc, map);
            break;

        // Delegate Resignation
        // No Asset Needed
        // case DELEGATE_RESIGNATION_TYPE

        // Htlc Lock
        case HTLC_LOCK_TYPE: 
            HtlcLock::addToJson(jsonDoc, map);
            break;

        // Htlc Claim
        case HTLC_CLAIM_TYPE:
            HtlcClaim::addToJson(jsonDoc, map);
            break;

        // Htlc Refund
        case HTLC_REFUND_TYPE:
            HtlcRefund::addToJson(jsonDoc, map);
            break;
        
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add a Transcations Extra data to a 'DynamicJsonDocument'
//
// - Transaction Id
// - Signature (if present)
// - Second Signature (if present)
//
// ---
static void mapExtrasJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map) {
    // Transaction Id
    jsonDoc[KEY_ID_LABEL] = map.at(KEY_ID_LABEL);

    // Signature
    if (map.find(KEY_SIGNATURE_LABEL) != map.end()) {
        jsonDoc[KEY_SIGNATURE_LABEL] = map.at(KEY_SIGNATURE_LABEL);
    }

    // Second Signature
    if (map.find(KEY_SECOND_SIGNATURE_LABEL) != map.end()) {
        jsonDoc[KEY_SECOND_SIGNATURE_LABEL] = map.at(KEY_SECOND_SIGNATURE_LABEL);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Extract a Json String from a given Transaction Map.
//
//
// - Add the Common Transaction data.
// - Add the Transaction Asset data.
// - Add the Transactions Extra data. (id, signatures)
//
// ---
auto Json::fromTransactionMap(const std::map<std::string, std::string> &map)
        -> std::string {
    // Get the Type from the Mapped Transaction.
    const uint16_t transactionType = static_cast<uint16_t>(
            strtoul(map.at(KEY_TYPE_LABEL).c_str(), nullptr, BASE_10));

    // Non-Zero only if Map contains MultiPayment data
    const auto multiPaymentCount = map.find(KEY_N_PAYMENTS_LABEL) != map.end()
            ? strtol(map.at(KEY_N_PAYMENTS_LABEL).c_str(), nullptr, BASE_10)
            : 0UL;

    // Calculate the Capacity needed for Json Serialization.
    size_t jsonCapacity =
            getCommonJsonCapacity(map) +
            getAssetJsonCapacity(transactionType, multiPaymentCount) +
            getExtrasJsonCapacity(map);

    DynamicJsonDocument jsonDoc(jsonCapacity);

    mapCommonJson(jsonDoc, map);
    mapAssetJson(transactionType, jsonDoc, map);
    mapExtrasJson(jsonDoc, map);

    std::string jsonStr;
    jsonStr.reserve(jsonCapacity);

    serializeJson(jsonDoc, jsonStr);

    return jsonStr;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
