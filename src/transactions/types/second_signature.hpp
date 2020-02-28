/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_SECOND_SIGNATURE_REGISTRATION_HPP
#define ARK_TRANSACTIONS_TYPES_SECOND_SIGNATURE_REGISTRATION_HPP

#include <cstdint>
#include <map>
#include <string>

#include "interfaces/identities.hpp"

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Type 1 - Second Signature Registration
struct SecondSignature {  // LCOV_EXCL_LINE
    ////////////////////////////////////////////////////////////////////////////
    PublicKeyBytes publicKey { };

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(SecondSignature *registration,
                                const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const SecondSignature &registration,
                              uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const SecondSignature &registration,
                         std::map<std::string, std::string> &map);

    ////////////////////////////////////////////////////////////////////////////
    static size_t getJsonCapacity();

    ////////////////////////////////////////////////////////////////////////////
    static void addToJson(DynamicJsonDocument &jsonDoc,
                          const std::map<std::string, std::string> &map);
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
