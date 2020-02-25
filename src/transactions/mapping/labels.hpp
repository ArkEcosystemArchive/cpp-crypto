/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_MAPPING_LABELS_HPP
#define ARK_TRANSACTIONS_MAPPING_LABELS_HPP

#include <cstddef>

namespace Ark {
namespace Crypto {
namespace transactions {  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// Mapping Label Constants
constexpr auto KEY_VERSION_LABEL            = "version";
constexpr size_t KEY_VERSION_SIZE           = 7;

constexpr auto KEY_NETWORK_LABEL            = "network";
constexpr size_t  KEY_NETWORK_SIZE          = 7;

constexpr auto KEY_TYPEGROUP_LABEL          = "typeGroup";
constexpr size_t KEY_TYPEGROUP_SIZE         = 8;

constexpr auto KEY_TYPE_LABEL               = "type";
constexpr size_t KEY_TYPE_SIZE              = 4;

constexpr auto KEY_NONCE_LABEL              = "nonce";
constexpr size_t KEY_NONCE_SIZE             = 5;

constexpr auto KEY_TIMESTAMP_LABEL          = "timestamp";
constexpr size_t KEY_TIMESTAMP_SIZE         = 9;

constexpr auto KEY_SENDER_PUBLICKEY_LABEL   = "senderPublicKey";
constexpr size_t KEY_SENDER_PUBLICKEY_SIZE  = 15;

constexpr auto KEY_FEE_LABEL                = "fee";
constexpr size_t KEY_FEE_SIZE               = 3;

constexpr auto KEY_VENDORFIELD_LABEL        = "vendorField";
constexpr size_t KEY_VENDORFIELD_SIZE       = 11;

constexpr auto KEY_SIGNATURE_LABEL          = "signature";
constexpr size_t KEY_SIGNATURE_SIZE         = 9;

constexpr auto KEY_SECOND_SIGNATURE_LABEL   = "secondSignature";
constexpr size_t KEY_SECOND_SIGNATURE_SIZE  = 15;

constexpr auto KEY_ID_LABEL                 = "id";
constexpr size_t KEY_ID_SIZE                = 2;

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif  // #define ARK_TRANSACTIONS_MAPPING_LABELS_HPP
