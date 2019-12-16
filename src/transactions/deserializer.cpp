/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/deserializer.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

#include "interfaces/constants.h"

#include "transactions/defaults/offsets.hpp"

#include "transactions/transaction_data.hpp"

#include "utils/packing.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize Common
//
// @param TransactionData *data: The Transaction Data destination.
// @param const std::vector<uint8_t> &buffer
//
// ---
// Internals:
//
// Header - 1 Byte:
// - data->header = buffer.at(0);
//
// Transaction Version - 1 Byte:
// - data->version = buffer.at(1);
//
// Network Version - 1 Byte:
// - data->network = buffer.at(2);
//
// TypeGroup - 4 Bytes:
// - data->typeGroup = unpack4LE(&buffer, 3); 
//
// Transaction Type - 2 Bytes:
// - data->type = unpack2LE(&buffer, 7);
//
// Nonce - 8 Bytes:
// - data->nonce = unpack8LE(&buffer, 9);
//
// SenderPublicKey - 33 Bytes:
// - std::copy_n(&buffer.at(Z) 33, data->senderPublicKey.begin());
//
// Fee - 8 bytes
// - data->fee = unpack8LE(&buffer, 50);
//
// VendorField Length - 1 Byte:
// - buffer.at(58);
//
// VendorField - 0 - 255 Bytes:
// - data->vendorField.insert(data->vendorField.begin(),
//                            &buffer.at(59),
//                            &buffer.at(59 + data->vendorField.size()));
//
// ---
static void deserializeCommon(TransactionData *data,
                              const std::vector<uint8_t> &buffer) {
    data->header        = buffer.at(HEADER_OFFSET);                 // 1 Byte
    data->version       = buffer.at(VERSION_OFFSET);                // 1 Byte
    data->network       = buffer.at(NETWORK_OFFSET);                // 1 Byte

    data->typeGroup     = unpack4LE(buffer, TYPEGROUP_OFFSET);      // 4 Bytes

    data->type          = unpack2LE(buffer, TYPE_OFFSET);           // 2 Bytes
    
    data->nonce         = unpack8LE(buffer, NONCE_OFFSET);          // 8 Bytes

    std::copy_n(&buffer.at(SENDER_PUBLICKEY_OFFSET),                // 21 Bytes
                PUBLICKEY_COMPRESSED_LEN,
                data->senderPublicKey.begin());

    data->fee           = unpack8LE(buffer, FEE_OFFSET);            // 8 Bytes

    if (buffer.at(VF_LEN_OFFSET) != 0U) {
        data->vendorField.insert(                           // 0 <=> 255 Bytes
                data->vendorField.begin(),
                &buffer.at(VF_OFFSET),
                &buffer.at(VF_OFFSET + buffer.at(VF_LEN_OFFSET)));
    };
}

////////////////////////////////////////////////////////////////////////////////
// Deserialize Common v1
//
// @param TransactionData *data: The Transaction Data destination.
// @param const std::vector<uint8_t> &buffer
//
// ---
// Internals:
//
// Header - 1 Byte:
// - data->header = buffer.at(0);
//
// Transaction Version - 1 Byte:
// - data->version = buffer.at(1);
//
// Network Version - 1 Byte:
// - data->network = buffer.at(2);
//
// Transaction Type - 1 Byte:
// - data->type = buffer.at(3);
//
// Timestamp - 4 Bytes
// - data->timestamp = unpack4LE(buffer, 4);
//
// SenderPublicKey - 33 Bytes:
// - std::copy_n(&buffer.at(8), 33, data->senderPublicKey.begin());
//
// Fee - 8 bytes
// - data->fee = unpack8LE(buffer, 41);
//
// VendorField Length - 1 Byte:
// - buffer.at(49)
//
// VendorField - 0 - 255 Bytes:
// - data->vendorField.insert(data->vendorField.begin(),
//                            &buffer.at(50),
//                            &buffer.at(50 + buffer.at(49)));
//
// ---
static void deserializeCommonV1(TransactionData *data,
                                const std::vector<uint8_t> &buffer) {
    data->header        = buffer.at(HEADER_OFFSET);                 // 1 Byte
    data->version       = buffer.at(VERSION_OFFSET);                // 1 Byte
    data->network       = buffer.at(NETWORK_OFFSET);                // 1 Byte

    data->type          = buffer.at(v1::TYPE_OFFSET);               // 1 Bytes

    data->timestamp     = unpack4LE(buffer, v1::TIMESTAMP_OFFSET);  // 4 Bytes

    std::copy_n(&buffer.at(v1::SENDER_PUBLICKEY_OFFSET),            // 33 Bytes
                PUBLICKEY_COMPRESSED_LEN,
                data->senderPublicKey.begin());

    data->fee        = unpack8LE(buffer, v1::FEE_OFFSET);           // 8 Bytes

    if (buffer.at(v1::VF_LEN_OFFSET) != 0U) {
        data->vendorField.insert(                           // 0 <=> 255 Bytes
                data->vendorField.begin(),
                &buffer.at(v1::VF_OFFSET),
                &buffer.at(v1::VF_OFFSET + buffer.at(v1::VF_LEN_OFFSET)));
    };
}

////////////////////////////////////////////////////////////////////////////////
static auto deserializeAsset(TransactionData *transaction,
                             const std::vector<uint8_t> &buffer,
                             const size_t &offset) -> size_t {
    switch (transaction->type) {
        // Transfer
        case TRANSFER_TYPE:
            return Transfer::Deserialize(
                    &transaction->asset.transfer,
                    &buffer.at(offset));

        // Second Signature Registration
        case SECOND_SIGNATURE_TYPE:
            return SecondSignature::Deserialize(
                    &transaction->asset.secondSignature,
                    &buffer.at(offset));

        // Delegate Registration
        case DELEGATE_REGISTRATION_TYPE:
            return DelegateRegistration::Deserialize(
                    &transaction->asset.delegateRegistration,
                    &buffer.at(offset));

        // Vote
        case VOTE_TYPE:
            return Vote::Deserialize(
                    &transaction->asset.vote,
                    &buffer.at(offset));

        // // MultiSignature Registration
        // case MULTI_SIGNATURE_TYPE:  // TODO

        // Ipfs
        case IPFS_TYPE:
            return Ipfs::Deserialize(
                    &transaction->asset.ipfs,
                    &buffer.at(offset));

        // MultiPayment
        case MULTI_PAYMENT_TYPE:
            return MultiPayment::Deserialize(
                    &transaction->asset.multiPayment,
                    &buffer.at(offset));

        // Delegate Resignation
        // No Asset Needed. Return Default of '0'.
        // case DELEGATE_RESIGNATION_TYPE:

        // Htlc Lock
        case HTLC_LOCK_TYPE:
            return HtlcLock::Deserialize(
                    &transaction->asset.htlcLock,
                    &buffer.at(offset));

        // Htlc Claim
        case HTLC_CLAIM_TYPE:
            return HtlcClaim::Deserialize(
                    &transaction->asset.htlcClaim,
                    &buffer.at(offset));

        // Htlc Claim
        case HTLC_REFUND_TYPE:
            return HtlcRefund::Deserialize(
                    &transaction->asset.htlcRefund,
                    &buffer.at(offset));

        default: return 0UL;
    }
}

////////////////////////////////////////////////////////////////////////////////
static void deserializeSignatures(TransactionData *transaction,
                                  const uint8_t *buffer,
                                  const size_t &size) {
    size_t signatureLength = buffer[1] == 0U ? 0U : 2U + buffer[1];
    if (signatureLength >= SIGNATURE_ECDSA_MIN &&
        signatureLength <= SIGNATURE_ECDSA_MAX) {
        transaction->signature.resize(signatureLength);
        std::copy_n(buffer,
                    transaction->signature.size(),
                    transaction->signature.begin());
    }

    size_t secondSignatureLength = size - signatureLength;
    if (secondSignatureLength >= SIGNATURE_ECDSA_MIN &&
        secondSignatureLength <= SIGNATURE_ECDSA_MAX) {
        transaction->secondSignature.resize(secondSignatureLength);
        std::copy_n(buffer + signatureLength,
                    transaction->secondSignature.size(),
                    transaction->secondSignature.begin());
    }
}

////////////////////////////////////////////////////////////////////////////////
// Deserialize Transaction Data
//
// @param TransactionData *data
// @param const std::vector<uint8_t> &buffer
//
// ---
auto Deserializer::deserialize(TransactionData *data,
                               const std::vector<uint8_t> &buffer) -> bool {
    size_t assetOffset = 0UL;

    // Use v2 or v1, otherwise return with no changes to the Tx Data.
    // v2
    if (buffer.at(VERSION_OFFSET) == TRANSACTION_VERSION_TYPE_2) {
        deserializeCommon(data, buffer);
        assetOffset = VF_OFFSET + data->vendorField.size();
    }
    // v1
    else if(buffer.at(VERSION_OFFSET) == TRANSACTION_VERSION_TYPE_1) {
        deserializeCommonV1(data, buffer);
        assetOffset = v1::VF_OFFSET + data->vendorField.size();
    }
    else { return false; }

    size_t assetSize = deserializeAsset(data, buffer, assetOffset);

    deserializeSignatures(data,
                          &buffer.at(assetOffset + assetSize),
                          buffer.size() - assetOffset - assetSize);

    return true;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
