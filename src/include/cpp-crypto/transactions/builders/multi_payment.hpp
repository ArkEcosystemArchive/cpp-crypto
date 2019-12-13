/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_MULTI_PAYMENT_HPP
#define ARK_TRANSACTIONS_BUILDERS_MULTI_PAYMENT_HPP

#include <cstdint>
#include <vector>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class MultiPayment;

////////////////////////////////////////////////////////////////////////////////
class MultiPayment : public Common<MultiPayment> {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Number of Payments
    //
    // - Should correspond to the 'Amounts' and 'Addresses' builder inputs counts.
    //
    // ---
    MultiPayment &n_payments(uint16_t n_payments) {
        this->transaction.data.asset.multiPayment.n_payments = n_payments;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Amounts
    //
    // - Must be a std::vector<uint64_t> -type.
    // - Count of amounts should match the 'n_payments' builder input.
    // - Must be ordered to match the corresponding 'Addresses' builder input.
    //
    // ---
    MultiPayment &amounts(const std::vector<uint64_t> &amounts) {
        this->transaction.data.asset.multiPayment.amounts = amounts;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Addresses
    //
    // - Must be a std::vector<AddressHash> -type.
    // - Count of amounts should match the 'n_payments' builder input.
    // - Must be ordered to match the corresponding 'Amounts' builder input.
    //
    // ---
    MultiPayment &addresses(const std::vector<AddressHash> &addresses) {
        this->transaction.data.asset.multiPayment.addresses = addresses;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    MultiPayment() {
        this->transaction.data.type = MULTI_PAYMENT_TYPE;
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
