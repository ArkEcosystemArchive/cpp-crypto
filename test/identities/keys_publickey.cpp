/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/keys.hpp"
#include "interfaces/identities.hpp"

#include "fixtures/identity.hpp"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace Ark::Crypto::fixtures::identity;

////////////////////////////////////////////////////////////////////////////////

TEST(identities_keys, publickey_from_privatekey) {
    auto publicKey = Keys::PublicKey::fromPrivateKey(tPrivateKeyBytes.data());

    ASSERT_TRUE(array_cmp(tPublicKeyBytes.data(),
                          publicKey.data(),
                          PUBLICKEY_COMPRESSED_LEN));
}

////////////////////////////////////////////////////////////////////////////////
