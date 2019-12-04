/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/
#include "crypto/curve.hpp"

#include <algorithm>
#include <vector>
#include <array>

#include "interfaces/identities.hpp"

#include "utils/hex.hpp"
#include "utils/platform.h"

#include "rfc6979/rfc6979.h"    // Nonce function

#include "bcl/Ecdsa.hpp"        // Signing operations
#include "bcl/Sha256.hpp"
#include "bcl/Sha256Hash.hpp"
#include "bcl/Uint256.hpp"

#include "bip66.h"              // ECDSA DER encoding

#include "uECC.h"               // publicKey operations

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Curve::Ecdsa::sign
//
// Sign the input hash with a privateKey using SECP256K1 ECDSA.
//
// Signing result is copied to the outgoing signature.
// Returns true if signing and encoding were both successful.
//
// const uint8_t *hash32
// - 32-byte array of the message hash to sign.
//
// const uint8_t *privateKeyBytes
// - 32-byte array of the privateKey.
//
// std::vector<uint8_t>& outSignature
// - Outgoing signature filled with the DER-encoded signing result.
//
// ---
auto Curve::Ecdsa::sign(const uint8_t *hash32,
                        const uint8_t *privateKeyBytes,
                        std::vector<uint8_t> *outSignature) -> bool {
    if (hash32 == nullptr || privateKeyBytes == nullptr) {
        return false;
    }

    // Create the Signing nonce
    Hash32 nonce32 {};
    nonce_function_rfc6979(nonce32.data(),
                           hash32,
                           privateKeyBytes,
                           nullptr, nullptr, 0);

    // Sign the hash using PrivateKey bytes and the Signing Nonce.
    // Outputs Signature values to the R and S elements.
    bcl::Uint256 r;
    bcl::Uint256 s;
    bcl::Ecdsa::sign(bcl::Uint256(privateKeyBytes),
                          bcl::Sha256Hash(hash32, HASH_32_LEN),
                          bcl::Uint256(nonce32.data()),
                          r, s);

    // Copy the big-endian bytes into and R/S element buffer.
    std::array<uint8_t, HASH_64_LEN> rsBuffer;
    r.getBigEndianBytes(&rsBuffer[0]);
    s.getBigEndianBytes(&rsBuffer[HASH_32_LEN]);

    // Encode R & S Elements into a BIP66-encoded signature.
    // returns 'true' if DER encoding was successful.
    return BIP66::encode(rsBuffer.data(), *outSignature);
}

////////////////////////////////////////////////////////////////////////////////
// Curve::Ecdsa::verify
//
// Verify a hash and publicKey against a signature using SECP256K1 ECDSA.
//
// Signing result is copied to the outgoing signature.
// Returns true if signing and encoding were both successful.
//
// const uint8_t *hash32
// - 32-byte array of the message hash to to verify.
//
// const uint8_t *publicKeyBytes
// - 33-byte array of the compressed-type publicKey.
//
// std::vector<uint8_t>& signature
// - DER-encoded Signature by which the hash and publicKey are being verified.
//
// ---
auto Curve::Ecdsa::verify(const uint8_t *hash32,
                          const uint8_t *publicKeyBytes,
                          const std::vector<uint8_t> &signature) -> bool {
    if (hash32 == nullptr || publicKeyBytes == nullptr) {
        return false;
    }

    // Decompressed the publicKey
    const auto decompressed = Curve::PublicKey::decompress(publicKeyBytes);

    // Build the curvePoint
    bcl::FieldInt x(BytesToHex(&decompressed[0],
                               &decompressed[HASH_32_LEN]).c_str());
    bcl::FieldInt y(BytesToHex(&decompressed[HASH_32_LEN],
                               &decompressed[HASH_64_LEN]).c_str());

    /// Decode signature from DER into R and S element buffers.
    std::vector<uint8_t> r(HASH_32_LEN, 0);
    std::vector<uint8_t> s(HASH_32_LEN, 0);

    BIP66::decode(signature, r, s);

    // Verify
    return bcl::Ecdsa::verify(
        bcl::CurvePoint(x, y),
        bcl::Sha256Hash(hash32, HASH_32_LEN),
        bcl::Uint256(&r.at(r.at(0) == 0U ? 1U : 0U)),
        bcl::Uint256(&s.at(s.at(0) == 0U ? 1U : 0U)));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Curve::PublicKey::compute
//
// Compute a compressed-type publicKey from a privateKey byte-array.
//
// Returns a 33-byte compressed-type publicKey array.
// If computation was not successful, an empty byte-array is returned.
//
// const uint8_t *privateKeyBytes
// - 32-byte privateKey byte array.
//
// ---
auto Curve::PublicKey::compute(const uint8_t *privateKeyBytes) -> PublicKeyBytes {
    const struct uECC_Curve_t *curve = uECC_secp256k1();

    PublicKeyPoint uncompressed {};
    if (uECC_compute_public_key(privateKeyBytes, &uncompressed[0], curve) == 0) {
        return {};
    };

    return compress(uncompressed.data());
}

////////////////////////////////////////////////////////////////////////////////
// Curve::PublicKey::compress
//
// Compresses an uncompressed publicKey curvepoint.
//
// Returns a 33-byte compressed-type publicKey array.
//
// const uint8_t *uncompressed
// - 64-byte uncompressed-type publicKey byte array of (x,y) elements
//
// ---
auto Curve::PublicKey::compress(const uint8_t *uncompressed) -> PublicKeyBytes {
    const struct uECC_Curve_t* curve = uECC_secp256k1();
    PublicKeyBytes compressed {};
    uECC_compress(uncompressed, compressed.data(), curve);

    return compressed;
}

////////////////////////////////////////////////////////////////////////////////
// Curve::PublicKey::decompress
//
// Decompresses a compressed publicKey.
// solves: y^3 = x^2 * ax + b
//
// Returns a 64-byte uncompressed-type publicKey array of (x,y) elements.
//
// const uint8_t *compressed
// - 33-byte compressed-type publicKey byte array.
//
// ---
auto Curve::PublicKey::decompress(const uint8_t *compressed) -> PublicKeyPoint {
    const struct uECC_Curve_t* curve = uECC_secp256k1();
    PublicKeyPoint decompressed {};
    uECC_decompress(compressed, decompressed.data(), curve);

    return decompressed;
}

////////////////////////////////////////////////////////////////////////////////
// Curve::PublicKey::validate
//
// Validate a compressed publicKey.
//
// Returns true if the 33-byte publicKey array was successfully validated.
//
// const uint8_t *publicKeyBytes
// - 33-byte compressed-type publicKey byte array.
//
// ---
auto Curve::PublicKey::validate(const uint8_t *publicKeyBytes) -> bool {
    const struct uECC_Curve_t* curve = uECC_secp256k1();
    return uECC_valid_public_key(decompress(publicKeyBytes).data(), curve) != 0;
}

}  // namespace Crypto
}  // namespace Ark
