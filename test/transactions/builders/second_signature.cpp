/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/second_signature.hpp"
#include "networks/mainnet.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/second_signature.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, second_signature) {
    const auto transaction = builder::SecondSignature(Mainnet)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .publicKey(TYPE_1_SECOND_PUBLICKEY)
        .signature(TYPE_1_SIGNATURE, sizeof(TYPE_1_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
