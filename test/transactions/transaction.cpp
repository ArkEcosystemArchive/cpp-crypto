#include "gtest/gtest.h"

#include "transactions/builder.h"
#include "helpers/json.h"
#include <string>

TEST(transactions, transaction_to_array) {
    //  Type 0
    auto transfer = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 1, "", "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> tArray = transfer.toArray();

    //  Amount
    ASSERT_STREQ("amount", tArray[0].first);
    ASSERT_STREQ("1", tArray[0].second.c_str());
    //  Fee
    ASSERT_STREQ("fee", tArray[2].first);
    ASSERT_STREQ("10000000", tArray[2].second.c_str());
    //  Id
    ASSERT_STREQ("id", tArray[3].first);
    ASSERT_STRNE("", tArray[3].second.c_str());
    //  RecipientId
    ASSERT_STREQ("recipientId", tArray[5].first);
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tArray[5].second.c_str());
    //  SenderPublicKey
    ASSERT_STREQ("senderPublicKey", tArray[7].first);
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", tArray[7].second.c_str());
    //  Signature
    ASSERT_STREQ("signature", tArray[8].first);
    ASSERT_STRNE("", tArray[8].second.c_str());
    //  Timestamp
    ASSERT_STREQ("timestamp", tArray[11].first);
    ASSERT_STRNE("", tArray[11].second.c_str());
    //  Type
    ASSERT_STREQ("type", tArray[12].first);
    ASSERT_STREQ("0", tArray[12].second.c_str());


    //  Type 1
    auto secondSignatureRegistration = Ark::Crypto::Transactions::Builder::buildSecondSignatureRegistration("Secret passphrase", "Second Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> ssArray = secondSignatureRegistration.toArray();

    //  Amount
    ASSERT_STREQ("amount", ssArray[0].first);
    ASSERT_STREQ("0", ssArray[0].second.c_str());
    //  Asset
    ASSERT_STREQ("publicKey", ssArray[1].first);
    ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104", ssArray[1].second.c_str());
    //  Fee
    ASSERT_STREQ("fee", ssArray[2].first);
    ASSERT_STREQ("500000000", ssArray[2].second.c_str());
    //  Id
    ASSERT_STREQ("id", ssArray[3].first);
    ASSERT_STRNE("", ssArray[3].second.c_str());
    //  RecipientId
    ASSERT_STREQ("recipientId", ssArray[5].first);
    ASSERT_STREQ("", ssArray[5].second.c_str());
    //  SecondSignature
    ASSERT_STREQ("secondSignature", ssArray[6].first);
    ASSERT_STRNE("", ssArray[6].second.c_str());
    //  SenderPublicKey
    ASSERT_STREQ("senderPublicKey", ssArray[7].first);
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", ssArray[7].second.c_str());
    //  Signature
    ASSERT_STREQ("signature", ssArray[8].first);
    ASSERT_STRNE("", ssArray[8].second.c_str());
    //  Timestamp
    ASSERT_STREQ("timestamp", ssArray[11].first);
    ASSERT_STRNE("", ssArray[11].second.c_str());
    //  Type
    ASSERT_STREQ("type", ssArray[12].first);
    ASSERT_STREQ("1", ssArray[12].second.c_str());


    //  Type 2
    auto delegateRegistration = Ark::Crypto::Transactions::Builder::buildDelegateRegistration("testName", "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> dArray = delegateRegistration.toArray();

    //  Amount
    ASSERT_STREQ("amount", dArray[0].first);
    ASSERT_STREQ("0", dArray[0].second.c_str());
    //  Asset
    ASSERT_STREQ("username", dArray[1].first);
    ASSERT_STREQ("testName", dArray[1].second.c_str());
    //  Fee
    ASSERT_STREQ("fee", dArray[2].first);
    ASSERT_STREQ("2500000000", dArray[2].second.c_str());
    //  Id
    ASSERT_STREQ("id", dArray[3].first);
    ASSERT_STRNE("", dArray[3].second.c_str());
    //  RecipientId
    ASSERT_STREQ("recipientId", dArray[5].first);
    ASSERT_STREQ("", dArray[5].second.c_str());
    //  SecondSignature
    ASSERT_STREQ("secondSignature", dArray[6].first);
    ASSERT_STREQ("", dArray[6].second.c_str());
    //  SenderPublicKey
    ASSERT_STREQ("senderPublicKey", dArray[7].first);
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", dArray[7].second.c_str());
    //  Signature
    ASSERT_STREQ("signature", dArray[8].first);
    ASSERT_STRNE("", dArray[8].second.c_str());
    //  Timestamp
    ASSERT_STREQ("timestamp", dArray[11].first);
    ASSERT_STRNE("", dArray[11].second.c_str());
    //  Type
    ASSERT_STREQ("type", dArray[12].first);
    ASSERT_STREQ("2", dArray[12].second.c_str());


    //  Type 3
    std::vector<std::string> votes = { "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", "+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6" };
    auto vote = Ark::Crypto::Transactions::Builder::buildVote(votes, "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> vArray = vote.toArray();

    //  Amount
    ASSERT_STREQ("amount", vArray[0].first);
    ASSERT_STREQ("0", vArray[0].second.c_str());
    //  Asset
    ASSERT_STREQ("votes", vArray[1].first);
    ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vArray[1].second.c_str());
    //  Fee
    ASSERT_STREQ("fee", vArray[2].first);
    ASSERT_STREQ("100000000", vArray[2].second.c_str());
    //  Id
    ASSERT_STREQ("id", vArray[3].first);
    ASSERT_STRNE("", vArray[3].second.c_str());
    //  RecipientId
    ASSERT_STREQ("recipientId", vArray[5].first);
    ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF", vArray[5].second.c_str());
    //  SecondSignature
    ASSERT_STREQ("secondSignature", vArray[6].first);
    ASSERT_STREQ("", vArray[6].second.c_str());
    //  SenderPublicKey
    ASSERT_STREQ("senderPublicKey", vArray[7].first);
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", vArray[7].second.c_str());
    //  Signature
    ASSERT_STREQ("signature", vArray[8].first);
    ASSERT_STRNE("", vArray[8].second.c_str());
    //  Timestamp
    ASSERT_STREQ("timestamp", vArray[11].first);
    ASSERT_STRNE("", vArray[11].second.c_str());
    //  Type
    ASSERT_STREQ("type", vArray[12].first);
    ASSERT_STREQ("3", vArray[12].second.c_str());
}

TEST(transactions, transaction_to_json) {

    //  Type 0
    auto transfer = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 1, "", "Secret passphrase");
    std::string tJson = transfer.toJson();

    const size_t tCapacity = JSON_OBJECT_SIZE(8) + 450;
    DynamicJsonBuffer tJsonBuffer(tCapacity);

    JsonObject& tRoot = tJsonBuffer.parseObject(tJson);

    ASSERT_EQ(tRoot["amount"], 1);
    ASSERT_EQ(tRoot["fee"], 10000000);
    ASSERT_STRNE("", tRoot["id"].as<const char*>());
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tRoot["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", tRoot["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", tRoot["signature"].as<const char*>());
    ASSERT_GT(tRoot["timestamp"], 50000000);
    ASSERT_LT(tRoot["timestamp"], 1000000000);
    ASSERT_EQ(tRoot["type"], 0);


    //  Type 1
    auto secondSignatureRegistration = Ark::Crypto::Transactions::Builder::buildSecondSignatureRegistration("Secret passphrase", "Second Secret passphrase");
    std::string ssJson = secondSignatureRegistration.toJson();

    const size_t ssCapacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(10) + 690;
    DynamicJsonBuffer ssJsonBuffer(ssCapacity);

    JsonObject& ssRoot = ssJsonBuffer.parseObject(ssJson);

    ASSERT_EQ(ssRoot["amount"], 0);
    const char* ssAsset = ssRoot["asset"]["signature"]["publicKey"];
    ASSERT_STREQ("02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104", ssAsset);
    ASSERT_EQ(ssRoot["fee"], 500000000);
    ASSERT_STRNE("", ssRoot["id"].as<const char*>());
    ASSERT_STREQ("", ssRoot["recipientId"].as<const char*>());
    ASSERT_STRNE("", ssRoot["secondSignature"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", ssRoot["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", ssRoot["signature"].as<const char*>());
    ASSERT_GT(ssRoot["timestamp"], 50000000);
    ASSERT_LT(ssRoot["timestamp"], 1000000000);
    ASSERT_EQ(ssRoot["type"], 1);


    //  Type 2
    auto delegateRegistration = Ark::Crypto::Transactions::Builder::buildDelegateRegistration("testName", "Secret passphrase");
    std::string dJson = delegateRegistration.toJson();

    const size_t dCapacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 450;
    DynamicJsonBuffer dJsonBuffer(dCapacity);

    JsonObject& dRoot = dJsonBuffer.parseObject(dJson);

    ASSERT_EQ(dRoot["amount"], 0);
    const char* dAsset = dRoot["asset"]["delegate"]["username"];
    ASSERT_STREQ("testName", dAsset);
    ASSERT_EQ(dRoot["fee"], 2500000000);
    ASSERT_STRNE("", dRoot["id"].as<const char*>());
    ASSERT_STREQ("", dRoot["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", dRoot["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", dRoot["signature"].as<const char*>());
    ASSERT_GT(dRoot["timestamp"], 50000000);
    ASSERT_LT(dRoot["timestamp"], 1000000000);
    ASSERT_EQ(dRoot["type"], 2);


    //  Type 3
    std::vector<std::string> votes = { "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6,+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6" };
    auto vote = Ark::Crypto::Transactions::Builder::buildVote(votes, "Secret passphrase");
    std::string vJson = vote.toJson();

    const size_t vCapacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + 540;
    DynamicJsonBuffer vJsonBuffer(vCapacity);

    JsonObject& vRoot = vJsonBuffer.parseObject(vJson);

    ASSERT_EQ(vRoot["amount"], 0);
    const char* vAsset1 = vRoot["asset"]["votes"][0];
    const char* vAsset2 = vRoot["asset"]["votes"][1];
    ASSERT_STREQ("-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vAsset1);
    ASSERT_STREQ("+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6", vAsset2);
    ASSERT_EQ(vRoot["fee"], 100000000);
    ASSERT_STRNE("", vRoot["id"].as<const char*>());
    ASSERT_STREQ("DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF", vRoot["recipientId"].as<const char*>());
    ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699", vRoot["senderPublicKey"].as<const char*>());
    ASSERT_STRNE("", vRoot["signature"].as<const char*>());
    ASSERT_GT(vRoot["timestamp"], 50000000);
    ASSERT_LT(vRoot["timestamp"], 1000000000);
    ASSERT_EQ(vRoot["type"], 3);
};
