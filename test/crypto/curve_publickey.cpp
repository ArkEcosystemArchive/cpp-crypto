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

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_compute) {
    const auto publicKey = Curve::PublicKey::compute(fixtures::PrivateKeyBytes.data());

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_compute_invalid) {
    const auto publicKey = Curve::PublicKey::compute(
            fixtures::invalid::PrivateKeyBytes.data());

    for (auto &e : publicKey) {
        ASSERT_EQ(0U, e);
    }
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_compress) {
    const auto compressed = Curve::PublicKey::compress(
                fixtures::PublicKeyUncompressedBytes.data());

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyBytes.data(),
                          compressed.data(),
                          compressed.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_decompress) {
    const auto decompressed = Curve::PublicKey::decompress(
                fixtures::PublicKeyBytes.data());

    ASSERT_TRUE(array_cmp(fixtures::PublicKeyUncompressedBytes.data(),
                          decompressed.data(),
                          decompressed.size()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_validate) {
    ASSERT_TRUE(Curve::PublicKey::validate(fixtures::PublicKeyBytes.data()));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, publickey_validate_invalid) {
    ASSERT_FALSE(Curve::PublicKey::validate(
            fixtures::invalid::PublicKeyBytes.data()));
}
