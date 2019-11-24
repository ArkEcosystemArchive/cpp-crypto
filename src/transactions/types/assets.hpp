/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_ASSETS_HPP
#define ARK_TRANSACTIONS_TYPES_ASSETS_HPP

#include "transactions/defaults/types.hpp"

#include "transactions/types/transfer.hpp"
#include "transactions/types/second_signature.hpp"
#include "transactions/types/delegate_registration.hpp"
#include "transactions/types/vote.hpp"
// #include "transactions/types/multi_signature.hpp"
#include "transactions/types/ipfs.hpp"
#include "transactions/types/multi_payment.hpp"
#include "transactions/types/delegate_resignation.hpp"
#include "transactions/types/htlc_lock.hpp"
#include "transactions/types/htlc_claim.hpp"
#include "transactions/types/htlc_refund.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// AIP-11 Transaction Assets
typedef struct tx_asset_t {
    Transfer                    transfer;               // Type 0
    SecondSignature             secondSignature;        // Type 1
    DelegateRegistration        delegateRegistration;   // Type 2
    Vote                        vote;                   // Type 3
    // MultiSignature              multiSignature;         // Type 4
    Ipfs                        ipfs;                   // Type 5
    MultiPayment                multiPayment;           // Type 6
    DelegateResignation         delegateResignation;    // Type 7
    HtlcLock                    htlcLock;               // Type 8
    HtlcClaim                   htlcClaim;              // Type 9
    HtlcRefund                  htlcRefund;             // Type 10
} Asset;

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
