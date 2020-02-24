/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/htlc_claim.hpp"
#include "networks/mainnet.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/htlc_claim.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, htlc_claim) {
    const auto transaction = builder::HtlcClaim(Mainnet)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_9_FEE)
        .lockTransactionId(TYPE_9_LOCK_TX_ID)
        .unlockSecret(TYPE_9_UNLOCK_SECRET)
        .signature(TYPE_9_SIGNATURE, sizeof(TYPE_9_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
