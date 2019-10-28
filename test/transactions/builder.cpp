
#include "gtest/gtest.h"

#include "transactions/builder.h"
#include "common/fee_policy.hpp"
using namespace Ark::Crypto::Transactions;
using namespace Ark::Crypto;

TEST(transactions, build_transfer) {
  const auto actual =
      Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                             100000000ULL,
                             "",
                             "Secret passphrase");

  ASSERT_EQ(0, actual.type);
  ASSERT_EQ(StaticFeePolicy[actual.type], actual.fee);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
               actual.recipient.c_str());
  ASSERT_EQ(100000000ULL, actual.amount);
  ASSERT_TRUE(actual.vendorField.empty());
}

TEST(transactions, build_empty_transaction) {
  // test 0 ARKtoshi value
  const auto shouldBeEmpty = Ark::Crypto::Transactions::Builder::buildTransfer(
      "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
      0,
      "",
      "Secret passphrase");

  ASSERT_TRUE(shouldBeEmpty.recipient.empty());
  ASSERT_EQ(0ULL, shouldBeEmpty.amount);
  ASSERT_FALSE(shouldBeEmpty.verify());
}
