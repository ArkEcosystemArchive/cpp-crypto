
#include "gtest/gtest.h"

#include <arkCrypto.h>

#if 0
TEST(transactions, deserialize_delegate_registration) { // NOLINT
  // delegate_registration/second-passphrase.json
  Ark::Crypto::Transactions::Deserializer deserializer(
    "ff011e02b0b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f902950000000000"
    "09626f6c646e696e6a613045022100f21b742fa052cd18de43328e1d068539ba7cbe9d33a9dcbd862a82871383955d022005"
    "3b06d22ed3e3ad6168c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94304402207da580da4feec955edcb8e8eb36947"
    "867b439de3d28d38e58c844fd8c45b564302200e6741b6ad11c2588a57b3afd180df1e9b345d48a9c2ae98be57dced869cf38c"
  );
  auto actual = deserializer.deserialize();

  ASSERT_EQ(0xFF, actual.header);
  ASSERT_EQ(2, actual.type);
  ASSERT_EQ(1, actual.version);
  ASSERT_EQ(30, actual.network);
  ASSERT_EQ(TransactionTypes::DelegateRegistration, actual.type);
  ASSERT_EQ(41269424UL, actual.timestamp);
  ASSERT_STREQ(
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
      actual.senderPublicKey.c_str());
  ASSERT_EQ(2500000000ULL, actual.fee);
  ASSERT_EQ(0ULL, actual.amount);
  ASSERT_EQ(0, actual.expiration);
  ASSERT_STREQ(
      "bf7e018ff9c0066f7a9f51e95d3f78c08cad5dd8581325d630d64350181a91bb",
      actual.id.c_str());
  ASSERT_STREQ("boldninja", actual.asset.delegate.username.c_str());
  ASSERT_STREQ(
      "3045022100f21b742fa052cd18de43328e1d068539ba7cbe9d33a9dcbd862a82871383955d0220053b06d22ed3e3ad6168c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94",
      actual.signature.c_str());
  ASSERT_STREQ(
      "304402207da580da4feec955edcb8e8eb36947867b439de3d28d38e58c844fd8c45b564302200e6741b6ad11c2588a57b3afd180df1e9b345d48a9c2ae98be57dced869cf38c",
      actual.secondSignature.c_str());
  ASSERT_TRUE(actual.verify()));
}
#endif
