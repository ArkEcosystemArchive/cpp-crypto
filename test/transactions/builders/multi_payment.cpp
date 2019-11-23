/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/multi_payment.hpp"

#include "interfaces/constants.h"

#include "transactions/types/fixtures/multi_payment.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_builders, multi_payment) {
    const auto transaction = builder::MultiPayment()
        .type(TYPE_6_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .fee(TYPE_6_FEE)
        .n_payments(TYPE_6_N_PAYMENTS)
        .amounts(TYPE_6_AMOUNTS)
        .addresses(TYPE_6_ADDRESSES)
        .signature(TYPE_6_SIGNATURE, sizeof(TYPE_6_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
