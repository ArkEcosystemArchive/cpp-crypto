/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "bcl/Sha256Hash.hpp"
#include "identities/privatekey.h"
#include "identities/publickey.h"

#include <cstdint>
#include <vector>

#ifndef CRYPTO_H
#define CRYPTO_H

void cryptoSign(Sha256Hash hash, Ark::Crypto::Identities::PrivateKey privateKey, std::vector<uint8_t>& signature);
bool cryptoVerify(Ark::Crypto::Identities::PublicKey publicKey, Sha256Hash hash, std::vector<uint8_t>& signature);

#endif
