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
TEST(crypto_message, to_map) {
    Message message;
    message.sign(fixtures::MessageString, fixtures::Passphrase);
    auto map = message.toMap();

    ASSERT_STREQ(fixtures::MessageString,           map["message"].c_str());
    ASSERT_STREQ(fixtures::PublicKeyHex,            map["publickey"].c_str());
    ASSERT_STREQ(fixtures::MessageSignatureString,  map["signature"].c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_message, to_json) {
    Message message;
    message.sign(fixtures::MessageString, fixtures::Passphrase);

    ASSERT_STREQ(fixtures::MessageJsonString, message.toJson().c_str());
}
