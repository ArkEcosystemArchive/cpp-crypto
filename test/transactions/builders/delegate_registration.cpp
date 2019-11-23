/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/delegate_registration.hpp"

#include "interfaces/constants.h"

#include "transactions/types/fixtures/delegate_registration.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_builders, delegate_registration) {
    const auto transaction = builder::DelegateRegistration()
        .network(COMMON_MAINNET)
        .type(TYPE_2_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .username(TYPE_2_USERNAME, sizeof(TYPE_2_USERNAME))
        .fee(TYPE_2_FEE)
        .signature(TYPE_2_SIGNATURE, sizeof(TYPE_2_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_builders, delegate_registration_string) {
    const auto transaction = builder::DelegateRegistration()
        .network(COMMON_MAINNET)
        .type(TYPE_2_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .username(TYPE_2_USERNAME_STRING)
        .fee(TYPE_2_FEE)
        .signature(TYPE_2_SIGNATURE, sizeof(TYPE_2_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
