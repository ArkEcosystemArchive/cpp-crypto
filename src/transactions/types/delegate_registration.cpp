/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/delegate_registration.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>

#include "utils/json.h"
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
// - std::copy_n(&buffer[1], registration->length, registration->username.begin());
//
// ---
auto DelegateRegistration::Deserialize(DelegateRegistration *registration,
                                       const uint8_t *buffer) -> size_t {
    if (buffer[0] < USERNAME_MIN || buffer[0] > USERNAME_MAX) {
        return 0UL;
    }

    registration->length = buffer[0];                               // 1 Byte

    std::copy_n(&buffer[sizeof(uint8_t)],                   // 3 <=> 20 Bytes
                registration->length,
                registration->username.begin());

    return sizeof(uint8_t) + registration->length;          // 4 <=> 21 Bytes
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
// - std::copy_n(registration.username.begin(), registration.length, &buffer[1]);
//
// ---
auto DelegateRegistration::Serialize(const DelegateRegistration &registration,
                                     uint8_t *buffer) -> size_t {
    if (registration.length < USERNAME_MIN ||
        registration.length > USERNAME_MAX) {
        return 0UL;
    }

    buffer[0] = registration.length;                                // 1 Byte

    std::copy_n(registration.username.begin(),              // 3 <=> 20 Bytes
                registration.length,
                &buffer[sizeof(uint8_t)]);

    return sizeof(uint8_t) + registration.length;           // 4 <=> 21 Bytes
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
constexpr auto OBJECT_DELEGATE_LABEL    = "delegate";
constexpr size_t KEY_DELEGATE_SIZE      = 8;

constexpr auto KEY_USERNAME_LABEL       = "username";
constexpr size_t KEY_USERNAME_SIZE      = 8;

////////////////////////////////////////////////////////////////////////////////
// Add Delegate Registration Asset data to a Transaction Map.
void DelegateRegistration::addToMap(const DelegateRegistration &registration,
                                    std::map<std::string, std::string> &map) {
    map.emplace(KEY_USERNAME_LABEL,
                std::string(registration.username.begin(),
                registration.username.begin() + registration.length));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a Delegate Registration-type Transaction.
auto DelegateRegistration::getJsonCapacity() -> size_t {
    return JSON_OBJECT_SIZE(1) + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1) + KEY_DELEGATE_SIZE +
           JSON_OBJECT_SIZE(1) + KEY_USERNAME_SIZE + USERNAME_MAX;
}

////////////////////////////////////////////////////////////////////////////////
// Add Delegate Registration data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain Delegate Registration data.
//
// ---
void DelegateRegistration::addToJson(
        DynamicJsonDocument &jsonDoc,
        const std::map<std::string, std::string> &map) {
    const auto asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    const auto registration = asset.createNestedObject(OBJECT_DELEGATE_LABEL);

    // Username
    registration[KEY_USERNAME_LABEL] = map.at(KEY_USERNAME_LABEL);
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
