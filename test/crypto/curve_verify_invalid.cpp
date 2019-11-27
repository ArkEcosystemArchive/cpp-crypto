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
TEST(crypto_curve, verify_invalid) {
    std::vector<uint8_t> temp = {
        fixtures::MessageSignatureBytes.begin(),
        fixtures::MessageSignatureBytes.end()
    };

    // Invalid PublicKey
    ASSERT_FALSE(Curve::Ecdsa::verify(fixtures::MessageSha256Bytes.data(),
                                      fixtures::invalid::PublicKeyBytes.data(),
                                      temp));

    // Null Hash
    ASSERT_FALSE(Curve::Ecdsa::verify(nullptr,
                                      fixtures::invalid::PublicKeyBytes.data(),
                                      temp));
}
