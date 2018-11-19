
#include "gtest/gtest.h"
#include "arkCrypto.h"

TEST(mnemonic, generate_mnemonic_valid)
{
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words);
    // use a set to ensure no duplicate words can be added
    std::set<std::string> words;
    char s[256] = {};
    strncpy(s, passphrase.c_str(), sizeof(s));
    auto pch = strtok(s, " ");
    while (pch != nullptr) {
      ASSERT_TRUE(words.insert(pch).second);
      pch = strtok(nullptr, " ");
    }

    ASSERT_EQ(num_words, words.size());
  }
}

TEST(mnemonic, generate_mnemonic_invalid)
{
  for (auto num_words = 0u; num_words <= 100u; ++num_words) {
    // skip the valid word cases
    if (num_words == 12u || num_words == 15u || num_words == 18u || num_words == 21u || num_words == 24u) { continue; }

    ASSERT_DEATH(Ark::Crypto::Identities::Mnemonic::generate(num_words), "");
  }
}
