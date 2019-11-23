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

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

////////////////////////////////////////////////////////////////////////////////

TEST(crypto_curve, verify_invalid) {
    std::vector<uint8_t> temp = {
        tMessageSignatureBytes.begin(),
        tMessageSignatureBytes.end()
    };

    ASSERT_FALSE(Curve::Ecdsa::verify(tMessageSha256Bytes.data(),
                                      invalid::tPublicKeyBytes.data(),
                                      temp));
}

////////////////////////////////////////////////////////////////////////////////
