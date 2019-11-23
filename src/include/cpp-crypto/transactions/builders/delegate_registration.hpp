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

#include <cstdint>
#include <cstring>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////

class DelegateRegistration;

////////////////////////////////////////////////////////////////////////////////

class DelegateRegistration : public Common<DelegateRegistration> {
  public:

////////////////////////////////////////////////////////////////////////////////

    // Username - uint8_t[] 3 <=> 20 Bytes
    DelegateRegistration &username(const uint8_t *username,
                                   const size_t length) {
        this->transaction.data.asset.delegateRegistration.length = length;
        memmove(this->transaction.data.asset.delegateRegistration.username.data(),
                username,
                length);

        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

    // Username - std::string
    DelegateRegistration &username(const std::string &username) {
        this->transaction.data.asset.delegateRegistration.length = username.length();
        memmove(this->transaction.data.asset.delegateRegistration.username.data(),
                username.data(),
                username.length());

        return *this;
    }

////////////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
