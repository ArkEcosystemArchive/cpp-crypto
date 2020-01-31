/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/mapping/mapping.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

#include "interfaces/constants.h"

#include "transactions/defaults/types.hpp"

#include "transactions/transaction_data.hpp"

#include "transactions/mapping/labels.hpp"

#include "utils/hex.hpp"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

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
static void mapCommon(std::map<std::string, std::string> &map,
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
static void mapAsset(std::map<std::string, std::string> &map,
                     const TransactionData &data) {
    switch (data.type) {
        // Tranfer
        case TRANSFER_TYPE:
            Transfer::addToMap(data.asset.transfer, map);

        // Second Signature Registration
        case SECOND_SIGNATURE_TYPE:
            SecondSignature::addToMap(data.asset.secondSignature, map);

        // Delegate Registration
        case DELEGATE_REGISTRATION_TYPE:
            DelegateRegistration::addToMap(data.asset.delegateRegistration, map);

        // Vote
        case VOTE_TYPE:
            Vote::addToMap(data.asset.vote, map);

        // MultiSignature Registration
        // case MULTI_SIGNATURE_TYPE:  // TODO

        // Ipfs
        case IPFS_TYPE:
            Ipfs::addToMap(data.asset.ipfs, map);

        // MultiPayment
        case MULTI_PAYMENT_TYPE:
            MultiPayment::addToMap(data.asset.multiPayment, map);

        // Delegate Resignation
        // No Asset Needed
        // case DELEGATE_RESIGNATION_TYPE:

        // Htlc Lock
        case HTLC_LOCK_TYPE:
            HtlcLock::addToMap(data.asset.htlcLock, map);

        // Htlc Claim
        case HTLC_CLAIM_TYPE:
            HtlcClaim::addToMap(data.asset.htlcClaim, map);

        // Htlc Refund
        case HTLC_REFUND_TYPE:
            HtlcRefund::addToMap(data.asset.htlcRefund, map);

        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Add Common Extra Map data
//
// - TransactionId
// - Signature (if present)
// - Second Signature (if present)
//
// ---
static void mapExtras(std::map<std::string, std::string> &map,
                      const TransactionData &data) {
    // Transaction Id
    map.emplace(KEY_ID_LABEL, BytesToHex(data.id));

    // Signature
    if (!data.signature.empty() && data.signature.at(1) != 0U) {
        map.emplace(KEY_SIGNATURE_LABEL,
                    BytesToHex(data.signature));
    }

    // Second Signature
    if (!data.secondSignature.empty() && data.secondSignature.at(1) != 0U) {
        map.emplace(KEY_SECOND_SIGNATURE_LABEL,
                    BytesToHex(data.secondSignature));
    }
}

////////////////////////////////////////////////////////////////////////////////
// Extract a standard string-Map from a Transaction's data.
auto Mapping::fromTransactionData(const TransactionData &data)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    mapCommon(map, data);
    mapAsset(map, data);
    mapExtras(map, data);

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
