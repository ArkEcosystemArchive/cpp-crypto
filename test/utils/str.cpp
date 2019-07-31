
#include "gtest/gtest.h"

#include "utils/str.hpp"

#include "fixtures/identity.hpp"
using namespace Ark::Crypto;
using namespace fixtures::identity;
static constexpr const size_t PassphraseLength = 31U;

TEST(utils, str_strlen_safe) {
  const auto passphrase = tPassphrase;
  for (auto i = 0; i < PassphraseLength; ++i) {
    ASSERT_EQ(strlenSafe(&passphrase[i]), PassphraseLength - i);
  };
}

/**/

TEST(utils, str_string_to_bytes) {
  const auto passphraseBytes = StringToBytes(tPassphrase);
  for (auto i = 0; i < PassphraseLength; ++i) {
    ASSERT_EQ(passphraseBytes.at(i), tPassphraseBytes.at(i));
  };
  ASSERT_EQ(passphraseBytes.size(), PassphraseLength);
}

/**/