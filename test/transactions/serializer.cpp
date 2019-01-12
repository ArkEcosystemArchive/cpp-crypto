#include "gtest/gtest.h"

#include "transactions/serializer.h"

TEST(transactions, serialize_transfer) {
  // transfer/passphrase-with-vendor-field.json
  Ark::Crypto::Transactions::Transaction transaction;

  transaction.type = 0;
  transaction.fee = 10000000;
  transaction.amount = 200000000;
  transaction.timestamp = 41443847;
  transaction.recipientId = "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib";
  transaction.senderPublicKey =
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
  transaction.vendorField = "Hello World";
  transaction.signature =
      "304402205616d6e361439d67a5c2067bbfc8fce61b93061a4fa113315a1c5cf965ff6f32"
      "02200a1d99caaa98aeebcec04edd5365352500addb830c79f49b9de484ec616bb1e1";

  Ark::Crypto::Transactions::Serializer serializer(transaction);
  std::string actual = serializer.serialize();

  ASSERT_STREQ(
      "ff011e0007627802034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58"
      "e7f0aed19280969800000000000b48656c6c6f20576f726c6400c2eb0b00000000000000"
      "001e0995750207ecaf0ccf251c1265b92ad84f553662304402205616d6e361439d67a5c2"
      "067bbfc8fce61b93061a4fa113315a1c5cf965ff6f3202200a1d99caaa98aeebcec04edd"
      "5365352500addb830c79f49b9de484ec616bb1e1",
      actual.c_str());
}

TEST(transactions, serialize_second_signature_registration) {
  // second_signature_registration/second-passphrase.json
  Ark::Crypto::Transactions::Transaction transaction;

  transaction.type = 1;
  transaction.fee = 500000000;
  transaction.timestamp = 41271867;
  transaction.senderPublicKey =
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
  transaction.signature =
      "304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf"
      "02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c";
  transaction.asset.signature.publicKey =
      "03699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609";

  Ark::Crypto::Transactions::Serializer serializer(transaction);
  std::string actual = serializer.serialize();

  ASSERT_STREQ(
      "ff011e013bc27502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58"
      "e7f0aed1920065cd1d000000000003699e966b2525f9088a6941d8d94f7869964a000efe"
      "65783d78ac82e1199fe609304402202aab49477dd3531e4473196d08fbd7c00ebb79223d"
      "5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9"
      "e20d6c8773f869831c",
      actual.c_str());
}

TEST(transactions, serialize_delegate_registration) {
  // delegate_registration/second-passphrase.json
  Ark::Crypto::Transactions::Transaction transaction;

  transaction.type = 2;
  transaction.fee = 2500000000;
  transaction.timestamp = 41269424;
  transaction.senderPublicKey =
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
  transaction.signature =
      "3045022100f21b742fa052cd18de43328e1d068539ba7cbe9d33a9dcbd862a8287138395"
      "5d0220053b06d22ed3e3ad6168c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94";
  transaction.secondSignature =
      "304402207da580da4feec955edcb8e8eb36947867b439de3d28d38e58c844fd8c45b5643"
      "02200e6741b6ad11c2588a57b3afd180df1e9b345d48a9c2ae98be57dced869cf38c";
  transaction.asset.delegate.username = "boldninja";

  Ark::Crypto::Transactions::Serializer serializer(transaction);
  std::string actual = serializer.serialize();

  ASSERT_STREQ(
      "ff011e02b0b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58"
      "e7f0aed19200f90295000000000009626f6c646e696e6a613045022100f21b742fa052cd"
      "18de43328e1d068539ba7cbe9d33a9dcbd862a82871383955d0220053b06d22ed3e3ad61"
      "68c6b27aa0ec68e7e40958c7709aec0e1555087ea9ad94304402207da580da4feec955ed"
      "cb8e8eb36947867b439de3d28d38e58c844fd8c45b564302200e6741b6ad11c2588a57b3"
      "afd180df1e9b345d48a9c2ae98be57dced869cf38c",
      actual.c_str());
}

TEST(transactions, serialize_vote) {
  // vote/second-passphrase.json
  Ark::Crypto::Transactions::Transaction transaction;

  transaction.type = 3;
  transaction.fee = 100000000;
  transaction.timestamp = 41269366;
  transaction.recipientId = "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib";
  transaction.senderPublicKey =
      "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";
  transaction.signature =
      "304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663d875af7ec1154448e98466e863"
      "02201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828ed2d7c53a5e8db08cb6d068";
  transaction.secondSignature =
      "304402201329882762a42d1af9079c822a9e3feefa47b7476b0afe61440637408958a644"
      "02206da179b08e31d9c784fbb23abe2c9b50353ed7881dc29787a5e8ecbee2dfda66";
  transaction.asset.votes = {
      "+022cca9529ec97a772156c152a00aad155ee6708243e65c9d211a589cb5d43234d"};

  Ark::Crypto::Transactions::Serializer serializer(transaction);
  std::string actual = serializer.serialize();

  ASSERT_STREQ(
      "ff011e0376b87502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58"
      "e7f0aed19200e1f50500000000000101022cca9529ec97a772156c152a00aad155ee6708"
      "243e65c9d211a589cb5d43234d304402204b8bb403e2db7f9599d46d0f5d39f8bb1d0663"
      "d875af7ec1154448e98466e86302201e92fb57e13fb729b07e1027fa3d6e3f28e0d5828e"
      "d2d7c53a5e8db08cb6d068304402201329882762a42d1af9079c822a9e3feefa47b7476b"
      "0afe61440637408958a64402206da179b08e31d9c784fbb23abe2c9b50353ed7881dc297"
      "87a5e8ecbee2dfda66",
      actual.c_str());
}

TEST(transactions, serialize_multi_signature_registration) {
  // multi_signature_registration/passphrase.json
  Ark::Crypto::Transactions::Transaction transaction;

  transaction.type = 4;
  transaction.version = 1;
  transaction.network = 23;
  transaction.fee = 2000000000;
  transaction.timestamp = 10112114;
  transaction.senderPublicKey =
      "036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f47b5d7d760";
  transaction.signature =
      "30440220324d89c5792e4a54ae70b4f1e27e2f87a8b7169cc6f2f7b2c83dba894960f987"
      "022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c3558045e787bc01a5";
  transaction.secondSignature =
      "304402201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d315d66321c69"
      "02201aa94c4ed3e5e479a12220aa886b259e488eb89b697c711f91e8c03b9620e0b1";
  transaction.signatures = {
      "304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df58673669406d42"
      "4c0220798f5710897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7dade60e4",
      "304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5ddf07802424dab78e"
      "02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd41fb",
      "304402207e660489bced5ce80c33d45c86781b63898775ab4a231bb48780f97b40073a63"
      "022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913d"};

  transaction.asset.multiSignature.keysgroup = {
      "+03543c6cc3545be6bac09c82721973a052c690658283472e88f24d14739f75acc8",
      "+0276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec7a165a80731b44ae89f1fc",
      "+02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8b7422063091f4b31"};
  transaction.asset.multiSignature.lifetime = 24;
  transaction.asset.multiSignature.min = 2;

  Ark::Crypto::Transactions::Serializer serializer(transaction);
  std::string actual = serializer.serialize();

  ASSERT_STREQ(
      "ff011704724c9a00036928c98ee53a1f52ed01dd87db10ffe1980eb47cd7c0a7d688321f"
      "47b5d7d76000943577000000000002031803543c6cc3545be6bac09c82721973a052c690"
      "658283472e88f24d14739f75acc80276dc5b8706a85ca9fdc46e571ac84e52fbb48e13ec"
      "7a165a80731b44ae89f1fc02e8d5d17eb17bbc8d7bf1001d29a2d25d1249b7bb7a5b7ad8"
      "b7422063091f4b3130440220324d89c5792e4a54ae70b4f1e27e2f87a8b7169cc6f2f7b2"
      "c83dba894960f987022053b8d0ae23ff9d1769364db7b6fd03216d93753c82a711c35580"
      "45e787bc01a5304402201fcd54a9ac9c0269b8cec213566ddf43207798e2cf9ca1ce3c5d"
      "315d66321c6902201aa94c4ed3e5e479a12220aa886b259e488eb89b697c711f91e8c03b"
      "9620e0b1ff304502210097f17c8eecf36f86a967cc52a83fa661e4ffc70cc4ea08df5867"
      "3669406d424c0220798f5710897b75dda42f6548f841afbe4ed1fa262097112cf5a1b3f7"
      "dade60e4304402201a4a4c718bfdc699bbb891b2e89be018027d2dcd10640b5ddf078024"
      "24dab78e02204ec7c7d505d2158c3b51fdd3843d16aecd2eaaa4c6c7a555ef123c5e59fd"
      "41fb304402207e660489bced5ce80c33d45c86781b63898775ab4a231bb48780f97b4007"
      "3a63022026f0cefd0d83022d822522ab4366a82e3b89085c328817919939f2efeabd913"
      "d",
      actual.c_str());
}
