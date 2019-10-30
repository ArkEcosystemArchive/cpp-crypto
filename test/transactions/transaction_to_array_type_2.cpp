
#include "gtest/gtest.h"

#include <map>
#include <string>


#include "transactions/builder.h"
#include "transactions/transaction.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_array_type_2) {  // NOLINT
  std::map<std::string, std::string> dArray;

  { // force dtor on transfer to clean up stack space
  // Type 2 //
  auto delegateRegistration = Builder::buildDelegateRegistration(
      "testName",
      "Secret passphrase");

  dArray = delegateRegistration.toArray();
  }
  // Amount
  ASSERT_STREQ("0", dArray["amount"].c_str());

  // Asset
  ASSERT_STREQ("testName", dArray["username"].c_str());

  // Fee
  ASSERT_STREQ("2500000000", dArray["fee"].c_str());

  // Id
  ASSERT_FALSE(dArray["id"].empty());

  //  Recipient
  ASSERT_TRUE(dArray["recipient"].empty());

  // SecondSignature
  ASSERT_TRUE(dArray["secondSignature"].empty());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               dArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(dArray["signature"].empty());

  // ASSERT_FALSE
  ASSERT_FALSE(dArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("2", dArray["type"].c_str());

  // Version
  ASSERT_STREQ("1", dArray["version"].c_str());
}
