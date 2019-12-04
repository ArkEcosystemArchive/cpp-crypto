/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_INTERFACES_CONSTANTS_H
#define ARK_INTERFACES_CONSTANTS_H

#include <cstddef>
#include <cstring>

#include "utils/platform.h"

////////////////////////////////////////////////////////////////////////////////
// Hash
const size_t BASE58_ALPHABET_LEN    = 58U;
const size_t HASH_20_LEN            = 20U;
const size_t HASH_32_LEN            = 32U;
const size_t HASH_64_LEN            = 64U;

////////////////////////////////////////////////////////////////////////////////
// Address
const uint8_t ADDRESS_DEFAULT_VERSION   = 0x1E;  // (30) Base58 'D' | Devnet
const size_t ADDRESS_HASH_LEN           = 21U;
const size_t ADDRESS_STR_LEN            = 34U;

////////////////////////////////////////////////////////////////////////////////
// Privatekey
const size_t PRIVATEKEY_BYTE_LEN    = 32U;
const size_t PRIVATEKEY_STRING_LEN  = 64U;

////////////////////////////////////////////////////////////////////////////////
// PublicKey
const size_t PUBLICKEY_COMPRESSED_LEN       = 33U;
const size_t PUBLICKEY_COMPRESSED_STR_LEN   = 66U;
const size_t PUBLICKEY_UNCOMPRESSED_LEN     = 65U;

////////////////////////////////////////////////////////////////////////////////
// Signatures
const size_t SIGNATURE_ECDSA_MIN    = 70U;
const size_t SIGNATURE_ECDSA_MAX    = 72U;

////////////////////////////////////////////////////////////////////////////////
// Transactions
const uint8_t TRANSACTION_VERSION_TYPE_1    = 0x01;
const uint8_t TRANSACTION_VERSION_TYPE_2    = 0x02;

const uint32_t TRANSACTION_DEFAULT_HEADER       = 0xFF;
const uint32_t TRANSACTION_DEFAULT_TYPEGROUP    = 1UL;

// The Default and Max Tx Sizes aid in limiting the impact of dynamic allocation.
// Particularly in embedded environments, this also helps avoid overflow errors.
//
// These are currently used by Serializer and the MultiPayment Tx-type.
// They can be tweaked to suit whichever environment were developing for.
const size_t TX_DEFAULT_SIZE    = 512UL;

#if defined(USE_IOT)
    const size_t TX_MAX_SIZE    = 768UL;
#else
    const size_t TX_MAX_SIZE    = 20480UL;
#endif

////////////////////////////////////////////////////////////////////////////////
// Wif
const uint8_t WIF_DEFAULT_VERSION   = 0xAA;  // (170) Base58 'S'
const size_t WIF_STRING_LEN         = 52U;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
const auto KEY_ASSET_LABEL      = "asset";
const auto KEY_ASSET_SIZE       = strlen(KEY_ASSET_LABEL);

////////////////////////////////////////////////////////////////////////////////
// Misc
const uint8_t BASE_10 = 10U;

const size_t UINT64_MAX_CHARS   = 20U;
const size_t UINT32_MAX_CHARS   = 10U;
const size_t UINT16_MAX_CHARS   = 5U;
const size_t UINT8_MAX_CHARS    = 3U;

const size_t HASH_32_MAX_CHARS          = 2U * HASH_32_LEN;
const size_t SIGNATURE_ECDSA_MAX_CHARS  = 2U * SIGNATURE_ECDSA_MAX;

#endif
