#include "gtest/gtest.h"

#include "identities/keys.hpp"
#include "interfaces/identities.hpp"

#include "fixtures/identity.hpp"
using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace Ark::Crypto::fixtures::identity;

TEST(identities, keys_publickey_from_privatekey) {
  auto publicKey = Keys::PublicKey::fromPrivateKey(tPrivateKeyBytes.data());
  for (auto i = 0U; i < PUBLICKEY_COMPRESSED_BYTE_LEN; i++) {
    ASSERT_EQ(publicKey.at(i), tPublicKeyBytes.at(i));
  };
}
