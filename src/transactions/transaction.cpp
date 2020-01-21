/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/transaction.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "crypto/curve.hpp"
#include "crypto/hash.hpp"

#include "identities/keys.hpp"

#include "transactions/deserializer.hpp"
#include "transactions/serializer.hpp"

#include "transactions/defaults/offsets.hpp"

#include "transactions/transaction_data.hpp"

#include "transactions/mapping.hpp"

#include "utils/hex.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Compute the unique transaction ID.
auto Transaction::getId() const -> Hash32 {
    const auto serialized = this->toBytes();
    return Hash::sha256(serialized.data(), serialized.size());
}

////////////////////////////////////////////////////////////////////////////////
// Sign the transaction using a passphrase.
auto Transaction::sign(const std::string &passphrase) -> bool {
    if (passphrase.empty()) {
        return false;
    }

    auto keys = identities::Keys::fromPassphrase(passphrase.c_str());

    std::copy(keys.publicKey.begin(),
              keys.publicKey.end(),
              this->data.senderPublicKey.begin());

    const auto serialized = this->toBytes({ true, true });
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    const auto success = Curve::Ecdsa::sign(hash32.data(),
                                            keys.privateKey.data(),
                                            &this->data.signature);

    memset(&keys, 0, sizeof(keys));

    if (success) {
        std::copy_n(this->getId().begin(), HASH_32_LEN, this->data.id.begin());
    }

    return success;
}

////////////////////////////////////////////////////////////////////////////////
// Sign the Transaction using a Second Passphrase.
auto Transaction::secondSign(const std::string &secondPassphrase) -> bool {
    if (this->data.signature.empty() || this->data.signature.at(0) == 0 ||
        secondPassphrase.empty()) {
        return false;
    }

    auto keys = identities::Keys::fromPassphrase(secondPassphrase.c_str());

    const auto serialized = this->toBytes({ false, true });
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    const auto success = Curve::Ecdsa::sign(hash32.data(),
                                            keys.privateKey.data(),
                                            &this->data.secondSignature);

    memset(&keys, 0, sizeof(keys));

    return success;
}

////////////////////////////////////////////////////////////////////////////////
// Verify the Transaction.
auto Transaction::verify() const -> bool {
    // skip both signatures,
    // neither should be present in the signing hash.
    const auto serialized = this->toBytes({ true, true });
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
    const auto serialized = this->toBytes({ false, true });
    const auto hash32 = Hash::sha256(serialized.data(), serialized.size());

    return Curve::Ecdsa::verify(hash32.data(),
                                secondPublicKey,
                                this->data.secondSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Deserialize the given Hex string via AIP11.
auto Transaction::deserialize(const std::vector<uint8_t> &serialized) -> bool {
    if (!Deserializer::deserialize(&this->data, serialized)) {
        return false;
    }

    std::copy_n(this->getId().begin(), HASH_32_LEN, this->data.id.begin());

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Serialize the object via AIP11.
auto Transaction::serialize() -> std::vector<uint8_t> {
    const auto serialized = Serializer::serialize(this->data);
    if (serialized.empty()) {
        return {};
    }

    std::copy_n(this->getId().begin(), HASH_32_LEN, this->data.id.begin());

    return serialized;
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into its byte representation.
auto Transaction::toBytes(const SerializerOptions &options) const
                                -> std::vector<uint8_t> {
    return Serializer::serialize(this->data, options);
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
    return Mapping::getMap(this->data);
}

////////////////////////////////////////////////////////////////////////////////
// Turn the Transaction into a JSON string using `toMap()` as the source.
auto Transaction::toJson() const -> std::string {
    return Mapping::toJson(this->toMap());
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
