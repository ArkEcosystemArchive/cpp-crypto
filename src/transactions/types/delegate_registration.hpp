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

#include "utils/json.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
constexpr uint8_t USERNAME_MIN      = 3U;
constexpr uint8_t USERNAME_MAX      = 20U;

////////////////////////////////////////////////////////////////////////////////
// Type 2 - Delegate Registration
//
// Min Length: 3
// Max Length: 20
//
// ---
struct DelegateRegistration {  // LCOV_EXCL_LINE
    ////////////////////////////////////////////////////////////////////////////
    uint8_t                                 length      { 0U };
    std::array<uint8_t, USERNAME_MAX>       username    { };

    ////////////////////////////////////////////////////////////////////////////
    static size_t Deserialize(DelegateRegistration *registration,
                              const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static size_t Serialize(const DelegateRegistration &registration,
                            uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static void addToMap(const DelegateRegistration &registration,
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
