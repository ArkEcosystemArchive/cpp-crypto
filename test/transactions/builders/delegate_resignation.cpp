/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/delegate_resignation.hpp"

#include "interfaces/constants.h"

#include "fixtures/identity.hpp"
#include "transactions/types/fixtures/delegate_registration.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, delegate_resignation) {
    auto transaction = builder::DelegateResignation()
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_2_FEE)
        .sign(fixtures::Passphrase)
        .build();

    ASSERT_TRUE(transaction.verify());
}
