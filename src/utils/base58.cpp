/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "utils/base58.hpp"

#include <array>

#include "interfaces/identities.hpp"
#include "utils/str.hpp"

#include "bcl/Base58Check.hpp"

namespace Ark {
namespace Crypto {

// Returns a Version-byte and Ripemd160 Hash as a pair.
// Expects a c_string address as input.
PubkeyHashPair Base58::getHashPair(const char* address) {
  PubkeyHashPair out {};
  bcl::Base58Check::pubkeyHashFromBase58Check(address,
                                              out.pubkeyHash.data(),
                                              &out.version);
  return out;
}

/**/

// Returns a formatted Address string.
// Expects a 20-byte Ripemd160 Address hash a Network version-byte.
std::string Base58::parseHash(const uint8_t* pubkeyHash, uint8_t version) {
  std::string out(ADDRESS_STRING_LEN + 1, '\0');  // (+1, null terminator)
  bcl::Base58Check::pubkeyHashToBase58Check(pubkeyHash, version, &out[0]);
  return out;
}

/**/

// Returns a Wif string from PrivateKey-bytes and a Wif version-byte.
std::string Base58::getWif(const uint8_t* privateKeyBytes, uint8_t version) {
  std::string out(WIF_STRING_LEN + 1, '\0');
  bcl::Base58Check::privateKeyToBase58Check(bcl::Uint256(privateKeyBytes),
                                                         version,
                                                         true,
                                                         &out[0]);
  return out;
}

/**/

// Returns PrivateKey bytes from a Wif string and a Wif version-byte.
PrivateKeyBytes Base58::parseWif(const char* wif, uint8_t* outVersion) {
  if (!Base58::validate(wif, WIF_STRING_LEN)) { return {}; };

  bcl::Uint256 num;
  bool compressed;
  bcl::Base58Check::privateKeyFromBase58Check(wif,
                                              num,
                                              outVersion,
                                              &compressed);

  PrivateKeyBytes privateKey;
  num.getBigEndianBytes(privateKey.data());
  return privateKey;
}

/**/

namespace {  // NOLINT
const size_t BASE58_TABLE_LEN = 128U;
const std::array<int8_t, BASE58_TABLE_LEN> Base58Table = {{
  #include "base58.table"
}};
}  // namespace

/**/

// Validates that a given string is Base58 encoded.
// An Address will be 34-chars.
// A Wif will be 52-chars.
bool Base58::validate(const char* str, size_t size) {
  auto length = strlenSafe(str);
  if (size == 0 || length != size) { return false; };

  for (auto i = 0U; i < length; ++i) {
    if (Base58Table.at(str[i]) == 0) { return false; };
  };

  return true;
};

}  // namespace Crypto
}  // namespace Ark
