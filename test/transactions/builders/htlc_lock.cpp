/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/htlc_lock.hpp"

#include "interfaces/constants.h"

#include "transactions/types/fixtures/htlc_lock.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, htlc_lock) {
    const auto transaction = builder::HtlcLock()
        .network(COMMON_MAINNET)
        .type(TYPE_8_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .fee(TYPE_8_FEE)
        .amount(TYPE_8_AMOUNT)
        .secretHash(TYPE_8_SECRET_HASH)
        .expirationType(TYPE_8_EXPIRATION_TYPE)
        .expiration(TYPE_8_EXPIRATION_VALUE)
        .recipientId(TYPE_8_RECIPIENT)
        .signature(TYPE_8_SIGNATURE, sizeof(TYPE_8_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, htlc_lock_string) {
    const auto transaction = builder::HtlcLock()
        .network(COMMON_MAINNET)
        .type(TYPE_8_TYPE)
        .nonce(COMMON_NONCE)
        .senderPublicKey(COMMON_PUBLICKEY)
        .fee(TYPE_8_FEE)
        .amount(TYPE_8_AMOUNT)
        .secretHash(TYPE_8_SECRET_HASH)
        .expirationType(TYPE_8_EXPIRATION_TYPE)
        .expiration(TYPE_8_EXPIRATION_VALUE)
        .recipientId(TYPE_8_RECIPIENT_STRING)
        .signature(TYPE_8_SIGNATURE, sizeof(TYPE_8_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}
