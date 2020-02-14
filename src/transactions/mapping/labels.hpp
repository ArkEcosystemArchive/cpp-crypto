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

#include <string>

namespace Ark {
namespace Crypto {
namespace transactions {  // NOLINT

////////////////////////////////////////////////////////////////////////////////
// Mapping Label Constants
constexpr auto KEY_VERSION_LABEL            = "version";
const auto KEY_VERSION_SIZE                 = strlen(KEY_VERSION_LABEL);

constexpr auto KEY_NETWORK_LABEL            = "network";
const auto KEY_NETWORK_SIZE                 = strlen(KEY_NETWORK_LABEL);

constexpr auto KEY_TYPEGROUP_LABEL          = "typeGroup";
const auto KEY_TYPEGROUP_SIZE               = strlen(KEY_TYPEGROUP_LABEL);

constexpr auto KEY_TYPE_LABEL               = "type";
const auto KEY_TYPE_SIZE                    = strlen(KEY_TYPE_LABEL);

constexpr auto KEY_NONCE_LABEL              = "nonce";
const auto KEY_NONCE_SIZE                   = strlen(KEY_NONCE_LABEL);

constexpr auto KEY_TIMESTAMP_LABEL          = "timestamp";
const auto KEY_TIMESTAMP_SIZE               = strlen(KEY_TIMESTAMP_LABEL);

constexpr auto KEY_SENDER_PUBLICKEY_LABEL   = "senderPublicKey";
const auto KEY_SENDER_PUBLICKEY_SIZE        = strlen(KEY_SENDER_PUBLICKEY_LABEL);

constexpr auto KEY_FEE_LABEL                = "fee";
const auto KEY_FEE_SIZE                     = strlen(KEY_FEE_LABEL);

constexpr auto KEY_VENDORFIELD_LABEL        = "vendorField";
const auto KEY_VENDORFIELD_SIZE             = strlen(KEY_VENDORFIELD_LABEL);

constexpr auto KEY_SIGNATURE_LABEL          = "signature";
const auto KEY_SIGNATURE_SIZE               = strlen(KEY_SIGNATURE_LABEL);

constexpr auto KEY_SECOND_SIGNATURE_LABEL   = "secondSignature";
const auto KEY_SECOND_SIGNATURE_SIZE        = strlen(KEY_SECOND_SIGNATURE_LABEL);

constexpr auto KEY_ID_LABEL                 = "id";
const auto KEY_ID_SIZE                      = strlen(KEY_ID_LABEL);

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif  // #define ARK_TRANSACTIONS_MAPPING_LABELS_HPP
