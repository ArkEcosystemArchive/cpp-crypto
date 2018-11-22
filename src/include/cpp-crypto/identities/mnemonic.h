/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef MNEMONIC_H
#define MNEMONIC_H

#include <string>

namespace Ark {
namespace Crypto {
namespace Identities {

enum class Language {
  en
};

class Mnemonic {
public:
  /// Generate a BIP39 passphrase with the given number of words (12,15,18,21,24) and given language
  static std::string generate(size_t num_words = 12u, Language language = Language::en);
};

}
}
}
#endif
