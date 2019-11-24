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
static constexpr const uint8_t COMMON_HEADER        = 0xFF;
static constexpr const uint8_t COMMON_VERSION_V1    = 1U;
static constexpr const uint8_t COMMON_VERSION_V2    = 2U;
static constexpr const uint8_t COMMON_MAINNET       = 23U;
static constexpr const uint8_t COMMON_DEVNET        = 30U;
static constexpr const uint16_t COMMON_TYPEGROUP    = 1U;
static constexpr const uint64_t COMMON_NONCE        = 1ULL;

////////////////////////////////////////////////////////////////////////////////
// Common Test Strings
static constexpr const char* COMMON_VERSION_V2_STRING   = "2";
static constexpr const char* COMMON_MAINNET_STRING      = "23";
static constexpr const char* COMMON_TYPEGROUP_STRING    = "1";
static constexpr const char* COMMON_NONCE_STRING        = "1";

static constexpr const char* COMMON_PUBLICKEY_STRING    = "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192";

////////////////////////////////////////////////////////////////////////////////
// Common PublicKey Fixture
// - 034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192
static constexpr const uint8_t COMMON_PUBLICKEY[] = {
    3,  65, 81,  163, 236, 70, 181, 103, 10,  104, 43,
    10, 99, 57,  79,  134, 53, 135, 209, 188, 151, 72,
    59, 27, 108, 112, 235, 88, 231, 240, 174, 209, 146 };

#endif
