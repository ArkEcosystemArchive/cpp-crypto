/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "bcl/Sha256Hash.hpp"
#include "identities/privatekey.hpp"
#include "identities/publickey.hpp"

#include <cstdint>
#include <vector>

#ifndef CRYPTO_H
#define CRYPTO_H

void cryptoSign(
    const Sha256Hash& hash,
    const Ark::Crypto::identities::PrivateKey& privateKey,
    std::vector<uint8_t>& signature);

/**/

bool cryptoVerify(
    const Ark::Crypto::identities::PublicKey& publicKey,
    const Sha256Hash& hash,
    const std::vector<uint8_t>& signature);

#endif
