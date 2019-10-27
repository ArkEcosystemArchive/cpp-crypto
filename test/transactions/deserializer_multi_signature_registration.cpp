
#include "gtest/gtest.h"

#include <arkCrypto.h>

TEST(transactions, deserialize_multi_signature_registration) { // NOLINT
  // multi_signature_registration/passphrase.json
  Ark::Crypto::Transactions::Deserializer deserializer(
      "ff011704724c9a00036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f47b5d7d76000943577000000000002031803543c"
      "6cc3545be6bac09c82721973a052c690658283472e88f24d14739f75acc80276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec7a165a80"
      "731b44ae89f1fc02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8b7422063091f4b3130440220324d89c5792e4a54ae70b4f1"
      "e27e2f87a8b7169cc6f2f7b2c83dba894960f987022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c3558045e787bc01a53044"
      "02201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d315d66321c6902201aa94c4ed3e5e479a12220aa886b259e488eb89b"
      "697c711f91e8c03b9620e0b1ff304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df58673669406d424c0220798f5710"
      "897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7dade60e4304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5d"
      "df07802424dab78e02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd41fb304402207e660489bced5ce80c33"
      "d45c86781b63898775ab4a231bb48780f97b40073a63022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913d");
  auto actual = deserializer.deserialize();

  ASSERT_EQ(0xFF, actual.header);
  ASSERT_EQ(1, actual.version);
  ASSERT_EQ(23, actual.network);
  ASSERT_EQ(TransactionTypes::MultiSignatureRegistration, actual.type);
  ASSERT_EQ(10112114UL, actual.timestamp);
  ASSERT_STREQ("036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f47b5d7d760", actual.senderPublicKey.c_str());
  ASSERT_TRUE(2000000000ULL == actual.fee);
  ASSERT_TRUE(0ULL == actual.amount);
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
  };

  ASSERT_STREQ("cbd6862966bb1b03ba742397b7e5a88d6eefb393a362ead0d605723b840db2af", actual.id.c_str());

  ASSERT_STREQ(
      "30440220324d89c5792e4a54ae70b4f1e27e2f87a8b7169cc6f2f7b2c83dba894960f987022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c3558045e787bc01a5",
      actual.signature.c_str());
  ASSERT_STREQ(
      "304402201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d315d66321c6902201aa94c4ed3e5e479a12220aa886b259e488eb89b697c711f91e8c03b9620e0b1",
      actual.secondSignature.c_str());

  std::vector<std::string> signatures = {
      "304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df58673669406d424c0220798f5710897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7dade60e4",
      "304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5ddf07802424dab78e02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd41fb",
      "304402207e660489bced5ce80c33d45c86781b63898775ab4a231bb48780f97b40073a63022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913d"};

  ASSERT_EQ(3, actual.signatures.size());
  for (uint8_t i = 0; i < signatures.size(); i++) {
    ASSERT_STREQ(signatures[i].c_str(), actual.signatures[i].c_str());
  }

  ASSERT_TRUE(actual.verify());

  // special case as the type 4 transaction itself has no recipient
  const auto publicKey = Ark::Crypto::identities::PublicKey::fromHex(actual.senderPublicKey.c_str());
  const auto address = Ark::Crypto::identities::Address::fromPublicKey(publicKey.toBytes().data(), actual.network);
  ASSERT_STREQ(address.toString().c_str(), actual.recipient.c_str());
}
