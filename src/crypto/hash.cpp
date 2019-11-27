/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "crypto/hash.hpp"

#include <algorithm>

#include "interfaces/identities.hpp"

#include "bcl/Ripemd160.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Sha256Hash.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Returns the RIPEMD160 hash of a publicKey bytes.
// Expects a 33-byte compressed PublicKey array.
auto Hash::ripemd160(const uint8_t *publicKeyBytes) -> PubkeyHash {
    PubkeyHash hash20 {};
    bcl::Ripemd160::getHash(publicKeyBytes,
                            PUBLICKEY_COMPRESSED_LEN,
                            hash20.data());
    return hash20;
}

////////////////////////////////////////////////////////////////////////////////
// Returns a 32-byte SHA256 hash of the input vector.
auto Hash::sha256(const uint8_t *inputBytes, const size_t size) -> Hash32 {
    auto result = bcl::Sha256::getHash(inputBytes, size);

    Hash32 hash32 {};
    std::move(result.value, result.value + HASH_32_LEN, hash32.begin());

    return hash32;
}

}  // namespace Crypto
}  // namespace Ark
