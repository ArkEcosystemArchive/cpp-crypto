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
#include "networks/mainnet.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/vote.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, vote) {
    const auto transaction = builder::Vote(Mainnet)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .votes(TYPE_3_VOTE)
        .signature(TYPE_3_SIGNATURE, sizeof(TYPE_3_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
