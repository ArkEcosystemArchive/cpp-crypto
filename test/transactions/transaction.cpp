
#include "gtest/gtest.h"

#include <map>
#include <string>

#include <arkCrypto.h>

#include "helpers/json.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_default) {
  Transaction transaction;
  ASSERT_FALSE(transaction.verify());
};

/**/

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

  // RecipientId
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tArray["recipientId"].c_str());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               tArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(tArray["signature"].empty());

  // Timestamp
  ASSERT_FALSE(tArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("0", tArray["type"].c_str());

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

  // RecipientId
  ASSERT_TRUE(ssArray["recipientId"].empty());

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

  //  RecipientId
  ASSERT_TRUE(dArray["recipientId"].empty());

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

  // RecipientId
  ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF",
               vArray["recipientId"].c_str());

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
}

/**/

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

  ASSERT_STREQ(tDoc["amount"], "1");

  ASSERT_STREQ(tDoc["fee"], "10000000");

  ASSERT_FALSE(tDoc["id"].as<std::string>().empty());

  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
               tDoc["recipientId"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               tDoc["senderPublicKey"].as<const char*>());

  ASSERT_FALSE(tDoc["signature"].as<std::string>().empty());

  ASSERT_GT(tDoc["timestamp"].as<unsigned long>(), 50000000UL);

  ASSERT_LT(tDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(tDoc["type"].as<int>(), 0);

  // Type 1 //
  auto secondSignatureRegistration = Builder::buildSecondSignatureRegistration(
      "Secret passphrase",
      "Second Secret passphrase");

  auto ssJson = secondSignatureRegistration.toJson();

  const size_t ssCapacity = 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(10) + 690;
  DynamicJsonDocument ssDoc(ssCapacity);

  DeserializationError ssError = deserializeJson(ssDoc, ssJson);
  ASSERT_FALSE(ssError);

  ASSERT_STREQ(ssDoc["amount"], "0");

  ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104",
               ssDoc["asset"]["signature"]["publicKey"].as<const char*>());

  ASSERT_STREQ(ssDoc["fee"], "500000000");

  ASSERT_FALSE(ssDoc["id"].as<std::string>().empty());

  ASSERT_TRUE(ssDoc["recipientId"].as<std::string>().empty());

  ASSERT_FALSE(ssDoc["secondSignature"].as<std::string>().empty());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               ssDoc["senderPublicKey"].as<const char*>());

  ASSERT_FALSE(ssDoc["signature"].as<std::string>().empty());

  ASSERT_GT(ssDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(ssDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(ssDoc["type"].as<int>(), 1);

  // Type 2 //
  auto delegateRegistration = Builder::buildDelegateRegistration(
      "testName",
      "Secret passphrase");

  auto dJson = delegateRegistration.toJson();

  const size_t dCapacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 450;
  DynamicJsonDocument dDoc(dCapacity);

  DeserializationError dError = deserializeJson(dDoc, dJson);
  ASSERT_FALSE(dError);

  ASSERT_STREQ(dDoc["amount"], "0");

  ASSERT_STREQ("testName",
               dDoc["asset"]["delegate"]["username"].as<const char*>());

  ASSERT_STREQ(dDoc["fee"], "2500000000");

  ASSERT_FALSE(dDoc["id"].as<std::string>().empty());

  ASSERT_TRUE(dDoc["recipientId"].as<std::string>().empty());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               dDoc["senderPublicKey"].as<const char*>());

  ASSERT_FALSE(dDoc["signature"].as<std::string>().empty());

  ASSERT_GT(dDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(dDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(dDoc["type"].as<int>(), 2);

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

  ASSERT_STREQ(vDoc["amount"], "0");

  ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
               vDoc["asset"]["votes"][0].as<const char*>());

  ASSERT_STREQ("+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6",
               vDoc["asset"]["votes"][1].as<const char*>());

  ASSERT_STREQ(vDoc["fee"], "100000000");

  ASSERT_FALSE(vDoc["id"].as<std::string>().empty());

  ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF",
               vDoc["recipientId"].as<const char*>());

  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               vDoc["senderPublicKey"].as<const char*>());

  ASSERT_FALSE(vDoc["signature"].as<std::string>().empty());

  ASSERT_GT(vDoc["timestamp"].as<unsigned long>(), 50000000UL);
  ASSERT_LT(vDoc["timestamp"].as<unsigned long>(), 1000000000UL);

  ASSERT_EQ(vDoc["type"].as<int>(), 3);
};

/**/

TEST(transactions, transaction_empty) {
  Ark::Crypto::Transactions::Transaction transaction;
  bool isValid = transaction.verify();
  ASSERT_FALSE(isValid);
}

/**/

TEST(transactions, transaction_asset_signature) { // NOLINT
  const auto publicKeyString = "02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699";
  TransactionAsset asset;
  asset.signature.publicKey = publicKeyString;
  ASSERT_STREQ(asset.signature.publicKey.c_str(), publicKeyString);
}

/**/

TEST(transactions, transaction_asset_delegate) {
  const auto testUsername = "testUsername";
  TransactionAsset asset;
  asset.delegate.username = "testUsername";
  ASSERT_STREQ(asset.delegate.username.c_str(), testUsername);
}

/**/

TEST(transactions, transaction_asset_multisignature) {
  const auto min = 2;
  const auto lifetime = 24;
  std::vector<std::string> keysgroup = {
    "+03543c6cc3545be6bac09c82721973a052c690658283472e88f24d14739f75acc8",
    "+0276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec7a165a80731b44ae89f1fc",
    "+02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8b7422063091f4b31"
  };

  TransactionAsset asset;
  asset.multiSignature.min = min;
  asset.multiSignature.lifetime = lifetime;
  asset.multiSignature.keysgroup = keysgroup;
  ASSERT_EQ(asset.multiSignature.min, min);
  ASSERT_EQ(asset.multiSignature.lifetime, lifetime);
  ASSERT_TRUE(asset.multiSignature.keysgroup[0] == keysgroup[0]);
  ASSERT_TRUE(asset.multiSignature.keysgroup[1] == keysgroup[1]);
  ASSERT_TRUE(asset.multiSignature.keysgroup[2] == keysgroup[2]);
}
