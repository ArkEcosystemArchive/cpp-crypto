/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "crypto/curve.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_compute) {
    const auto publicKey = Curve::PublicKey::compute(tPrivateKeyBytes.data());

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_compute_invalid) {
    const auto publicKey = Curve::PublicKey::compute(
            invalid::tPrivateKeyBytes.data());

    for (auto &e : publicKey) {
        ASSERT_EQ(0U, e);
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_compress) {
    const auto compressed = Curve::PublicKey::compress(
                tUncompressedPublicKeyBytes.data());

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          compressed.data(),
                          compressed.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_decompress) {
    const auto decompressed = Curve::PublicKey::decompress(
                tPublicKeyBytes.data());

    ASSERT_TRUE(array_cmp(tUncompressedPublicKeyBytes.data(),
                          decompressed.data(),
                          decompressed.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_validate) {
    ASSERT_TRUE(Curve::PublicKey::validate(tPublicKeyBytes.data()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, publickey_validate_invalid) {
    ASSERT_FALSE(Curve::PublicKey::validate(invalid::tPublicKeyBytes.data()));
}

////////////////////////////////////////////////////////////////////////////////
