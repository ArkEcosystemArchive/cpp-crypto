
#include "gtest/gtest.h"

#include "crypto/hash.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

TEST(crypto, hash_ripemd_hash_160) {
  auto ripeHash = Hash::ripemd160(tPublicKeyBytes.data());
  for (auto i = 0U; i < HASH_20_BYTE_LEN; ++i) {
    ASSERT_EQ(ripeHash.at(i), tAddressBytes.at(i));
  };
}

/**/

TEST(crypto, hash_sha_hash_256) {
  auto shaHash = Hash::sha256(tMessageBytes.data(),
                              tMessageBytes.size());
  for (auto i = 0U; i < HASH_32_BYTE_LEN; ++i) {
    ASSERT_EQ(shaHash.at(i), tMessageSha256Bytes.at(i));
  };
}
