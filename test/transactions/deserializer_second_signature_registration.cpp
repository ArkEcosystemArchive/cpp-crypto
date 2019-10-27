
#include "gtest/gtest.h"

#include <arkCrypto.h>

TEST(transactions, deserialize_second_signature_registration) { // NOLINT
  // second_signature_registration/second-passphrase.json
  Ark::Crypto::Transactions::Deserializer deserializer(
      "ff011e013bc27502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000003"
      "699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609304402202aab49477dd3531e4473196d08fbd7"
      "c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c");
  auto actual = deserializer.deserialize();

  ASSERT_EQ(0xFF, actual.header);
  ASSERT_EQ(1, actual.version);
  ASSERT_EQ(30, actual.network);
  ASSERT_EQ(TransactionTypes::SecondSignatureRegistration, actual.type);
  ASSERT_EQ(41271867UL, actual.timestamp);
  ASSERT_STREQ(
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
      actual.senderPublicKey.c_str());
  ASSERT_TRUE(500000000ULL == actual.fee);
  ASSERT_TRUE(0UL == actual.amount);
  ASSERT_EQ(0, actual.expiration);
  ASSERT_STREQ(
      "6d1615924d172d352c8f44d4ded84cbbece3c03ebb3e4fc3f3334784ae332590",
      actual.id.c_str());
  ASSERT_STREQ(
      "03699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609",
      actual.asset.signature.publicKey.c_str());
  ASSERT_STREQ(
      "304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c",
      actual.signature.c_str());
  ASSERT_TRUE(actual.verify());

  // special case as the type 1 transaction itself has no recipient
  const auto publicKey = Ark::Crypto::identities::PublicKey::fromHex(actual.senderPublicKey.c_str());
  const auto address = Ark::Crypto::identities::Address::fromPublicKey(publicKey.toBytes().data(), actual.network);
  ASSERT_STREQ(address.toString().c_str(), actual.recipient.c_str());
}
