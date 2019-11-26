/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include <map>

#include "crypto/message.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"

#include "utils/hex.hpp"

using namespace Ark::Crypto;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_message, sign) {
    Message message;
    message.sign(fixtures::MessageString, fixtures::Passphrase);

    ASSERT_STREQ(fixtures::MessageSignatureString,
                 BytesToHex(message.signature.begin(),
                            message.signature.begin() +
                            2U + message.signature.at(1)).c_str());
}
