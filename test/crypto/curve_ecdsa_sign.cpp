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
TEST(crypto_curve, ecdsa_sign) {
    std::vector<uint8_t> signature = {};
    ASSERT_TRUE(Curve::Ecdsa::sign(fixtures::MessageSha256Bytes.data(),
                                   fixtures::PrivateKeyBytes.data(),
                                   &signature));

    ASSERT_TRUE(array_cmp(fixtures::MessageSignatureBytes.data(),
                          signature.data(),
                          signature.size()));
}
