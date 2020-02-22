/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_DELEGATE_RESIGNATION_HPP
#define ARK_TRANSACTIONS_BUILDERS_DELEGATE_RESIGNATION_HPP

#include "transactions/builders/common.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class DelegateResignation;

////////////////////////////////////////////////////////////////////////////////
class DelegateResignation : public Common<DelegateResignation> {
  public:
    DelegateResignation() {
        this->transaction.data.type = DELEGATE_RESIGNATION_TYPE;
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
