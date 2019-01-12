#include "gtest/gtest.h"

#include "enums/types.h"
#include "identities/address.h"
#include "identities/publickey.h"
#include "transactions/deserializer.h"

TEST(transactions, deserialize_transfer)
{
    // transfer/passphrase-with-vendor-field.json
    Ark::Crypto::Transactions::Deserializer deserializer("ff011e0007627802034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19280969800000000000b48656c6c6f20576f726c6400c2eb0b00000000000000001e0995750207ecaf0ccf251c1265b92ad84f553662304402205616d6e361439d67a5c2067bbfc8fce61b93061a4fa113315a1c5cf965ff6f3202200a1d99caaa98aeebcec04edd5365352500addb830c79f49b9de484ec616bb1e1");
    auto actual = deserializer.deserialize();

    ASSERT_EQ(0xFF, actual.header);
    ASSERT_EQ(1, actual.version);
    ASSERT_EQ(30, actual.network);
    ASSERT_EQ(Ark::Crypto::Enums::Types::TRANSFER, actual.type);
    ASSERT_EQ(41443847, actual.timestamp);
    ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", actual.senderPublicKey.c_str());
    ASSERT_TRUE(10000000 == actual.fee);
    ASSERT_STREQ("48656c6c6f20576f726c64", actual.vendorFieldHex.c_str());
    ASSERT_STREQ("Hello World", actual.vendorField.c_str());
    ASSERT_TRUE(200000000 == actual.amount);
    ASSERT_STREQ("ecf558fbddd62ae42edcfcba02f402d987a94b72a7636ef1121e8625487e2a1e", actual.id.c_str());
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", actual.recipientId.c_str());
    ASSERT_STREQ("304402205616d6e361439d67a5c2067bbfc8fce61b93061a4fa113315a1c5cf965ff6f3202200a1d99caaa98aeebcec04edd5365352500addb830c79f49b9de484ec616bb1e1", actual.signature.c_str());
    ASSERT_TRUE(actual.verify());
}

TEST(transactions, deserialize_second_signature_registration)
{
    // second_signature_registration/second-passphrase.json
    Ark::Crypto::Transactions::Deserializer deserializer("ff011e013bc27502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000003699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c");
    auto actual = deserializer.deserialize();

    ASSERT_EQ(0xFF, actual.header);
    ASSERT_EQ(1, actual.version);
    ASSERT_EQ(30, actual.network);
    ASSERT_EQ(Ark::Crypto::Enums::Types::SECOND_SIGNATURE_REGISTRATION, actual.type);
    ASSERT_EQ(41271867, actual.timestamp);
    ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", actual.senderPublicKey.c_str());
    ASSERT_TRUE(500000000 == actual.fee);
    ASSERT_TRUE(0 == actual.amount);
    ASSERT_EQ(0, actual.expiration);
    ASSERT_STREQ("6d1615924d172d352c8f44d4ded84cbbece3c03ebb3e4fc3f3334784ae332590", actual.id.c_str());
    ASSERT_STREQ("03699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609", actual.asset.signature.publicKey.c_str());
    ASSERT_STREQ("304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c", actual.signature.c_str());
    ASSERT_TRUE(actual.verify());

    // special case as the type 1 transaction itself has no recipientId
    const auto publicKey = Ark::Crypto::Identities::PublicKey::fromHex(actual.senderPublicKey.c_str());
    const auto address = Ark::Crypto::Identities::Address::fromPublicKey(publicKey, actual.network);
    ASSERT_STREQ(address.toString().c_str(), actual.recipientId.c_str());
}

#if 0
TEST(transactions, deserialize_delegate_registration)
{
    // delegate_registration/second-passphrase.json
    Ark::Crypto::Transactions::Deserializer deserializer("ff011e02b0b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200f90295000000000009626f6c646e696e6a613045022100f21b742fa052cd18de43328e1d068539ba7cbe9d33a9dcbd862a82871383955d0220053b06d22ed3e3ad6168c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94304402207da580da4feec955edcb8e8eb36947867b439de3d28d38e58c844fd8c45b564302200e6741b6ad11c2588a57b3afd180df1e9b345d48a9c2ae98be57dced869cf38c");
    auto actual = deserializer.deserialize();

    ASSERT_EQ(0xFF, actual.header);
    ASSERT_EQ(1, actual.version);
    ASSERT_EQ(30, actual.network);
    ASSERT_EQ(Ark::Crypto::Enums::Types::DELEGATE_REGISTRATION, actual.type);
    ASSERT_EQ(41269424, actual.timestamp);
    ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", actual.senderPublicKey.c_str());
    ASSERT_TRUE(2500000000 == actual.fee);
    ASSERT_TRUE(0 == actual.amount);
    ASSERT_EQ(0, actual.expiration);
    ASSERT_STREQ("bf7e018ff9c0066f7a9f51e95d3f78c08cad5dd8581325d630d64350181a91bb", actual.id.c_str());
    ASSERT_STREQ("boldninja", actual.asset.delegate.username.c_str());
    ASSERT_STREQ("3045022100f21b742fa052cd18de43328e1d068539ba7cbe9d33a9dcbd862a82871383955d0220053b06d22ed3e3ad6168c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94", actual.signature.c_str());
    ASSERT_STREQ("304402207da580da4feec955edcb8e8eb36947867b439de3d28d38e58c844fd8c45b564302200e6741b6ad11c2588a57b3afd180df1e9b345d48a9c2ae98be57dced869cf38c", actual.secondSignature.c_str());
    ASSERT_TRUE(actual.verify());
}
#endif

TEST(transactions, deserialize_vote)
{
    // vote/second-passphrase.json
    Ark::Crypto::Transactions::Deserializer deserializer("ff011e0376b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed19200e1f50500000000000101022cca9529ec97a772156c152a00aad155ee6708243e65c9d211a589cb5d43234d304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663d875af7ec1154448e98466e86302201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828ed2d7c53a5e8db08cb6d068304402201329882762a42d1af9079c822a9e3feefa47b7476b0afe61440637408958a64402206da179b08e31d9c784fbb23abe2c9b50353ed7881dc29787a5e8ecbee2dfda66");
    auto actual = deserializer.deserialize();

    ASSERT_EQ(0xFF, actual.header);
    ASSERT_EQ(1, actual.version);
    ASSERT_EQ(30, actual.network);
    ASSERT_EQ(Ark::Crypto::Enums::Types::VOTE, actual.type);
    ASSERT_EQ(41269366, actual.timestamp);
    ASSERT_STREQ("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192", actual.senderPublicKey.c_str());
    ASSERT_TRUE(100000000 == actual.fee);
    ASSERT_TRUE(0 == actual.amount);
    ASSERT_EQ(0, actual.expiration);
    ASSERT_STREQ("16f28a180cd6f3ea46c10f358a457989e956e9d355258230d0c7b07acec10b73", actual.id.c_str());
    ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", actual.recipientId.c_str());

    std::vector<std::string> votes = {std::string("+022cca9529ec97a772156c152a00aad155ee6708243e65c9d211a589cb5d43234d")};
    ASSERT_EQ(1, actual.asset.votes.size());
    ASSERT_STREQ(votes[0].c_str(), actual.asset.votes[0].c_str());

    ASSERT_STREQ("304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663d875af7ec1154448e98466e86302201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828ed2d7c53a5e8db08cb6d068", actual.signature.c_str());
    ASSERT_STREQ("304402201329882762a42d1af9079c822a9e3feefa47b7476b0afe61440637408958a64402206da179b08e31d9c784fbb23abe2c9b50353ed7881dc29787a5e8ecbee2dfda66", actual.secondSignature.c_str());
    ASSERT_TRUE(actual.verify());
}

TEST(transactions, deserialize_multi_signature_registration)
{
    // multi_signature_registration/passphrase.json
    Ark::Crypto::Transactions::Deserializer deserializer("ff011704724c9a00036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f47b5d7d76000943577000000000002031803543c6cc3545be6bac09c82721973a052c690658283472e88f24d14739f75acc80276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec7a165a80731b44ae89f1fc02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8b7422063091f4b3130440220324d89c5792e4a54ae70b4f1e27e2f87a8b7169cc6f2f7b2c83dba894960f987022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c3558045e787bc01a5304402201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d315d66321c6902201aa94c4ed3e5e479a12220aa886b259e488eb89b697c711f91e8c03b9620e0b1ff304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df58673669406d424c0220798f5710897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7dade60e4304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5ddf07802424dab78e02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd41fb304402207e660489bced5ce80c33d45c86781b63898775ab4a231bb48780f97b40073a63022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913d");
    auto actual = deserializer.deserialize();

    ASSERT_EQ(0xFF, actual.header);
    ASSERT_EQ(1, actual.version);
    ASSERT_EQ(23, actual.network);
    ASSERT_EQ(Ark::Crypto::Enums::Types::MULTI_SIGNATURE_REGISTRATION, actual.type);
    ASSERT_EQ(10112114, actual.timestamp);
    ASSERT_STREQ("036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f47b5d7d760", actual.senderPublicKey.c_str());
    ASSERT_TRUE(2000000000 == actual.fee);
    ASSERT_TRUE(0 == actual.amount);
    ASSERT_EQ(0, actual.expiration);

    std::vector<std::string> keysgroup = {
        "+03543c6cc3545be6bac09c82721973a052c690658283472e88f24d14739f75acc8",
        "+0276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec7a165a80731b44ae89f1fc",
        "+02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8b7422063091f4b31"
    };

    ASSERT_EQ(3, actual.asset.multiSignature.keysgroup.size());
    ASSERT_EQ(2, actual.asset.multiSignature.min);
    ASSERT_EQ(24, actual.asset.multiSignature.lifetime);

    for (uint8_t i = 0; i < keysgroup.size(); i++) {
        ASSERT_STREQ(keysgroup[i].c_str(), actual.asset.multiSignature.keysgroup[i].c_str());
    }

    ASSERT_STREQ("cbd6862966bb1b03ba742397b7e5a88d6eefb393a362ead0d605723b840db2af", actual.id.c_str());

    ASSERT_STREQ("30440220324d89c5792e4a54ae70b4f1e27e2f87a8b7169cc6f2f7b2c83dba894960f987022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c3558045e787bc01a5", actual.signature.c_str());
    ASSERT_STREQ("304402201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d315d66321c6902201aa94c4ed3e5e479a12220aa886b259e488eb89b697c711f91e8c03b9620e0b1", actual.secondSignature.c_str());

    std::vector<std::string> signatures = {
        "304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df58673669406d424c0220798f5710897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7dade60e4",
        "304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5ddf07802424dab78e02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd41fb",
        "304402207e660489bced5ce80c33d45c86781b63898775ab4a231bb48780f97b40073a63022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913d"
    };

    ASSERT_EQ(3, actual.signatures.size());
    for (uint8_t i = 0; i < signatures.size(); i++) {
        ASSERT_STREQ(signatures[i].c_str(), actual.signatures[i].c_str());
    }

    ASSERT_TRUE(actual.verify());

    // special case as the type 4 transaction itself has no recipientId
    const auto publicKey = Ark::Crypto::Identities::PublicKey::fromHex(actual.senderPublicKey.c_str());
    const auto address = Ark::Crypto::Identities::Address::fromPublicKey(publicKey, actual.network);
    ASSERT_STREQ(address.toString().c_str(), actual.recipientId.c_str());
}
