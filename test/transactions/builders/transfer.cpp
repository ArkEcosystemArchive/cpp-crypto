/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/builders/transfer.hpp"

#include "interfaces/constants.h"

#include "common/configuration.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
#include "transactions/types/fixtures/common.hpp"
#include "transactions/types/fixtures/transfer.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builders, transfer_address_hash) {
    const auto transaction = builder::Transfer()
        .network(COMMON_MAINNET)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_0_FEE)
        .amount(TYPE_0_AMOUNT)
        .expiration(TYPE_0_EXPIRATION)
        .recipientId(TYPE_0_RECIPIENT)
        .signature(TYPE_0_SIGNATURE, sizeof(TYPE_0_SIGNATURE))
        .build();

    ASSERT_EQ(COMMON_VERSION_V2,    transaction.data.version);
    ASSERT_EQ(COMMON_MAINNET,       transaction.data.network);
    ASSERT_EQ(COMMON_TYPEGROUP,     transaction.data.typeGroup);
    ASSERT_EQ(TYPE_0_TYPE,          transaction.data.type);
    ASSERT_EQ(COMMON_NONCE,         transaction.data.nonce);

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          transaction.data.senderPublicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));

    ASSERT_EQ(TYPE_0_FEE,           transaction.data.fee);

    ASSERT_EQ(TYPE_0_AMOUNT, transaction.data.asset.transfer.amount);

    ASSERT_EQ(TYPE_0_EXPIRATION, transaction.data.asset.transfer.expiration);

    ASSERT_TRUE(array_cmp(TYPE_0_RECIPIENT,
                          transaction.data.asset.transfer.recipientId.data(),
                          ADDRESS_HASH_LEN));

    ASSERT_TRUE(array_cmp(TYPE_0_SIGNATURE,
                          transaction.data.signature.data(),
                          sizeof(TYPE_0_SIGNATURE)));

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builder, transfer_address_string) {
    const std::vector<uint8_t> signature = {
        TYPE_0_SIGNATURE,
        TYPE_0_SIGNATURE + sizeof(TYPE_0_SIGNATURE)
    };

    const auto transaction = builder::Transfer()
        .network(COMMON_MAINNET)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_0_FEE)
        .amount(TYPE_0_AMOUNT)
        .expiration(TYPE_0_EXPIRATION)
        .recipientId(TYPE_0_RECIPIENT_ID_STRING)
        .signature(TYPE_0_SIGNATURE, sizeof(TYPE_0_SIGNATURE))
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builder, transfer_sign) {
    const auto transaction = builder::Transfer()
        .network(COMMON_MAINNET)
        .nonce(COMMON_NONCE)
        .fee(TYPE_0_FEE)
        .amount(TYPE_0_AMOUNT)
        .expiration(TYPE_0_EXPIRATION)
        .recipientId(TYPE_0_RECIPIENT)
        .sign(fixtures::Passphrase)
        .build();

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builder, transfer_sign_configuration) {
    const Network Radians = {
        "f39a61f04d6136a690a0b675ef6eedbd053665bd343b4e4f03311f12065fb875",
        1, 0xCE, 0x41,
        "2019-10-25T09:05:40.856Z"
    };

    const Configuration radiansCfg(Radians);

    const AddressHash radiansRecipient = {
        65, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
        90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

    auto transaction = builder::Transfer(radiansCfg)
        .nonce(COMMON_NONCE)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .fee(TYPE_0_FEE)
        .amount(TYPE_0_AMOUNT)
        .expiration(TYPE_0_EXPIRATION)
        .recipientId(radiansRecipient.data())
        .build();

    transaction.sign(fixtures::Passphrase);

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_builder, transfer_sign_vendorfield_second_signature) {
    const auto transaction = builder::Transfer()
        .network(COMMON_MAINNET)
        .nonce(COMMON_NONCE)
        .fee(TYPE_0_FEE)
        .vendorField(fixtures::MessageString)
        .amount(TYPE_0_AMOUNT)
        .expiration(TYPE_0_EXPIRATION)
        .recipientId(TYPE_0_RECIPIENT)
        .sign(fixtures::Passphrase)
        .secondSign(fixtures::SecondPassphrase)
        .build();

    ASSERT_TRUE(transaction.verify());
}
