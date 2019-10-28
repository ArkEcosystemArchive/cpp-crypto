
#include "gtest/gtest.h"

#include <map>
#include <string>

#include <arkCrypto.h>

#include "utils/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_json) {  // NOLINT
  //  Type 0 //
  auto transfer = Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                                         1,
                                         "",
                                         "Secret passphrase");

  auto tJson = transfer.toJson();

  const size_t tCapacity = JSON_OBJECT_SIZE(8) + 450;
  DynamicJsonDocument tDoc(tCapacity);

  DeserializationError tError = deserializeJson(tDoc, tJson);
  ASSERT_FALSE(tError);

  ASSERT_STREQ("1", tDoc["amount"].as<const char*>());

  ASSERT_STREQ("10000000", tDoc["fee"].as<const char*>());

  ASSERT_STRNE("", tDoc["id"].as<const char*>());

  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
               tDoc["recipient"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               tDoc["senderPublicKey"].as<const char*>());

  ASSERT_STRNE("", tDoc["signature"].as<const char*>());

  ASSERT_GT(tDoc["timestamp"].as<unsigned long>(), 50000000UL);

  ASSERT_LT(tDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(tDoc["type"].as<int>(), 0);

  ASSERT_EQ(1, tDoc["version"].as<int>());

  // Type 1 //
  auto secondSignatureRegistration = Builder::buildSecondSignatureRegistration(
      "Secret passphrase",
      "Second Secret passphrase");

  auto ssJson = secondSignatureRegistration.toJson();

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

  // Type 2 //
  auto delegateRegistration = Builder::buildDelegateRegistration(
      "testName",
      "Secret passphrase");

  auto dJson = delegateRegistration.toJson();

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

  // Type 3 //
  std::vector<std::string> votes = {
    "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,"
    "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6"
  };

  auto vote = Builder::buildVote(votes, "Secret passphrase");

  auto vJson = vote.toJson();

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
