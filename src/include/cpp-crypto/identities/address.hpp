/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_IDENTITIES_ADDRESS_HPP
#define ARK_IDENTITIES_ADDRESS_HPP

#include <cstdbool>
#include <string>

#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

////////////////////////////////////////////////////////////////////////////////
class Address {
  public:
    ////////////////////////////////////////////////////////////////////////////
    Address(const PubkeyHash &pubkeyHash, uint8_t version);
    explicit Address(const char *addressString);

    ////////////////////////////////////////////////////////////////////////////
    uint8_t version() const noexcept;

    ////////////////////////////////////////////////////////////////////////////
    PubkeyHash toBytes() const noexcept;
    std::string toString() const;

    ////////////////////////////////////////////////////////////////////////////
    static Address fromPassphrase(const char *passphrase,
                                  uint8_t version);

    static Address fromPublicKey(const uint8_t *publicKeyBytes,
                                 uint8_t version);

    static Address fromPrivateKey(const uint8_t *privateKeyBytes,
                                  uint8_t version);

    ////////////////////////////////////////////////////////////////////////////
    static bool validate(const Address& address, uint8_t version);

  private:
    ////////////////////////////////////////////////////////////////////////////
    PubkeyHash pubkeyHash_;
    uint8_t version_;
};

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark

#endif
