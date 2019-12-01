/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/transaction.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"

#include "identities/keys.hpp"

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "transactions/defaults/offsets.hpp"

#include "transactions/transaction_data.hpp"

#include "transactions/mapping.hpp"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/json.h"
#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Compute the unique transaction ID.
auto Transaction::getId() const -> Hash32 {
    const auto serialized = this->toBytes(false, false);
    return Hash::sha256(serialized.data(), serialized.size());
}

////////////////////////////////////////////////////////////////////////////////
// Sign the transaction using a passphrase.
auto Transaction::sign(const std::string &passphrase) -> bool {
    if (passphrase.empty()) {
        return false;
    }

    const auto keys = identities::Keys::fromPassphrase(passphrase.c_str());

    std::move(keys.publicKey.begin(),
              keys.publicKey.end(),
              this->data.senderPublicKey.begin());

    const auto serialized = this->toBytes(true, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    this->data.signature.reserve(SIGNATURE_ECDSA_MAX);

    return Curve::Ecdsa::sign(hash32.data(),
                              keys.privateKey.data(),
                              &this->data.signature);
}

////////////////////////////////////////////////////////////////////////////////
// Sign the Transaction using a Second Passphrase.
auto Transaction::secondSign(const std::string &secondPassphrase) -> bool {
    if (this->data.signature.empty() || secondPassphrase.empty()) {
        return false;
    }

    const auto keys = identities::Keys::fromPassphrase(secondPassphrase.c_str());

    const auto serialized = this->toBytes(false, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    this->data.secondSignature.reserve(SIGNATURE_ECDSA_MAX);
    
    return Curve::Ecdsa::sign(hash32.data(),
                              keys.privateKey.data(),
                              &this->data.secondSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Verify the Transaction.
auto Transaction::verify() const -> bool {
    // skip both signatures,
    // neither should be present in the signing hash.
    const auto serialized = this->toBytes(true, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    return Curve::Ecdsa::verify(hash32.data(),
                                this->data.senderPublicKey.data(),
                                this->data.signature);
}

////////////////////////////////////////////////////////////////////////////////
// Verify the Transaction using a Second PublicKey.
auto Transaction::secondVerify(const uint8_t *secondPublicKey) const -> bool {
    // include only the first signature,
    // that should be present signing hash for a second signing.
    const auto serialized = this->toBytes(false, true);
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    return Curve::Ecdsa::verify(hash32.data(),
                                secondPublicKey,
                                this->data.secondSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Deserialize the given Hex string via AIP11.
auto Transaction::deserialize(const std::vector<uint8_t> &serialized) -> bool {
    return Deserializer::deserialize(&this->data, serialized);
}

////////////////////////////////////////////////////////////////////////////////
// Serialize the object via AIP11.
auto Transaction::serialize() -> std::vector<uint8_t> {
    return Serializer::serialize(this->data);
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into its byte representation.
auto Transaction::toBytes(bool excludeSignature,
                          bool excludeSecondSignature) const
                                -> std::vector<uint8_t> {
    return Serializer::serialize(this->data,
                                 { excludeSignature, excludeSecondSignature });
}

////////////////////////////////////////////////////////////////////////////////
// Turn the transaction into a standardized array.
//
// This concept of an array in is quite different compared to other ARK SDKs.
// C++11 doesn't have an 'Any' type, so we'll need to use a string map here.
//
// Json Sizes are approximated using 'https://arduinojson.org/v6/assistant/'
//
// --
auto Transaction::toMap() const -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map = Mapping::getMap(this->data);

    // Add the Transaction Id
    map["id"] = BytesToHex(this->getId());

    return map;
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into a JSON string using `toMap()` as the source.
auto Transaction::toJson() const -> std::string {
    return Mapping::toJson(this->toMap());
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
