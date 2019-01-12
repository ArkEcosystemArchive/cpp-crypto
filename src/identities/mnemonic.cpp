/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/mnemonic.h"

#include "bip39/bip39.h"

#include <cassert>

namespace Ark {
namespace Crypto {
namespace Identities {

std::string Mnemonic::generate(size_t num_words /* = 12u */, Language language /* = Language::en */) {
  static const std::map<size_t, BIP39::entropy_bits_t> words_to_entropy = {{12, BIP39::entropy_bits_t::_128},
                                                                           {15, BIP39::entropy_bits_t::_160},
                                                                           {18, BIP39::entropy_bits_t::_192},
                                                                           {21, BIP39::entropy_bits_t::_224},
                                                                           {24, BIP39::entropy_bits_t::_256}};
  static const std::map<Language, BIP39::language> language_map = {
      {Language::en, BIP39::language::en},           {Language::es, BIP39::language::es},
      {Language::ja, BIP39::language::ja},           {Language::it, BIP39::language::it},
      {Language::fr, BIP39::language::fr},           {Language::ko, BIP39::language::ko},
      {Language::zh_Hans, BIP39::language::zh_Hans}, {Language::zh_Hant, BIP39::language::zh_Hant}};

  const auto entropy_it = words_to_entropy.find(num_words);
  assert(entropy_it != words_to_entropy.end());

  const auto lang = language_map.find(language);
  assert(lang != language_map.end());

  return BIP39::generate_mnemonic(entropy_it->second, lang->second).to_string();
}

}  // namespace Identities
}  // namespace Crypto
}  // namespace Ark
