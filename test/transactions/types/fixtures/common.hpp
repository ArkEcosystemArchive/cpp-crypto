/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_COMMON_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_COMMON_HPP

#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
// Common Test Numbers
constexpr uint8_t COMMON_HEADER         = 0xFF;
constexpr uint8_t COMMON_VERSION_V1     = 1U;
constexpr uint8_t COMMON_VERSION_V2     = 2U;
constexpr uint8_t COMMON_MAINNET        = 23U;
constexpr uint8_t COMMON_DEVNET         = 30U;
constexpr uint16_t COMMON_TYPEGROUP     = 1U;
constexpr uint64_t COMMON_NONCE         = 1ULL;

////////////////////////////////////////////////////////////////////////////////
// Common Test Strings
constexpr auto COMMON_VERSION_V2_STRING     = "2";
constexpr auto COMMON_MAINNET_STRING        = "23";
constexpr auto COMMON_TYPEGROUP_STRING      = "1";
constexpr auto COMMON_NONCE_STRING          = "1";

#endif
