
#include "gtest/gtest.h"

#include <map>
#include <string>


#include "transactions/builder.h"
#include "transactions/transaction.h"
#include "utils/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_array) {  // NOLINT
  // Type 0 //
  auto transfer = Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                                         1,
                                         "",
                                         "Secret passphrase");

  auto tArray = transfer.toArray();

  // Amount
  ASSERT_STREQ("1", tArray["amount"].c_str());

  // Fee
  ASSERT_STREQ("10000000", tArray["fee"].c_str());

  // Id
  ASSERT_FALSE(tArray["id"].empty());

  // Recipient
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tArray["recipient"].c_str());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               tArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(tArray["signature"].empty());

  // Timestamp
  ASSERT_FALSE(tArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("0", tArray["type"].c_str());

  // Version
  ASSERT_STREQ("1", tArray["version"].c_str());

  // Type 1 //
  auto secondSignatureRegistration = Builder::buildSecondSignatureRegistration(
      "Secret passphrase",
      "Second Secret passphrase");

  auto ssArray = secondSignatureRegistration.toArray();

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

  // Type 2 //
  auto delegateRegistration = Builder::buildDelegateRegistration(
      "testName",
      "Secret passphrase");

  auto dArray = delegateRegistration.toArray();

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

  // Type 3 //
  std::vector<std::string> votes = {
    "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
    "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6"
  };

  auto vote = Builder::buildVote(votes, "Secret passphrase");

  auto vArray = vote.toArray();

  // Amount
  ASSERT_STREQ("0", vArray["amount"].c_str());

  // Asset
  ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,"
               "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
               vArray["votes"].c_str());

  // Fee
  ASSERT_STREQ("100000000", vArray["fee"].c_str());

  // Id
  ASSERT_FALSE(vArray["id"].empty());

  // Recipient
  ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF",
               vArray["recipient"].c_str());

  // SecondSignature
  ASSERT_TRUE(vArray["secondSignature"].empty());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               vArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(vArray["signature"].empty());

  //  Timestamp
  ASSERT_FALSE(vArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("3", vArray["type"].c_str());

  // Version
  ASSERT_STREQ("1", vArray["version"].c_str());
}
