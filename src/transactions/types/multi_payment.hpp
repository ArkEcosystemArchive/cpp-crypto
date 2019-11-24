/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_MULTI_PAYMENT_HPP
#define ARK_TRANSACTIONS_TYPES_MULTI_PAYMENT_HPP

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

namespace Ark {
namespace Crypto {
namespace transactions {

const uint16_t MULTI_PAYMENT_NETWORK_LIMIT = 100UL;

////////////////////////////////////////////////////////////////////////////////
// Type 6 - MultiPayment
//
// MultiPayment Transaction-types can get fairly large.
//
// Typically, we avoid using dynamic allocation as much as possible.
//
// In this case, we're using vectors.
// Otherwise, we'd need to allocate upwards of ~65K on the stack..
//
// Extra precaution should always be used when dealing with large Txs.
// Particularly in embedded environments.
//
// ---
struct MultiPayment {
    ////////////////////////////////////////////////////////////////////////////
    // Network Limit: 100
    uint16_t n_payments;

    ////////////////////////////////////////////////////////////////////////////
    // n_payments * vector<uint64_t>
    std::vector<uint64_t> amounts;

    ////////////////////////////////////////////////////////////////////////////
    // n_payments * vector<array[21]> Bytes
    // std::vector<std::array<uint8_t, ADDRESS_HASH_LEN> > addresses;
    std::vector<AddressHash> addresses;

    ////////////////////////////////////////////////////////////////////////////
    static uint32_t Deserialize(MultiPayment *payments, const uint8_t *buffer);

    ////////////////////////////////////////////////////////////////////////////
    static uint32_t Serialize(const MultiPayment &payments,
                              std::vector<uint8_t> &buffer,
                              const size_t offset);

    ////////////////////////////////////////////////////////////////////////////
    static std::map<std::string, std::string> getMap(
            const MultiPayment &payments);

    ////////////////////////////////////////////////////////////////////////////
    MultiPayment() : n_payments(0U), amounts({ 0ULL }), addresses() {}
};

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
