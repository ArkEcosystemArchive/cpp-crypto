/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_UTILS_BASE58_HPP
#define ARK_UTILS_BASE58_HPP

#include <vector>
#include <string>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
struct Base58 {
    ////////////////////////////////////////////////////////////////////////////
    static std::string checkEncode(const uint8_t *data, const size_t &length);

    ////////////////////////////////////////////////////////////////////////////
    static PubkeyHashPair getHashPair(const char *address);

    ////////////////////////////////////////////////////////////////////////////
    static std::string parseAddressHash(const AddressHash &addressHash);

    ////////////////////////////////////////////////////////////////////////////
    static std::string parsePubkeyHash(const uint8_t *pubkeyHash,
                                       uint8_t version);

    ////////////////////////////////////////////////////////////////////////////
    static std::string getWif(const uint8_t *privateKeyBytes, uint8_t version);

    ////////////////////////////////////////////////////////////////////////////
    static PrivateKeyBytes parseWif(const char *wif, uint8_t *outVersion);

    ////////////////////////////////////////////////////////////////////////////
    static bool validate(const char *str, const size_t &size);
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace Crypto
}  // namespace Ark

#endif
