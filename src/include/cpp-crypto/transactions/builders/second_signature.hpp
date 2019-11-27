/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_SECOND_SIGNATURE_HPP
#define ARK_TRANSACTIONS_BUILDERS_SECOND_SIGNATURE_HPP

#include <cstdint>
#include <utility>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class SecondSignature;

////////////////////////////////////////////////////////////////////////////////
class SecondSignature : public Common<SecondSignature> {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Second Signature PublicKey
    SecondSignature &publicKey(const uint8_t *secondPublicKey) {
        std::move(
            secondPublicKey,
            secondPublicKey + PUBLICKEY_COMPRESSED_LEN,
            this->transaction.data.asset.secondSignature.publicKey.begin());

        return *this;
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif