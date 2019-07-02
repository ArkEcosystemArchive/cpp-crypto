
#include "gtest/gtest.h"

#include <arkCrypto.h>

TEST(transactions, build_transfer) {
  const auto actual =
      Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                             100000000ULL,
                             "",
                             "Secret passphrase");

  ASSERT_EQ(0, actual.type);
  ASSERT_EQ(defaults::Fees::StaticFeePolicy()[actual.type], actual.fee);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
               actual.recipientId.c_str());
  ASSERT_EQ(100000000ULL, actual.amount);
  ASSERT_TRUE(actual.vendorField.empty());
}

/**/

TEST(transactions, build_transfer_custom_network) {
  static const Network MyCustomNetwork = {
    "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
    1, 0x53, 0xaa,
    "2019-04-12T13:00:00.000Z"
  };

  const Configuration myCustomConfiguration(MyCustomNetwork);

  const auto transaction = Builder::buildTransfer(
          "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
          100000000ULL,
          "this is a custom bridgechain transaction",
          "this is a top secret passphrase",
          "this is a top secret passphrase too",
          myCustomConfiguration);

  ASSERT_EQ(0, transaction.type);
  ASSERT_EQ(myCustomConfiguration.getFee(transaction.type), transaction.fee);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
               transaction.recipientId.c_str());
  ASSERT_EQ(100000000ULL, transaction.amount);
  ASSERT_STREQ("this is a custom bridgechain transaction",
               transaction.vendorField.c_str());
}

/**/

TEST(transactions, build_empty_transaction) {
  // test 0 ARKtoshi value
  const auto shouldBeEmpty = Ark::Crypto::Transactions::Builder::buildTransfer(
      "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
      0,
      "",
      "Secret passphrase");

  ASSERT_TRUE(shouldBeEmpty.recipientId.empty());
  ASSERT_EQ(0ULL, shouldBeEmpty.amount);
  ASSERT_FALSE(shouldBeEmpty.verify());
}
