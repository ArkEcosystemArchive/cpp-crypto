
#include "gtest/gtest.h"

#include <map>
#include <string>

#include <arkCrypto.h>

#include "utils/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_json_type_0) {  // NOLINT
  std::string tJson;

  { // force dtor on transfer to clean up stack space
  auto transfer = Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                                         1,
                                         "",
                                         "Secret passphrase");

  tJson = transfer.toJson();
  }

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

}
