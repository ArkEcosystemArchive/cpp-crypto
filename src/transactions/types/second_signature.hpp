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

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Type 1 - Second Signature Registration
struct SecondSignature {
    ////////////////////////////////////////////////////////////////////////////
    PublicKeyBytes publicKey;

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(SecondSignature *registration,
                                const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const SecondSignature &registration,
                              uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static std::map<std::string, std::string> getMap(
            const SecondSignature &registration);

    ////////////////////////////////////////////////////////////////////////////
    SecondSignature() : publicKey() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
