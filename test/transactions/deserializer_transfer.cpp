
#include "gtest/gtest.h"

#include "defaults/transaction_types.hpp"
#include "transactions/deserializer.h"
using namespace Ark::Crypto;

TEST(transactions, deserialize_transfer) { // NOLINT
  // transfer/passphrase-with-vendor-field.json
  Ark::Crypto::Transactions::Deserializer deserializer(
      "ff011e0007627802034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f"
      "20576f726c6400c2eb0b00000000000000001e0995750207ecaf0ccf251c1265b92ad84f553662304402205616d6e361439d67a5c2067b"
      "bfc8fce61b93061a4fa113315a1c5cf965ff6f3202200a1d99caaa98aeebcec04edd5365352500addb830c79f49b9de484ec616bb1e1");
  auto actual = deserializer.deserialize();

  ASSERT_EQ(0xFF, actual.header);
  ASSERT_EQ(1, actual.version);
  ASSERT_EQ(30, actual.network);
  ASSERT_EQ(TransactionTypes::Transfer, actual.type);
  ASSERT_EQ(41443847UL, actual.timestamp);
  ASSERT_STREQ(
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192",
      actual.senderPublicKey.c_str());
  ASSERT_TRUE(10000000ULL == actual.fee);
  ASSERT_STREQ("48656c6c6f20576f726c64", actual.vendorFieldHex.c_str());
  ASSERT_STREQ("Hello World", actual.vendorField.c_str());
  ASSERT_TRUE(200000000ULL == actual.amount);
  ASSERT_STREQ(
      "ecf558fbddd62ae42edcfcba02f402d987a94b72a7636ef1121e8625487e2a1e",
      actual.id.c_str());
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", actual.recipient.c_str());
  ASSERT_STREQ(
      "304402205616d6e361439d67a5c2067bbfc8fce61b93061a4fa113315a1c5cf965ff6f3202200a1d99caaa98aeebcec04edd5365352500addb830c79f49b9de484ec616bb1e1",
      actual.signature.c_str());
  ASSERT_TRUE(actual.verify());
}
