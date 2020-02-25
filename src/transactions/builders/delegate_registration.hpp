/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_DELEGATE_REGISTRATION_HPP
#define ARK_TRANSACTIONS_BUILDERS_DELEGATE_REGISTRATION_HPP

#include <algorithm>
#include <cstdint>
#include <string>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

#include "utils/str.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class DelegateRegistration;

////////////////////////////////////////////////////////////////////////////////
class DelegateRegistration : public Common<DelegateRegistration> {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Username - uint8_t[] 3 <=> 20 Bytes
    DelegateRegistration &username(const uint8_t *username,
                                   const size_t &length) {
        this->transaction.data.asset
                .delegateRegistration.length = static_cast<uint8_t>(length);

        std::copy_n(username, length, this->transaction.data.asset
                                            .delegateRegistration
                                            .username.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Username - std::string
    DelegateRegistration &username(const std::string &username) {
        this->transaction.data.asset
                .delegateRegistration.length =
                        static_cast<uint8_t>(username.length());

        std::copy_n(StringToBytes(username).begin(),
                    username.length(),
                    this->transaction.data.asset
                            .delegateRegistration
                            .username.begin());

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    DelegateRegistration(const Configuration &config = {}) {
        this->transaction.data.type = DELEGATE_REGISTRATION_TYPE;
        this->configure(config);
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
