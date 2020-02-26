/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/htlc_refund.hpp"
#include "networks/mainnet.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/htlc_refund.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, htlc_refund) {
    const auto transaction = builder::HtlcRefund(Mainnet)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .lockTransactionId(TYPE_10_LOCK_TX_ID)
        .signature(TYPE_10_SIGNATURE, sizeof(TYPE_10_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
