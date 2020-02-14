/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/ipfs.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/ipfs.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, ipfs) {
    const auto transaction = builder::Ipfs()
        .network(COMMON_MAINNET)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_5_FEE)
        .ipfs(TYPE_5_DAG, sizeof(TYPE_5_DAG))
        .signature(TYPE_5_SIGNATURE, sizeof(TYPE_5_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
