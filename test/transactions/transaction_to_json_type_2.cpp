
#include "gtest/gtest.h"

#include <map>
#include <string>

#include <arkCrypto.h>

#include "utils/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_json_type_2) {  // NOLINT
  std::string dJson;

  { // force dtor on transfer to clean up stack space
  auto delegateRegistration = Builder::buildDelegateRegistration(
      "testName",
      "Secret passphrase");

  dJson = delegateRegistration.toJson();
  }

  const size_t dCapacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 450;
  DynamicJsonDocument dDoc(dCapacity);

  DeserializationError dError = deserializeJson(dDoc, dJson);
  ASSERT_FALSE(dError);

  ASSERT_STREQ("0", dDoc["amount"].as<const char*>());

  ASSERT_STREQ("testName",
               dDoc["asset"]["delegate"]["username"].as<const char*>());

  ASSERT_STREQ("2500000000", dDoc["fee"].as<const char*>());

  ASSERT_STRNE("", dDoc["id"].as<const char*>());

  ASSERT_STREQ("", dDoc["recipient"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               dDoc["senderPublicKey"].as<const char*>());

  ASSERT_STRNE("", dDoc["signature"].as<const char*>());

  ASSERT_GT(dDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(dDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(dDoc["type"].as<int>(), 2);

  ASSERT_EQ(1, dDoc["version"].as<int>());

}
