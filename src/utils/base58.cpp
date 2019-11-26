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
#include <cstddef>
#include <utility>

#include "interfaces/identities.hpp"
#include "utils/str.hpp"

#include "bcl/Base58Check.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
auto Base58::checkEncode(const uint8_t *data, const size_t length)
        -> std::string {
    const std::array<uint8_t, BASE58_ALPHABET_LEN> BASE58ALPHABET = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
        'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    const size_t tmpSize    = 164UL;
    const size_t limit      = 256UL;
    const auto limitFlag    = 0xFF;

    std::vector<uint8_t> tmp;
    tmp.resize(tmpSize);

    std::vector<uint8_t> buffer;
    buffer.resize(tmpSize);

    size_t j;
    size_t startAt;
    size_t zeroCount = 0;

    if (length > tmp.size()) {
        return {};
    }

    std::move(data, data + length, tmp.begin());
    while ((zeroCount < length) && (tmp.at(zeroCount) == 0U)) {
        ++zeroCount;
    }

    j = 2U * length;
    startAt = zeroCount;
    while (startAt < length) {
        size_t remainder = 0U;
        size_t divLoop;

        for (divLoop = startAt; divLoop < length; divLoop++) {
            auto digit256 = (uint16_t)(tmp.at(divLoop) & limitFlag);
            auto tmpDiv = remainder * limit + digit256;
            tmp.at(divLoop) = (uint8_t)(tmpDiv / BASE58_ALPHABET_LEN);
            remainder = (tmpDiv % BASE58_ALPHABET_LEN);
        }

        if (tmp.at(startAt) == 0U) {
            ++startAt;
        }

        buffer.at(--j) = (uint8_t)BASE58ALPHABET.at(remainder);
    }

    while ((j < (2U * length)) && (buffer.at(j) == BASE58ALPHABET.at(0))) {
        ++j;
    }

    while (zeroCount-- > 0U) {
        buffer.at(--j) = BASE58ALPHABET.at(0);
    }

    auto outLength = 2U * length - j;

    return std::string((buffer.begin() + j), buffer.begin() + j + outLength);
}

////////////////////////////////////////////////////////////////////////////////
// Returns a Version-byte and Ripemd160 Hash as a pair.
// Expects a c_string address as input.
auto Base58::getHashPair(const char *address) -> PubkeyHashPair {
    PubkeyHashPair out {};
    bcl::Base58Check::pubkeyHashFromBase58Check(address,
                                                out.pubkeyHash.data(),
                                                &out.version);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// Returns a formatted Address string.
// Expects a 20-byte Ripemd160 Address hash a Network version-byte.
auto Base58::parseAddressHash(const AddressHash &addressHash) -> std::string {
    std::string out(ADDRESS_STR_LEN, '\0');
    bcl::Base58Check::pubkeyHashToBase58Check(&addressHash.at(1),
                                              addressHash.at(0),
                                              &out[0]);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// Returns a formatted Address string.
// Expects a 20-byte Ripemd160 Address hash a Network version-byte.
auto Base58::parsePubkeyHash(const uint8_t *pubkeyHash, const uint8_t version)
        -> std::string {
    std::string out(ADDRESS_STR_LEN, '\0');
    bcl::Base58Check::pubkeyHashToBase58Check(pubkeyHash, version, &out[0]);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// Returns a Wif string from PrivateKey-bytes and a Wif version-byte.
auto Base58::getWif(const uint8_t *privateKeyBytes, const uint8_t version)
        -> std::string {
    std::string out(WIF_STRING_LEN, '\0');
    bcl::Base58Check::privateKeyToBase58Check(bcl::Uint256(privateKeyBytes),
                                                           version,
                                                           true,
                                                           &out[0]);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// Returns PrivateKey bytes from a Wif string and a Wif version-byte.
auto Base58::parseWif(const char *wif, uint8_t* outVersion) -> PrivateKeyBytes {
    if (!Base58::validate(wif, WIF_STRING_LEN)) {
        return PrivateKeyBytes();
    }

    bcl::Uint256 num;
    bool compressed;
    bcl::Base58Check::privateKeyFromBase58Check(wif,
                                                num,
                                                outVersion,
                                                &compressed);

    PrivateKeyBytes privateKey {};
    num.getBigEndianBytes(privateKey.data());

    return privateKey;
}

////////////////////////////////////////////////////////////////////////////////
static const size_t BASE58_TABLE_LEN = 128U;
static const std::array<int8_t, BASE58_TABLE_LEN> Base58Table = {{
  #include "base58.table"
}};

////////////////////////////////////////////////////////////////////////////////
// Validates that a given string is Base58 encoded.
// An Address will be 34-chars.
// A Wif will be 52-chars.
auto Base58::validate(const char *str, const size_t size) -> bool {
    auto length = strlenSafe(str);
    if (size == 0 || length != size) {
        return false;
    }

    for (auto i = 0U; i < length; ++i) {
        if (Base58Table.at(str[i]) == 0) {
            return false; 
        }
    }

    return true;
}

}  // namespace Crypto
}  // namespace Ark
