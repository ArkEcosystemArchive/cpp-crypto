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
using namespace fixtures::identity;
using namespace fixtures::message;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_message, to_map) {
    Message message;
    message.sign(tMessageString, tPassphrase);
    auto map = message.toMap();

    ASSERT_STREQ(tMessageString,        map["message"].c_str());
    ASSERT_STREQ(tPublicKeyHex,         map["publickey"].c_str());
    ASSERT_STREQ(tSignatureString,      map["signature"].c_str());
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_message, to_json) {
    Message message;
    message.sign(tMessageString, tPassphrase);

    ASSERT_STREQ(tMessageJsonString, message.toJson().c_str());
}
