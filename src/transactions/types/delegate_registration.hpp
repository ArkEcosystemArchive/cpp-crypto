/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_DELEGATE_REGISTRATION_HPP
#define ARK_TRANSACTIONS_TYPES_DELEGATE_REGISTRATION_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

const uint8_t USERNAME_MIN      = 3U;
const uint8_t USERNAME_MAX      = 20U;

////////////////////////////////////////////////////////////////////////////////

struct DelegateRegistration {
    uint8_t                                 length;         // min: 3, max: 20
    std::array<uint8_t, USERNAME_MAX>       username;       // 3 <=> 20 bytes

    static uint32_t Deserialize(DelegateRegistration *registration,
                                const uint8_t *buffer);

    static uint32_t Serialize(const DelegateRegistration &registration,
                              uint8_t *buffer);

    static std::map<std::string, std::string> getMap(
            const DelegateRegistration &registration);

    DelegateRegistration() : length(0U), username() {}
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
