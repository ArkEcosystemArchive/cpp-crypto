
#include "gtest/gtest.h"

#include <map>
#include <string>

#include "transactions/builder.h"
#include "utils/json.h"
using namespace Ark::Crypto;
using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_json_type_1) {  // NOLINT
  std::string ssJson;

  { // force dtor on transfer to clean up stack space
  auto secondSignatureRegistration = Builder::buildSecondSignatureRegistration(
      "Secret passphrase",
      "Second Secret passphrase");

  ssJson = secondSignatureRegistration.toJson();
  }

  const size_t ssCapacity = 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(10) + 690;
  DynamicJsonDocument ssDoc(ssCapacity);

  DeserializationError ssError = deserializeJson(ssDoc, ssJson);
  ASSERT_FALSE(ssError);

  ASSERT_STREQ("0", ssDoc["amount"].as<const char*>());

  ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104",
               ssDoc["asset"]["signature"]["publicKey"].as<const char*>());

  ASSERT_STREQ("500000000", ssDoc["fee"].as<const char*>());

  ASSERT_STRNE("", ssDoc["id"].as<const char*>());

  ASSERT_STREQ("", ssDoc["recipient"].as<const char*>());

  ASSERT_STRNE("", ssDoc["secondSignature"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               ssDoc["senderPublicKey"].as<const char*>());

  ASSERT_STRNE("", ssDoc["signature"].as<const char*>());

  ASSERT_GT(ssDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(ssDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(ssDoc["type"].as<int>(), 1);

  ASSERT_EQ(1, ssDoc["version"].as<int>());

}
