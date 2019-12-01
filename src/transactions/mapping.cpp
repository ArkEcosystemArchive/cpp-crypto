/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/mapping.hpp"

#include <cstdint>
#include <cstring>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "transactions/transaction_data.hpp"

#include "transactions/defaults/types.hpp"

#include "utils/hex.hpp"
#include "utils/json.h"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Common Constants
const auto KEY_VERSION_LABEL    = "version";
const auto KEY_VERSION_SIZE     = strlen(KEY_VERSION_LABEL);

const auto KEY_NETWORK_LABEL    = "network";
const auto KEY_NETWORK_SIZE     = strlen(KEY_NETWORK_LABEL);

const auto KEY_TYPEGROUP_LABEL  = "typeGroup";
const auto KEY_TYPEGROUP_SIZE   = strlen(KEY_TYPEGROUP_LABEL);

const auto KEY_TYPE_LABEL       = "type";
const auto KEY_TYPE_SIZE        = strlen(KEY_TYPE_LABEL);

const auto KEY_NONCE_LABEL      = "nonce";
const auto KEY_NONCE_SIZE       = strlen(KEY_NONCE_LABEL);

const auto KEY_TIMESTAMP_LABEL  = "timestamp";
const auto KEY_TIMESTAMP_SIZE   = strlen(KEY_TIMESTAMP_LABEL);

const auto KEY_SENDER_PUBLICKEY_LABEL   = "senderPublicKey";
const auto KEY_SENDER_PUBLICKEY_SIZE    = strlen(KEY_SENDER_PUBLICKEY_LABEL);

const auto KEY_FEE_LABEL        = "fee";
const auto KEY_FEE_SIZE         = strlen(KEY_FEE_LABEL);

const auto KEY_VENDORFIELD_LABEL        = "vendorField";
const auto KEY_VENDORFIELD_SIZE         = strlen(KEY_VENDORFIELD_LABEL);

const auto KEY_SIGNATURE_LABEL  = "signature";
const auto KEY_SIGNATURE_SIZE   = strlen(KEY_SIGNATURE_LABEL);

const auto KEY_SECOND_SIGNATURE_LABEL   = "secondSignature";
const auto KEY_SECOND_SIGNATURE_SIZE    = strlen(KEY_SECOND_SIGNATURE_LABEL);

const auto KEY_ID_LABEL         = "id";
const auto KEY_ID_SIZE          = strlen(KEY_ID_LABEL);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map Serialization

////////////////////////////////////////////////////////////////////////////////
// Start with the Common Map data
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
static void AddCommonMap(std::map<std::string, std::string> &map,
                         const TransactionData &data) {
    //  Version
    map.emplace(KEY_VERSION_LABEL, UintToString(data.version));

    //  Network
    map.emplace(KEY_NETWORK_LABEL, UintToString(data.network));

    // v2
    if (data.version == TRANSACTION_VERSION_TYPE_2) {
        // TypeGroup
        map.emplace(KEY_TYPEGROUP_LABEL,
                    UintToString(data.typeGroup));
    }

    // Type
    map.emplace(KEY_TYPE_LABEL, UintToString(data.type));

    // v2
    if (data.version == TRANSACTION_VERSION_TYPE_2) {
        // Nonce
        map.emplace(KEY_NONCE_LABEL, UintToString(data.nonce));
    }
    // v1
    else if (data.version == TRANSACTION_VERSION_TYPE_1) {
        // Timestamp
        map.emplace(KEY_TIMESTAMP_LABEL,
                    UintToString(data.timestamp));
    }

    // Sender PublicKey
    map.emplace(KEY_SENDER_PUBLICKEY_LABEL,
                BytesToHex(data.senderPublicKey));

    //  Fee
    map.emplace(KEY_FEE_LABEL, UintToString(data.fee));

    // VendorField
    if (!data.vendorField.empty()) {
        const auto vf = reinterpret_cast<const char *>(
                data.vendorField.data());

        map.emplace(KEY_VENDORFIELD_LABEL,
                    std::string(vf, vf + data.vendorField.size()));
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add Asset data
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
static void AddAssetMap(std::map<std::string, std::string> &map,
                        const TransactionData &data) {
    // Tranfer
    if (data.type == TRANSFER_TYPE) {
        Transfer::addToMap(data.asset.transfer, map);
    }

    // Second Signature Registration
    else if (data.type == SECOND_SIGNATURE_TYPE) {
        SecondSignature::addToMap(data.asset.secondSignature, map);
    }

    // Delegate Registration
    else if (data.type == DELEGATE_REGISTRATION_TYPE) {
        DelegateRegistration::addToMap(data.asset.delegateRegistration, map);
    }

    // Vote
    else if (data.type == VOTE_TYPE) {
        Vote::addToMap(data.asset.vote, map);
    }

    // MultiSignature Registration
    // if (this->data.type == MULTI_SIGNATURE_TYPE) {}  // TODO

    // Ipfs
    else if (data.type == IPFS_TYPE) {
        Ipfs::addToMap(data.asset.ipfs, map);
    }

    // MultiPayment
    else if (data.type ==  MULTI_PAYMENT_TYPE) {
        MultiPayment::addToMap(data.asset.multiPayment, map);
    }

    // Delegate Resignation
    // data.type == DELEGATE_RESIGNATION_TYPE  // No Asset Needed

    // Htlc Lock
    else if (data.type == HTLC_LOCK_TYPE) {
        HtlcLock::addToMap(data.asset.htlcLock, map);
    }

    // Htlc Claim
    else if (data.type == HTLC_CLAIM_TYPE) {
        HtlcClaim::addToMap(data.asset.htlcClaim, map);
    }

    // Htlc Refund
    else if (data.type == HTLC_REFUND_TYPE) {
        HtlcRefund::addToMap(data.asset.htlcRefund, map);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add Common Extra Map data
//
// - Signature (if present)
// - Second Signature (if present)
//
// ---
static void AddCommonExtrasMap(std::map<std::string, std::string> &map,
                               const TransactionData &data) {
    // Signature
    if (!data.signature.empty()) {
        map.emplace(KEY_SIGNATURE_LABEL,
                    BytesToHex(data.signature));
    }

    // Second Signature
    if (!data.secondSignature.empty()) {
        map.emplace(KEY_SECOND_SIGNATURE_LABEL,
                    BytesToHex(data.secondSignature));
    }
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
auto Mapping::getMap(const TransactionData &data)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    AddCommonMap(map, data);
    AddAssetMap(map, data);
    AddCommonExtrasMap(map, data);

    return map;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Json Serialization

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
static auto GetCommonJsonCapacity(
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

    const auto transactionVersion = strtol(map.at(KEY_VERSION_LABEL).c_str(),
                                           nullptr,
                                           BASE_10);

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

    // Vendorfield
    if (map.find(KEY_VENDORFIELD_LABEL) != map.end()) {
        commonCapacity += JSON_OBJECT_SIZE(1) +
                KEY_VENDORFIELD_SIZE + map.at(KEY_VENDORFIELD_LABEL).size();
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
static auto GetAssetJsonCapacity(const uint8_t type,
                                 const size_t n_payments = 0UL) -> size_t {
    // Transfer
    if (type == TRANSFER_TYPE) {
        return Transfer::getJsonCapacity();
    }

    // Second Signature Registration
    else if (type == SECOND_SIGNATURE_TYPE) {
        return SecondSignature::getJsonCapacity();
    }

    // Delegate Registration
    else if (type == DELEGATE_REGISTRATION_TYPE) {
        return DelegateRegistration::getJsonCapacity();
    }

    // Vote
    else if (type == VOTE_TYPE) {
        return Vote::getJsonCapacity();
    }

    // // MultiSignature Registration
    // else if (type == MULTI_SIGNATURE_TYPE) {}  // TODO

    // Ipfs
    else if (type == IPFS_TYPE) {
        return Ipfs::getJsonCapacity();
    }

    // MultiPayment
    else if (type == MULTI_PAYMENT_TYPE) {
        return MultiPayment::getJsonCapacity(n_payments);
    }

    // Delegate Resignation
    // type == DELEGATE_RESIGNATION_TYPE  // No Asset Needed

    // Htlc Lock
    else if (type == HTLC_LOCK_TYPE) {
        return HtlcLock::getJsonCapacity();
    }

    // Htlc Claim
    else if (type == HTLC_CLAIM_TYPE) {
        return HtlcClaim::getJsonCapacity();
    }

    // Htlc Refund
    else if (type == HTLC_REFUND_TYPE) {
        return HtlcRefund::getJsonCapacity();
    }

    return 0UL;
}

////////////////////////////////////////////////////////////////////////////////
// Calculate the ArduinoJson Capacity of the Extra Transaction Data.
//
// Json Sizes are calculated using 'https://arduinojson.org/v6/assistant/'
//
// - Signature          (if present)
// - Second Signature   (if present)
// - Transaction Id
//
// ---
static auto GetCommonExtrasJsonCapacity(
        const std::map<std::string, std::string> &map) -> size_t {
    size_t commonExtrasCapacity = 0UL;

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

    commonExtrasCapacity += KEY_ID_SIZE + HASH_32_MAX_CHARS;

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
static void AddCommonJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map){
    const auto transactionVersion = strtol(map.at(KEY_VERSION_LABEL).c_str(),
                                           nullptr,
                                           BASE_10);

    // Version
    jsonDoc[KEY_VERSION_LABEL] = transactionVersion;

    // Network
    jsonDoc[KEY_NETWORK_LABEL] = strtol(map.at(KEY_NETWORK_LABEL).c_str(),
                                    nullptr,
                                    BASE_10);

    // v2
    if (transactionVersion == TRANSACTION_VERSION_TYPE_2) {
        // TypeGroup
        jsonDoc[KEY_TYPEGROUP_LABEL] = strtol(
                map.at(KEY_TYPEGROUP_LABEL).c_str(),
                nullptr,
                BASE_10);
    }

    // Type
    jsonDoc[KEY_TYPE_LABEL] = strtol(map.at(KEY_TYPE_LABEL).c_str(),
                                     nullptr,
                                     BASE_10);

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
static void AddAssetToJson(const uint8_t type,
                           DynamicJsonDocument &jsonDoc,
                           const std::map<std::string, std::string> &map) {
    // Transfer
    if (type == TRANSFER_TYPE) {
        Transfer::addToJson(jsonDoc, map);
    }

    // SecondSignature
    else if (type == SECOND_SIGNATURE_TYPE) {
        SecondSignature::addToJson(jsonDoc, map);
    }

    // Delegate Registration
    else if (type == DELEGATE_REGISTRATION_TYPE) {
        DelegateRegistration::addToJson(jsonDoc, map);
    }

    // Vote
    else if (type == VOTE_TYPE) {
        Vote::addToJson(jsonDoc, map);
    }

    // // MultiSignature Registration
    // if (this->data.type == MULTI_SIGNATURE_TYPE) {}  // TODO

    // Ipfs
    else if (type == IPFS_TYPE) {
        Ipfs::addToJson(jsonDoc, map);
    }

    // MultiPayment
    else if (type == MULTI_PAYMENT_TYPE) {
    // Get the Type from the Mapped Transaction.
        MultiPayment::addToJson(jsonDoc, map);
    }

    // Delegate Resignation
    // No Asset Needed

    // Htlc Lock
    else if (type == HTLC_LOCK_TYPE) {
        HtlcLock::addToJson(jsonDoc, map);
    }

    // Htlc Claim
    else if (type == HTLC_CLAIM_TYPE) {
        HtlcClaim::addToJson(jsonDoc, map);
    }

    // Htlc Refund
    else if (type == HTLC_REFUND_TYPE) {
        HtlcRefund::addToJson(jsonDoc, map);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add a Transcations Extra data to a 'DynamicJsonDocument'
//
// - Signature (if present)
// - Second Signature (if present)
// - Transaction Id
//
// ---
static void AddCommonExtrasJson(DynamicJsonDocument &jsonDoc,
                                const std::map<std::string, std::string> &map) {
    // Signature
    if (map.find(KEY_SIGNATURE_LABEL) != map.end()) {
        jsonDoc[KEY_SIGNATURE_LABEL] = map.at(KEY_SIGNATURE_LABEL);
    }

    // Second Signature
    if (map.find(KEY_SECOND_SIGNATURE_LABEL) != map.end()) {
        jsonDoc[KEY_SECOND_SIGNATURE_LABEL] = map.at(KEY_SECOND_SIGNATURE_LABEL);
    }

    // Transaction Id
    jsonDoc[KEY_ID_LABEL] = map.at(KEY_ID_LABEL);
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into a JSON string using `toMap()` as the source.
//
//
// - Add the Common Transaction data.
// - Add the Transaction Asset data.
// - Add the Transactions Extra data.
//
// ---
auto Mapping::toJson(const std::map<std::string, std::string> &map)
        -> std::string {  // NOLINT
    // Get the Type from the Mapped Transaction.
    const uint8_t transactionType = strtol(map.at(KEY_TYPE_LABEL).c_str(),
                                                  nullptr,
                                                  BASE_10);

    // Non-Zero only if Map contains MultiPayment data
    const auto multiPaymentCount = map.find(KEY_N_PAYMENTS_LABEL) != map.end()
            ? strtol(map.at(KEY_N_PAYMENTS_LABEL).c_str(), nullptr, BASE_10)
            : 0UL;

    // Calculate the Capacity needed for ArduinoJson Serialization.
    size_t jsonCapacity =
            GetCommonJsonCapacity(map) +
            GetAssetJsonCapacity(transactionType, multiPaymentCount) +
            GetCommonExtrasJsonCapacity(map);

    DynamicJsonDocument jsonDoc(jsonCapacity);

    AddCommonJson(jsonDoc, map);
    AddAssetToJson(transactionType, jsonDoc, map);
    AddCommonExtrasJson(jsonDoc, map);

    std::string jsonStr;
    jsonStr.reserve(jsonCapacity);

    serializeJson(jsonDoc, jsonStr);

    return jsonStr;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
