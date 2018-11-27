
#include "gtest/gtest.h"

#include "identities/mnemonic.h"

#include <set>
#include <string>

namespace {

const auto MAX_WORD_BYTES = ((8 * 4) + 1) * 24;  // ((8 characters per word * 4 potential octets per character) + 1 nul terminator) * maximum of 24 words

void generate_mnemonic_valid(Ark::Crypto::Identities::Language language)
{
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, language);
    // use a set to ensure no duplicate words can be added
    std::set<std::string> words;
    char s[MAX_WORD_BYTES] = {};
    strncpy(s, passphrase.c_str(), sizeof(s));
    auto pch = strtok(s, " ");
    while (pch != nullptr) {
      ASSERT_TRUE(words.insert(pch).second);
      pch = strtok(nullptr, " ");
    }

    ASSERT_EQ(num_words, words.size());
  }
}

}

TEST(mnemonic, generate_mnemonic_valid_en) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::en);
}

TEST(mnemonic, generate_mnemonic_valid_es) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::es);
}

TEST(mnemonic, generate_mnemonic_valid_ja) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::ja);
}

TEST(mnemonic, generate_mnemonic_valid_it) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::it);
}

TEST(mnemonic, generate_mnemonic_valid_fr) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::fr);
}

TEST(mnemonic, generate_mnemonic_valid_ko) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::ko);
}

TEST(mnemonic, generate_mnemonic_valid_zh_Hans) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::zh_Hans);
}

TEST(mnemonic, generate_mnemonic_valid_zh_Hant) {
  generate_mnemonic_valid(Ark::Crypto::Identities::Language::zh_Hant);
}


// These tests depend on the library asserting, disable this test for Release builds
#ifdef DEBUG
TEST(mnemonic, generate_mnemonic_invalid)
{
  for (auto num_words = 0u; num_words <= 100u; ++num_words) {
    // skip the valid word cases
    if (num_words == 12u || num_words == 15u || num_words == 18u || num_words == 21u || num_words == 24u) { continue; }

    ASSERT_DEATH(Ark::Crypto::Identities::Mnemonic::generate(num_words), "");
  }
}
#endif
