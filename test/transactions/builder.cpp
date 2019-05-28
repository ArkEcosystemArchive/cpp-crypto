
#include "gtest/gtest.h"

#include "configuration/fee.h"
#include "enums/types.h"
#include "transactions/builder.h"
using namespace Ark::Crypto::Transactions;

#include <iostream>

TEST(transactions, build_transfer) {
  const auto actual = Ark::Crypto::Transactions::Builder::buildTransfer(
      "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
      100000000ULL,
      "",
      "Secret passphrase");
  ASSERT_EQ(Ark::Crypto::Enums::Types::TRANSFER, actual.type);
  ASSERT_EQ(
      Ark::Crypto::Configuration::Fee().get(Ark::Crypto::Enums::Types::TRANSFER),
      actual.fee);
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", actual.recipientId.c_str());
  ASSERT_EQ(100000000ULL, actual.amount);
  ASSERT_TRUE(actual.vendorField.empty());
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
