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

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_curve, ecdsa_sign_null_hash) {
    std::vector<uint8_t> signature = {};
    Curve::Ecdsa::sign(nullptr, fixtures::PrivateKeyBytes.data(), &signature);

    ASSERT_FALSE(Curve::Ecdsa::verify(fixtures::MessageSha256Bytes.data(),
                                      fixtures::PublicKeyBytes.data(),
                                      signature));
}
