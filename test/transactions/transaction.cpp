#include "gtest/gtest.h"

#include "transactions/builder.h"
#include "helpers/json.h"

#include <map>
#include <string>

TEST(transactions, transaction_to_array) {
    //  Type 0
    auto transfer = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 1, "", "Secret passphrase");
    std::map<std::string, std::string> tArray = transfer.toArray();

    //  Amount
    ASSERT_STREQ("1", tArray["amount"].c_str());
    //  Fee
    ASSERT_STREQ("10000000", tArray["fee"].c_str());
    //  Id
    ASSERT_STRNE("", tArray["id"].c_str());
    //  RecipientId
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tArray["recipientId"].c_str());
    //  SenderPublicKey
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", tArray["senderPublicKey"].c_str());
    //  Signature
    ASSERT_STRNE("", tArray["signature"].c_str());
    //  Timestamp
    ASSERT_STRNE("", tArray["timestamp"].c_str());
    //  Type
    ASSERT_STREQ("0", tArray["type"].c_str());


    //  Type 1
    auto secondSignatureRegistration = Ark::Crypto::Transactions::Builder::buildSecondSignatureRegistration("Secret passphrase", "Second Secret passphrase");
    std::map<std::string, std::string> ssArray = secondSignatureRegistration.toArray();

    //  Amount
    ASSERT_STREQ("0", ssArray["amount"].c_str());
    //  Asset
    ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104", ssArray["publicKey"].c_str());
    //  Fee
    ASSERT_STREQ("500000000", ssArray["fee"].c_str());
    //  Id
    ASSERT_STRNE("", ssArray["id"].c_str());
    //  RecipientId
    ASSERT_STREQ("", ssArray["recipientId"].c_str());
    //  SecondSignature
    ASSERT_STRNE("", ssArray["secondSignature"].c_str());
    //  SenderPublicKey
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", ssArray["senderPublicKey"].c_str());
    //  Signature
    ASSERT_STRNE("", ssArray["signature"].c_str());
    //  Timestamp
    ASSERT_STRNE("", ssArray["timestamp"].c_str());
    //  Type
    ASSERT_STREQ("1", ssArray["type"].c_str());


    //  Type 2
    auto delegateRegistration = Ark::Crypto::Transactions::Builder::buildDelegateRegistration("testName", "Secret passphrase");
    std::map<std::string, std::string> dArray = delegateRegistration.toArray();

    //  Amount
    ASSERT_STREQ("0", dArray["amount"].c_str());
    //  Asset
    ASSERT_STREQ("testName", dArray["username"].c_str());
    //  Fee
    ASSERT_STREQ("2500000000", dArray["fee"].c_str());
    //  Id
    ASSERT_STRNE("", dArray["id"].c_str());
    //  RecipientId
    ASSERT_STREQ("", dArray["recipientId"].c_str());
    //  SecondSignature
    ASSERT_STREQ("", dArray["secondSignature"].c_str());
    //  SenderPublicKey
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", dArray["senderPublicKey"].c_str());
    //  Signature
    ASSERT_STRNE("", dArray["signature"].c_str());
    //  Timestamp
    ASSERT_STRNE("", dArray["timestamp"].c_str());
    //  Type
    ASSERT_STREQ("2", dArray["type"].c_str());


    //  Type 3
    std::vector<std::string> votes = { "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6" };
    auto vote = Ark::Crypto::Transactions::Builder::buildVote(votes, "Secret passphrase");
    std::map<std::string, std::string> vArray = vote.toArray();

    //  Amount
    ASSERT_STREQ("0", vArray["amount"].c_str());
    //  Asset
    ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vArray["votes"].c_str());
    //  Fee
    ASSERT_STREQ("100000000", vArray["fee"].c_str());
    //  Id
    ASSERT_STRNE("", vArray["id"].c_str());
    //  RecipientId
    ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF", vArray["recipientId"].c_str());
    //  SecondSignature
    ASSERT_STREQ("", vArray["secondSignature"].c_str());
    //  SenderPublicKey
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", vArray["senderPublicKey"].c_str());
    //  Signature
    ASSERT_STRNE("", vArray["signature"].c_str());
    //  Timestamp
    ASSERT_STRNE("", vArray["timestamp"].c_str());
    //  Type
    ASSERT_STREQ("3", vArray["type"].c_str());
}

TEST(transactions, transaction_to_json) {

    //  Type 0
    auto transfer = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 1, "", "Secret passphrase");
    std::string tJson = transfer.toJson();

    const size_t tCapacity = JSON_OBJECT_SIZE(8) + 450;
    DynamicJsonDocument tDoc(tCapacity);

    DeserializationError tError = deserializeJson(tDoc, tJson);
    ASSERT_FALSE(tError);

    ASSERT_EQ(tDoc["amount"], 1);
    ASSERT_EQ(tDoc["fee"], 10000000);
    ASSERT_STRNE("", tDoc["id"].as<const char*>());
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tDoc["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", tDoc["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", tDoc["signature"].as<const char*>());
    ASSERT_GT(tDoc["timestamp"], 50000000);
    ASSERT_LT(tDoc["timestamp"], 1000000000);
    ASSERT_EQ(tDoc["type"], 0);


    //  Type 1
    auto secondSignatureRegistration = Ark::Crypto::Transactions::Builder::buildSecondSignatureRegistration("Secret passphrase", "Second Secret passphrase");
    std::string ssJson = secondSignatureRegistration.toJson();

    const size_t ssCapacity = 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(10) + 690;
    DynamicJsonDocument ssDoc(ssCapacity);

    DeserializationError ssError = deserializeJson(ssDoc, ssJson);
    ASSERT_FALSE(ssError);


    ASSERT_EQ(ssDoc["amount"], 0);
    ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104", ssDoc["asset"]["signature"]["publicKey"].as<const char*>());
    ASSERT_EQ(ssDoc["fee"], 500000000);
    ASSERT_STRNE("", ssDoc["id"].as<const char*>());
    ASSERT_STREQ("", ssDoc["recipientId"].as<const char*>());
    ASSERT_STRNE("", ssDoc["secondSignature"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", ssDoc["senderPublicKey"]);
    ASSERT_STRNE("", ssDoc["signature"].as<const char*>());
    ASSERT_GT(ssDoc["timestamp"], 50000000);
    ASSERT_LT(ssDoc["timestamp"], 1000000000);
    ASSERT_EQ(ssDoc["type"], 1);


    //  Type 2
    auto delegateRegistration = Ark::Crypto::Transactions::Builder::buildDelegateRegistration("testName", "Secret passphrase");
    std::string dJson = delegateRegistration.toJson();

    const size_t dCapacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 450;
    DynamicJsonDocument dDoc(dCapacity);

    DeserializationError dError = deserializeJson(dDoc, dJson);
    ASSERT_FALSE(dError);

    ASSERT_EQ(dDoc["amount"], 0);
    ASSERT_STREQ("testName", dDoc["asset"]["delegate"]["username"].as<const char*>());
    ASSERT_EQ(dDoc["fee"], 2500000000);
    ASSERT_STRNE("", dDoc["id"].as<const char*>());
    ASSERT_STREQ("", dDoc["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", dDoc["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", dDoc["signature"].as<const char*>());
    ASSERT_GT(dDoc["timestamp"], 50000000);
    ASSERT_LT(dDoc["timestamp"], 1000000000);
    ASSERT_EQ(dDoc["type"], 2);


    //  Type 3
    std::vector<std::string> votes = { "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6" };
    auto vote = Ark::Crypto::Transactions::Builder::buildVote(votes, "Secret passphrase");
    std::string vJson = vote.toJson();

    const size_t vCapacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 700;
    DynamicJsonDocument vDoc(vCapacity);

    DeserializationError vError = deserializeJson(vDoc, vJson);
    ASSERT_FALSE(vError);

    ASSERT_EQ(vDoc["amount"], 0);
    ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vDoc["asset"]["votes"][0].as<const char*>());
    ASSERT_STREQ("+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vDoc["asset"]["votes"][1].as<const char*>());
    ASSERT_EQ(vDoc["fee"], 100000000);
    ASSERT_STRNE("", vDoc["id"].as<const char*>());
    ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF", vDoc["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", vDoc["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", vDoc["signature"].as<const char*>());
    ASSERT_GT(vDoc["timestamp"], 50000000);
    ASSERT_LT(vDoc["timestamp"], 1000000000);
    ASSERT_EQ(vDoc["type"], 3);
};
