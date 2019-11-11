
#include "gtest/gtest.h"

#include <map>
#include <string>

#include "transactions/transaction.h"
#include "utils/json.h"
using namespace Ark::Crypto;
using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_default) {
  Transaction transaction;
  ASSERT_FALSE(transaction.verify());
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
