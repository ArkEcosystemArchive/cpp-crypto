
#include "gtest/gtest.h"

#include <map>
#include <string>


#include "transactions/builder.h"
#include "transactions/transaction.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_array_type_1) {  // NOLINT
  std::map<std::string, std::string> ssArray;

  { // force dtor on transfer to clean up stack space
  // Type 1 //
  auto secondSignatureRegistration = Builder::buildSecondSignatureRegistration(
      "Secret passphrase",
      "Second Secret passphrase");

  ssArray = secondSignatureRegistration.toArray();
  }

  // Amount
  ASSERT_STREQ("0", ssArray["amount"].c_str());

  // Asset
  ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104",
               ssArray["publicKey"].c_str());

  // Fee
  ASSERT_STREQ("500000000", ssArray["fee"].c_str());

  // Id
  ASSERT_FALSE(ssArray["id"].empty());

  // Recipient
  ASSERT_TRUE(ssArray["recipient"].empty());

  // SecondSignature
  ASSERT_FALSE(ssArray["secondSignature"].empty());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               ssArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(ssArray["signature"].empty());

  // Timestamp
  ASSERT_FALSE(ssArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("1", ssArray["type"].c_str());

  // Version
  ASSERT_STREQ("1", ssArray["version"].c_str());
}
