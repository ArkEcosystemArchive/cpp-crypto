/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/wif.hpp"

#include <string>

#include "interfaces/identities.hpp"

#include "identities/keys.hpp"

#include "utils/base58.hpp"

namespace Ark {
namespace Crypto {
namespace identities {

////////////////////////////////////////////////////////////////////////////////
// Constructs a Wif object using a PrivateKey and Wif Version-byte.
Wif::Wif(const PrivateKeyBytes &privateKeyBytes, const uint8_t &version)
        : privateKeyBytes_(privateKeyBytes), version_(version) {}

////////////////////////////////////////////////////////////////////////////////
// Constructs a Wif object from a 52(+ 1)-char string and Wif Version-byte.
Wif::Wif(const char *wif) : privateKeyBytes_(), version_() {
    if (Base58::validate(wif, WIF_STRING_LEN)) {
        this->privateKeyBytes_ = Keys::PrivateKey::fromWif(wif, &this->version_);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Returns the Wif Network Version-byte.
auto Wif::version() const noexcept -> uint8_t { return this->version_; };

////////////////////////////////////////////////////////////////////////////////
// Returns the Wif's internal privateKey 
auto Wif::toBytes() const noexcept -> PrivateKeyBytes {
    return this->privateKeyBytes_;
}

////////////////////////////////////////////////////////////////////////////////
// Returns the 52(+ 1)-char Base58-encoded Wif string.
auto Wif::toString() const -> std::string {
    return Base58::getWif(this->privateKeyBytes_.data(), this->version_);
}

////////////////////////////////////////////////////////////////////////////////
// Returns a Wif object from a Passphrase and Wif Version-byte.
auto Wif::fromPassphrase(const char *passphrase, const uint8_t &version) -> Wif {
    return { Keys::PrivateKey::fromPassphrase(passphrase), version };
}

}  // namespace identities
}  // namespace Crypto
}  // namespace Ark
