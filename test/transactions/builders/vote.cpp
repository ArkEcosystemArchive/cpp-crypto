/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/vote.hpp"

#include "interfaces/constants.h"

#include "transactions/types/fixtures/vote.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_builders, vote) {
    const auto transaction = builder::Vote()
        .network(COMMON_MAINNET)
        .type(TYPE_3_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .fee(TYPE_3_FEE)
        .votes(TYPE_3_VOTE)
        .signature(TYPE_3_SIGNATURE, sizeof(TYPE_3_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
