/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/serializer.hpp"

#include <cstdbool>
#include <cstdint>
#include <cstring>
#include <vector>

#include "interfaces/constants.h"

#include "crypto/hash.hpp"

#include "transactions/defaults/offsets.hpp"

#include "transactions/transaction_data.hpp"

#include "utils/packing.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Serialize Common
//
// @param const TransactionData &data
// @param std::vector<uint8_t> &buffer: The serialized transactions buffer.
//
// ---
// Internals:
//
// Header - 1 Byte:
// - buffer.at(0) = transaction.header;
//
// Transaction Version - 1 Byte:
// - buffer.at(1) = transaction.version;
//
// Network Version - 1 Byte:
// - buffer.at(2) = transaction.network;
//
// TypeGroup - 4 Bytes:
// - pack4LE(&buffer.at(TYPEGROUP_OFFSET), &transaction.typeGroup);
//
// Transaction Type - 2 Bytes:
// - pack2LE(&buffer.at(TYPE_OFFSET), &transaction.type);
//
// Nonce - 8 Bytes:
// - pack8LE(&buffer[NONCE_OFFSET], &transaction.nonce);
//
// SenderPublicKey - 33 Bytes:
// - buffer.insert(buffer.begin() + 17, transaction.senderPublicKey.begin(), transaction.senderPublicKey.end());
//
// Fee - 8 bytes
// - pack8LE(&buffer[FEE_OFFSET], &transaction.fee);
//
// VendorField Length - 1 Byte:
// - buffer.at(58) = transaction.vendorField.size();
//
// VendorField - 0 <=> 255 Bytes:
// - buffer.insert(buffer.begin() + 59, transaction.vendorField.begin(), transaction.vendorField.end());
//
// ---
static void serializeCommon(const TransactionData &transaction,
                            std::vector<uint8_t> &buffer) {
    buffer.at(HEADER_OFFSET)        = transaction.header;           // 1 Byte
    buffer.at(VERSION_OFFSET)       = transaction.version;          // 1 Byte
    buffer.at(NETWORK_OFFSET)       = transaction.network;          // 1 Byte

    pack4LE(&buffer.at(TYPEGROUP_OFFSET), &transaction.typeGroup);  // 4 Bytes
    pack2LE(&buffer.at(TYPE_OFFSET), &transaction.type);            // 2 Bytes
    pack8LE(&buffer[NONCE_OFFSET], &transaction.nonce);             // 8 Bytes

    buffer.insert(buffer.begin() + SENDER_PUBLICKEY_OFFSET,         // 21 Bytes
                  transaction.senderPublicKey.begin(),
                  transaction.senderPublicKey.end());

    pack8LE(&buffer[FEE_OFFSET], &transaction.fee);                 // 8 Bytes

    buffer.at(VF_LEN_OFFSET) =                                      // 1 Byte
            static_cast<uint8_t>(transaction.vendorField.size());

    if (!transaction.vendorField.empty()) {
        buffer.insert(buffer.begin() + VF_OFFSET,           // 0 <=> 255 Bytes
                     transaction.vendorField.begin(),
                     transaction.vendorField.end());
    }
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Common V1
//
// @param const TransactionData &data
// @param std::vector<uint8_t> &buffer: The serialized transactions buffer.
//
// ---
// Internals:
//
// Header - 1 Byte:
// - buffer.at(0) = transaction.header;
//
// Transaction Version - 1 Byte:
// - buffer.at(1) = transaction.version;
//
// Network Version - 1 Byte:
// - buffer.at(2) = transaction.network;
//
// Transaction Type - 1 Byte:
// - buffer.at(3) = transaction.type;
//
// Timestamp - 4 Bytes
// - pack4LE(&buffer.at(v1::TIMESTAMP_OFFSET), &transaction.timestamp);
//
// SenderPublicKey - 33 Bytes:
// - buffer.insert(buffer.begin() + 8, transaction.senderPublicKey.begin(), transaction.senderPublicKey.end());
//
// Fee - 8 bytes
// - pack8LE(&buffer.at(v1::FEE_OFFSET), &transaction.fee);
//
// VendorField Length - 1 Byte:
// - buffer.at(49) = transaction.vendorField.size();
//
// VendorField - 0 <=> 255 Bytes:
// - buffer.insert(buffer.begin() + 50, transaction.vendorField.begin(), transaction.vendorField.end());
//
// ---
static void serializeCommonV1(const TransactionData &transaction,
                              std::vector<uint8_t> &buffer) {
    buffer.at(v1::HEADER_OFFSET)        = transaction.header;       // 1 Byte
    buffer.at(v1::VERSION_OFFSET)       = transaction.version;      // 1 Byte
    buffer.at(v1::NETWORK_OFFSET)       = transaction.network;      // 1 Byte

    buffer.at(v1::TYPE_OFFSET) =                                    // 1 Byte
            static_cast<uint8_t>(transaction.type);

    pack4LE(&buffer.at(v1::TIMESTAMP_OFFSET),                       // 4 Bytes
            &transaction.timestamp);

    buffer.insert(buffer.begin() + v1::SENDER_PUBLICKEY_OFFSET,     // 21 Bytes
                  transaction.senderPublicKey.begin(),
                  transaction.senderPublicKey.end());

    pack8LE(&buffer.at(v1::FEE_OFFSET), &transaction.fee);          // 8 Bytes

    buffer.at(v1::VF_LEN_OFFSET) =                                  // 1 Byte
            static_cast<uint8_t>(transaction.vendorField.size());

    if (!transaction.vendorField.empty()) {
        buffer.insert(buffer.begin() + v1::VF_OFFSET,       // 0 <=> 255 Bytes
                      transaction.vendorField.begin(),
                      transaction.vendorField.end());
    }
}

////////////////////////////////////////////////////////////////////////////////
static auto serializeAsset(const TransactionData &transaction,
                           std::vector<uint8_t> &buffer,
                           const size_t &offset) -> size_t {
    switch (transaction.type) {
        case TRANSFER_TYPE:
            return Transfer::Serialize(
                    transaction.asset.transfer,
                    &buffer.at(offset));

        case SECOND_SIGNATURE_TYPE:
            return SecondSignature::Serialize(
                    transaction.asset.secondSignature,
                    &buffer.at(offset));

        case DELEGATE_REGISTRATION_TYPE:
            return DelegateRegistration::Serialize(
                    transaction.asset.delegateRegistration,
                     &buffer.at(offset));

        case VOTE_TYPE:
            return Vote::Serialize(
                    transaction.asset.vote,
                    &buffer.at(offset));

        // case MULTI_SIGNATURE_TYPE:  // TODO

        case IPFS_TYPE:
            return Ipfs::Serialize(
                    transaction.asset.ipfs,
                    &buffer.at(offset));

        case MULTI_PAYMENT_TYPE:
            return MultiPayment::Serialize(
                    transaction.asset.multiPayment,
                    buffer,
                    offset);

        // Delegate Resignation
        // No Asset Needed. Return Default of '0'.
        // case DELEGATE_RESIGNATION_TYPE:

        case HTLC_LOCK_TYPE:
            return HtlcLock::Serialize(
                    transaction.asset.htlcLock,
                    &buffer.at(offset));

        case HTLC_CLAIM_TYPE:
            return HtlcClaim::Serialize(
                    transaction.asset.htlcClaim,
                    &buffer.at(offset));

        case HTLC_REFUND_TYPE:
            return HtlcRefund::Serialize(
                    transaction.asset.htlcRefund,
                    &buffer.at(offset));

        default: return 0UL;
    };
}

////////////////////////////////////////////////////////////////////////////////
static auto serializeSignatures(const TransactionData &data,
                                std::vector<uint8_t> &buffer,
                                const size_t offset,
                                const SerializerOptions &options) -> size_t {
    if (!options.excludeSignature &&
        data.signature.size() >= SIGNATURE_ECDSA_MIN &&
        data.signature.size() <= SIGNATURE_ECDSA_MAX) {
        buffer.insert(buffer.begin() + offset,
                      data.signature.begin(),
                      data.signature.end());
    }
    else { return 0UL; }

    if (!options.excludeSecondSignature &&
        data.secondSignature.size() >= SIGNATURE_ECDSA_MIN &&
        data.secondSignature.size() <= SIGNATURE_ECDSA_MAX) {
        buffer.insert(buffer.begin() + offset + data.signature.size(),
                      data.secondSignature.begin(),
                      data.secondSignature.end());
    }
    else { return data.signature.size(); }

    return data.signature.size() + data.secondSignature.size();
}

////////////////////////////////////////////////////////////////////////////////
// Serialize Transaction Data
//
// @param const TransactionData &data
// @param const SerializerOptions &options
//
// @return std::vector<uint8_t>
//
// ---
auto Serializer::serialize(const TransactionData &data,
                           const SerializerOptions &options)
                                    -> std::vector<uint8_t>{
    std::vector<uint8_t> buffer;
    buffer.resize(TX_DEFAULT_SIZE);

    size_t assetOffset = 0UL;

    // Use v2 or v1, otherwise return an empty object.
    if (data.version == TRANSACTION_VERSION_TYPE_2) {
        serializeCommon(data, buffer);
        assetOffset = VF_OFFSET + data.vendorField.size();
    }
    else if (data.version == TRANSACTION_VERSION_TYPE_1) {
        serializeCommonV1(data, buffer);
        assetOffset = v1::VF_OFFSET + data.vendorField.size();
    }
    else { return {}; }

    size_t assetSize = serializeAsset(data, buffer, assetOffset);

    size_t signaturesSize = serializeSignatures(data,
                                                buffer,
                                                assetOffset + assetSize,
                                                options);

    buffer.resize(assetOffset + assetSize + signaturesSize);

    return buffer;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
