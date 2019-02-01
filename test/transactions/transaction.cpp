#include "gtest/gtest.h"

#include "transactions/builder.h"
#include "helpers/json.h"
#include <string>

TEST(transactions, transaction_to_array) {
    //  Type 0
    auto transfer = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 1, "", "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> tArray = transfer.toArray();

    //  Amount
    ASSERT_STREQ(tArray[0].first, (const char*)"amount");
    ASSERT_STREQ(tArray[0].second.c_str(), (const char*)"1");
    //  Fee
    ASSERT_STREQ(tArray[2].first, (const char*)"fee");
    ASSERT_STREQ(tArray[2].second.c_str(), (const char*)"10000000");
    //  Id
    ASSERT_STREQ(tArray[3].first, (const char*)"id");
    ASSERT_STRNE(tArray[3].second.c_str(), (const char*)"");
    //  RecipientId
    ASSERT_STREQ(tArray[5].first, (const char*)"recipientId");
    ASSERT_STREQ(tArray[5].second.c_str(), (const char*)"D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib");
    //  SenderPublicKey
    ASSERT_STREQ(tArray[7].first, (const char*)"senderPublicKey");
    ASSERT_STREQ(tArray[7].second.c_str(), (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    //  Signature
    ASSERT_STREQ(tArray[8].first, (const char*)"signature");
    ASSERT_STRNE(tArray[8].second.c_str(), (const char*)"");
    //  Timestamp
    ASSERT_STREQ(tArray[11].first, (const char*)"timestamp");
    ASSERT_STRNE(tArray[11].second.c_str(), (const char*)"");
    //  Type
    ASSERT_STREQ(tArray[12].first, (const char*)"type");
    ASSERT_STREQ(tArray[12].second.c_str(), (const char*)"0");


    //  Type 1
    auto secondSignatureRegistration = Ark::Crypto::Transactions::Builder::buildSecondSignatureRegistration("Secret passphrase", "Second Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> ssArray = secondSignatureRegistration.toArray();

    //  Amount
    ASSERT_STREQ(ssArray[0].first, (const char*)"amount");
    ASSERT_STREQ(ssArray[0].second.c_str(), (const char*)"0");
    //  Asset
    ASSERT_STREQ(ssArray[1].first, (const char*)"publicKey");
    ASSERT_STREQ(ssArray[1].second.c_str(), (const char*)"02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104");
    //  Fee
    ASSERT_STREQ(ssArray[2].first, (const char*)"fee");
    ASSERT_STREQ(ssArray[2].second.c_str(), (const char*)"500000000");
    //  Id
    ASSERT_STREQ(ssArray[3].first, (const char*)"id");
    ASSERT_STRNE(ssArray[3].second.c_str(), (const char*)"");
    //  RecipientId
    ASSERT_STREQ(ssArray[5].first, (const char*)"recipientId");
    ASSERT_STREQ(ssArray[5].second.c_str(), (const char*)"");
    //  SecondSignature
    ASSERT_STREQ(ssArray[6].first, (const char*)"secondSignature");
    ASSERT_STRNE(ssArray[6].second.c_str(), (const char*)"");
    //  SenderPublicKey
    ASSERT_STREQ(ssArray[7].first, (const char*)"senderPublicKey");
    ASSERT_STREQ(ssArray[7].second.c_str(), (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    //  Signature
    ASSERT_STREQ(ssArray[8].first, (const char*)"signature");
    ASSERT_STRNE(ssArray[8].second.c_str(), (const char*)"");
    //  Timestamp
    ASSERT_STREQ(ssArray[11].first, (const char*)"timestamp");
    ASSERT_STRNE(ssArray[11].second.c_str(), (const char*)"");
    //  Type
    ASSERT_STREQ(ssArray[12].first, (const char*)"type");
    ASSERT_STREQ(ssArray[12].second.c_str(), (const char*)"1");


    //  Type 2
    auto delegateRegistration = Ark::Crypto::Transactions::Builder::buildDelegateRegistration("testName", "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> dArray = delegateRegistration.toArray();

    //  Amount
    ASSERT_STREQ(dArray[0].first, (const char*)"amount");
    ASSERT_STREQ(dArray[0].second.c_str(), (const char*)"0");
    //  Asset
    ASSERT_STREQ(dArray[1].first, (const char*)"username");
    ASSERT_STREQ(dArray[1].second.c_str(), (const char*)"testName");
    //  Fee
    ASSERT_STREQ(dArray[2].first, (const char*)"fee");
    ASSERT_STREQ(dArray[2].second.c_str(), (const char*)"2500000000");
    //  Id
    ASSERT_STREQ(dArray[3].first, (const char*)"id");
    ASSERT_STRNE(dArray[3].second.c_str(), (const char*)"");
    //  RecipientId
    ASSERT_STREQ(dArray[5].first, (const char*)"recipientId");
    ASSERT_STREQ(dArray[5].second.c_str(), (const char*)"");
    //  SecondSignature
    ASSERT_STREQ(dArray[6].first, (const char*)"secondSignature");
    ASSERT_STREQ(dArray[6].second.c_str(), (const char*)"");
    //  SenderPublicKey
    ASSERT_STREQ(dArray[7].first, (const char*)"senderPublicKey");
    ASSERT_STREQ(dArray[7].second.c_str(), (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    //  Signature
    ASSERT_STREQ(dArray[8].first, (const char*)"signature");
    ASSERT_STRNE(dArray[8].second.c_str(), (const char*)"");
    //  Timestamp
    ASSERT_STREQ(dArray[11].first, (const char*)"timestamp");
    ASSERT_STRNE(dArray[11].second.c_str(), (const char*)"");
    //  Type
    ASSERT_STREQ(dArray[12].first, (const char*)"type");
    ASSERT_STREQ(dArray[12].second.c_str(), (const char*)"2");


    //  Type 3
    std::vector<std::string> votes = { "-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6, +0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6" };
    auto vote = Ark::Crypto::Transactions::Builder::buildVote(votes, "Secret passphrase");
    std::vector<std::pair<const char *const, std::string>> vArray = vote.toArray();

    //  Amount
    ASSERT_STREQ(vArray[0].first, (const char*)"amount");
    ASSERT_STREQ(vArray[0].second.c_str(), (const char*)"0");
    //  Asset
    ASSERT_STREQ(vArray[1].first, (const char*)"votes");
    ASSERT_STREQ(vArray[1].second.c_str(), (const char*)"-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6, +0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6");
    //  Fee
    ASSERT_STREQ(vArray[2].first, (const char*)"fee");
    ASSERT_STREQ(vArray[2].second.c_str(), (const char*)"100000000");
    //  Id
    ASSERT_STREQ(vArray[3].first, (const char*)"id");
    ASSERT_STRNE(vArray[3].second.c_str(), (const char*)"");
    //  RecipientId
    ASSERT_STREQ(vArray[5].first, (const char*)"recipientId");
    ASSERT_STREQ(vArray[5].second.c_str(), (const char*)"DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF");
    //  SecondSignature
    ASSERT_STREQ(vArray[6].first, (const char*)"secondSignature");
    ASSERT_STREQ(vArray[6].second.c_str(), (const char*)"");
    //  SenderPublicKey
    ASSERT_STREQ(vArray[7].first, (const char*)"senderPublicKey");
    ASSERT_STREQ(vArray[7].second.c_str(), (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    //  Signature
    ASSERT_STREQ(vArray[8].first, (const char*)"signature");
    ASSERT_STRNE(vArray[8].second.c_str(), (const char*)"");
    //  Timestamp
    ASSERT_STREQ(vArray[11].first, (const char*)"timestamp");
    ASSERT_STRNE(vArray[11].second.c_str(),(const char*) "");
    //  Type
    ASSERT_STREQ(vArray[12].first, (const char*)"type");
    ASSERT_STREQ(vArray[12].second.c_str(), (const char*)"3");
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
    ASSERT_STRNE(tRoot["id"], (const char*)"");
    ASSERT_STREQ(tRoot["recipientId"], (const char*)"D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib");
    ASSERT_STREQ(tRoot["senderPublicKey"], (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    ASSERT_STRNE(tRoot["signature"], (const char*)"");
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
    ASSERT_STREQ(ssAsset, (const char*)"02e1684d8990c0a5625aec85977fcf22204884bc08d45dbc71b2859e5fa4f45104");
    ASSERT_EQ(ssRoot["fee"], 500000000);
    ASSERT_STRNE(ssRoot["id"], (const char*)"");
    ASSERT_STREQ(ssRoot["recipientId"], (const char*)"");
    ASSERT_STRNE(ssRoot["secondSignature"], (const char*)"");
    ASSERT_STREQ(ssRoot["senderPublicKey"], (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    ASSERT_STRNE(ssRoot["signature"], (const char*)"");
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
    ASSERT_STREQ(dAsset, (const char*)"testName");
    ASSERT_EQ(dRoot["fee"], 2500000000);
    ASSERT_STRNE(dRoot["id"], (const char*)"");
    ASSERT_STREQ(dRoot["recipientId"], (const char*)"");
    ASSERT_STREQ(dRoot["senderPublicKey"], (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    ASSERT_STRNE(dRoot["signature"], (const char*)"");
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
    ASSERT_STREQ(vAsset1, (const char*)"-0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6");
    ASSERT_STREQ(vAsset2, (const char*)"+0250b742256f9321bd7d46f3ed9769b215a7c2fb02be951acf43bc51eb57ceadf6");    ASSERT_EQ(vRoot["fee"], 100000000);
    ASSERT_STRNE(vRoot["id"], (const char*)"");
    ASSERT_STREQ(vRoot["recipientId"], (const char*)"DPgZq5MK6rm5yVks9b7TrA22F8FwRvkCtF");
    ASSERT_STREQ(vRoot["senderPublicKey"], (const char*)"02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699");
    ASSERT_STRNE(vRoot["signature"], (const char*)"");
    ASSERT_GT(vRoot["timestamp"], 50000000);
    ASSERT_LT(vRoot["timestamp"], 1000000000);
    ASSERT_EQ(vRoot["type"], 3);
};
