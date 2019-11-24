/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "crypto/hash.hpp"

#include "fixtures/identity.hpp"
#include "fixtures/message.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace fixtures::identity;
using namespace fixtures::message;

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_hash_ripemd, hash_160) {
    auto ripeHash = Hash::ripemd160(tPublicKeyBytes.data());
    ASSERT_TRUE(array_cmp(tAddressBytes.data(), ripeHash.data(), HASH_20_LEN));
}

////////////////////////////////////////////////////////////////////////////////
TEST(crypto_hash_sha256, hash_256) {
    auto shaHash = Hash::sha256(tMessageBytes.data(), tMessageBytes.size());

    ASSERT_TRUE(array_cmp(tMessageSha256Bytes.data(),
                          shaHash.data(),
                          HASH_32_LEN));
}
