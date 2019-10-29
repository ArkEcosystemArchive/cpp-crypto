
#include "gtest/gtest.h"

#include <map>
#include <string>

#include <arkCrypto.h>

#include "utils/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_json_type_3) {  // NOLINT
  std::string vJson;
  { // force dtor on transfer to clean up stack space
  std::vector<std::string> votes = {
    "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,"
    "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6"
  };
  auto vote = Builder::buildVote(votes, "Secret passphrase");
  vJson = vote.toJson();
  }

  const size_t vCapacity = JSON_ARRAY_SIZE(1)
                           + JSON_OBJECT_SIZE(1)
                           + JSON_OBJECT_SIZE(9)
                           + 700;
  DynamicJsonDocument vDoc(vCapacity);

  DeserializationError vError = deserializeJson(vDoc, vJson);
  ASSERT_FALSE(vError);

  ASSERT_STREQ("0", vDoc["amount"].as<const char*>());

  ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
               vDoc["asset"]["votes"][0].as<const char*>());

  ASSERT_STREQ("+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
               vDoc["asset"]["votes"][1].as<const char*>());

  ASSERT_STREQ("100000000", vDoc["fee"].as<const char*>());

  ASSERT_STRNE("", vDoc["id"].as<const char*>());

  ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF",
               vDoc["recipient"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               vDoc["senderPublicKey"].as<const char*>());

  ASSERT_STRNE("", vDoc["signature"].as<const char*>());

  ASSERT_GT(vDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(vDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(vDoc["type"].as<int>(), 3);

  ASSERT_EQ(1, vDoc["version"].as<int>());
}
