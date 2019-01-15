
#include "gtest/gtest.h"

#include "identities/mnemonic.h"

#include <set>
#include <string>

namespace {

const auto MAX_WORD_BYTES =
    ((8 * 4) + 1) *
    24;  // ((8 characters per word * 4 potential octets per character) + 1 nul terminator) * maximum of 24 words
}

// Note:  generate_mnemonic_valid_[lang] tests could be refactored to use a single helper function with a language
// argument.
//        This causes problems with AUnit when building and testing IoT due to ASSERT macros not being available.
TEST(mnemonic, generate_mnemonic_valid_en) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::en);
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

TEST(mnemonic, generate_mnemonic_valid_es) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::es);
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

TEST(mnemonic, generate_mnemonic_valid_ja) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::ja);
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

TEST(mnemonic, generate_mnemonic_valid_it) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::it);
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

TEST(mnemonic, generate_mnemonic_valid_fr) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::fr);
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

TEST(mnemonic, generate_mnemonic_valid_ko) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase = Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::ko);
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

TEST(mnemonic, generate_mnemonic_valid_zh_Hans) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase =
        Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::zh_Hans);
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

TEST(mnemonic, generate_mnemonic_valid_zh_Hant) {
  for (auto num_words = 12u; num_words <= 24u; num_words += 3) {
    auto passphrase =
        Ark::Crypto::Identities::Mnemonic::generate(num_words, Ark::Crypto::Identities::Language::zh_Hant);
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

// These tests depend on the library asserting, disable this test for Release builds
#ifdef DEBUG
TEST(mnemonic, generate_mnemonic_invalid) {
  for (auto num_words = 0u; num_words <= 100u; ++num_words) {
    // skip the valid word cases
    if (num_words == 12u || num_words == 15u || num_words == 18u || num_words == 21u || num_words == 24u) {
      continue;
    }

    ASSERT_DEATH(Ark::Crypto::Identities::Mnemonic::generate(num_words), "");
  }
}
#endif
