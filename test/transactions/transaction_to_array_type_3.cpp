
#include "gtest/gtest.h"

#include <map>
#include <string>


#include "transactions/builder.h"
#include "transactions/transaction.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_array_type_3) {  // NOLINT
  std::map<std::string, std::string> vArray;

  { // force dtor on transfer to clean up stack space
  // Type 3 //
  std::vector<std::string> votes = {
    "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
    "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6"
  };

  auto vote = Builder::buildVote(votes, "Secret passphrase");

  vArray = vote.toArray();
  }

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
