
#include "gtest/gtest.h"

#include "transactions/builder.h"
using namespace Ark::Crypto::Transactions;

#include "common/network.hpp"
using namespace Ark::Crypto;

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
               transaction.recipient.c_str());
  ASSERT_EQ(100000000ULL, transaction.amount);
  ASSERT_STREQ("this is a custom bridgechain transaction",
               transaction.vendorField.c_str());
}
