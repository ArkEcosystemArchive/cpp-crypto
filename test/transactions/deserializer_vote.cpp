
#include "gtest/gtest.h"

#include <arkCrypto.h>

TEST(transactions, deserialize_vote) { // NOLINT
  // vote/second-passphrase.json
  Ark::Crypto::Transactions::Deserializer deserializer(
      "ff011e0376b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200e1f50500000000000101022cca95"
      "29ec97a772156c152a00aad155ee6708243e65c9d211a589cb5d43234d304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663d875af7e"
      "c1154448e98466e86302201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828ed2d7c53a5e8db08cb6d068304402201329882762a42d1af9"
      "079c822a9e3feefa47b7476b0afe61440637408958a64402206da179b08e31d9c784fbb23abe2c9b50353ed7881dc29787a5e8ecbee2dfda66");
  auto actual = deserializer.deserialize();

  ASSERT_EQ(0xFF, actual.header);
  ASSERT_EQ(1, actual.version);
  ASSERT_EQ(30, actual.network);
  ASSERT_EQ(TransactionTypes::Vote, actual.type);
  ASSERT_EQ(41269366UL, actual.timestamp);
  ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", actual.senderPublicKey.c_str());
  ASSERT_TRUE(100000000ULL == actual.fee);
  ASSERT_TRUE(0ULL == actual.amount);
  ASSERT_EQ(0, actual.expiration);
  ASSERT_STREQ("16f28a180cd6f3ea46c10f358a457989e956e9d355258230d0c7b07acec10b73", actual.id.c_str());
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", actual.recipient.c_str());

  std::vector<std::string> votes = {std::string("+022cca9529ec97a772156c152a00aad155ee6708243e65c9d211a589cb5d43234d")};
  ASSERT_EQ(1, actual.asset.votes.size());
  ASSERT_STREQ(votes[0].c_str(), actual.asset.votes[0].c_str());

  ASSERT_STREQ(
      "304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663d875af7ec1154448e98466e86302201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828ed2d7c53a5e8db08cb6d068",
      actual.signature.c_str());
  ASSERT_STREQ(
      "304402201329882762a42d1af9079c822a9e3feefa47b7476b0afe61440637408958a64402206da179b08e31d9c784fbb23abe2c9b50353ed7881dc29787a5e8ecbee2dfda66",
      actual.secondSignature.c_str());
  ASSERT_TRUE(actual.verify());
}
