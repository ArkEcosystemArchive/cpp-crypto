/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/delegate_registration.hpp"

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////

// Deserialize Delegate Registration (Type 2) - 4 <=> 21 Bytes
//
// @param DelegateRegistration *registration.
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Username Length - 1 Byte:
// - registration.length = buffer[0];
//
// Username - 3 <=> 20 Bytes:
// - std::move(&buffer[sizeof(uint8_t)],  &buffer[1 + registration->length], registration->username.begin());
//
// ---
auto DelegateRegistration::Deserialize(DelegateRegistration *registration,
                                       const uint8_t *buffer) -> uint32_t {
    registration->length = buffer[0];                               // 1 Byte

    if (registration->length < USERNAME_MIN ||
        registration->length > USERNAME_MAX) {
        return 0UL;
    }

    std::move(&buffer[sizeof(uint8_t)],                             // 3 <=> 20
              &buffer[sizeof(uint8_t) + registration->length],
              registration->username.begin());

    return sizeof(uint8_t) + registration->length;                   // 4 <=> 21
}

////////////////////////////////////////////////////////////////////////////////

// Serialize Delegate Registration (Type 2) - 4 <=> 21 Bytes
//
// @param const DelegateRegistration &registration.
// @param uint8_t *buffer: The buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Username Length - 1 Byte:
// - buffer[0] = registration.length;
//
// Username - 3 <=> 20 Bytes:
// - std::move(registration.username.begin(), registration.username.end(),&buffer[1]);
//
// ---
auto DelegateRegistration::Serialize(const DelegateRegistration &registration,
                                     uint8_t *buffer) -> uint32_t {
    buffer[0] = registration.length;                                // 1 Byte

    if (registration.length < USERNAME_MIN ||
        registration.length > USERNAME_MAX) {
        return 0UL;
    }

    std::move(registration.username.begin(),                       // 3 <=> 20
              registration.username.end(),
              &buffer[sizeof(uint8_t)]);

    return sizeof(uint8_t) + registration.length;                   // 4 <=> 21
}

////////////////////////////////////////////////////////////////////////////////

// Return a Map of the Delegate Registration Username.
auto DelegateRegistration::getMap(const DelegateRegistration &registration) 
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    map.emplace("usernameLen", UintToString(registration.length));

    map.emplace(
        "username",
        std::string(registration.username.begin(),
                    registration.username.begin() + registration.length));

    return map;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
