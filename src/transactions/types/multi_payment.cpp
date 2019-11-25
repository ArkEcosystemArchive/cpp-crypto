/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "transactions/types/multi_payment.hpp"

#include <array>
#include <cstdint>
#include <cstring>
#include <map>
#include <numeric>  // std::accumulate
#include <string>
#include <utility>
#include <vector>

#include "interfaces/constants.h"
#include "interfaces/identities.hpp"

#include "identities/address.hpp"

#include "utils/base58.hpp"
#include "utils/hex.hpp"
#include "utils/str.hpp"
#include "utils/unpack.h"

namespace Ark {
namespace Crypto {
namespace transactions {

////////////////////////////////////////////////////////////////////////////////
// Deserialize MultiPayment (Type 6) - 2 + 29N Bytes
//
// @param MultiPayment  *multipayment
// @param const uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Number of Payments - 2 Bytes:
// - payments.n_payments = unpack2LE(buffer, 0U);
//
// Amounts - n_payments * 8 Bytes
// - payments.amounts.at(i)  = unpack8LE(buffer, offset);
//
// Addresses - n_payments * vector<array[21]> Bytes
// - std::move(&buffer[pos], &buffer[pos + 21], payments->addresses.at(i).begin());
//
// ---
auto MultiPayment::Deserialize(MultiPayment *payments, const uint8_t *buffer)
        -> uint32_t {
    payments->n_payments = unpack2LE(buffer, 0U);               // 2 Bytes

    if (payments->n_payments > MULTI_PAYMENT_NETWORK_LIMIT) {
        return 0UL;
    }

    payments->amounts.resize(payments->n_payments);
    payments->addresses.resize(payments->n_payments);

    uint32_t pos = sizeof(uint16_t);

    for (uint32_t i = 0UL; i < payments->n_payments; ++i) {
        payments->amounts.at(i)  = unpack8LE(buffer, pos);      // 8 Bytes

        pos += sizeof(uint64_t);

        std::move(&buffer[pos],                                 // 21 Bytes
                  &buffer[pos + ADDRESS_HASH_LEN],
                  payments->addresses.at(i).begin());

        pos += ADDRESS_HASH_LEN;
    }

    return pos;                                             // 2 + 29N Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Check the final size of the transaction.
//
// - Do nothing if the buffer size is okay:             return true.
// - Resize the buffer if it's too small:               return true.
// - Clear the buffer if the transaction is too large:  return false.
//
// ---
static inline auto checkBuffer(const MultiPayment &payments,
                               std::vector<uint8_t> &buffer,
                               const size_t offset) -> bool {
    const size_t assetSize =
        sizeof(uint16_t) +
        ((sizeof(uint64_t) + ADDRESS_HASH_LEN) * payments.n_payments);

    const size_t fullTxSize = offset + assetSize;

    if (fullTxSize > TX_MAX_SIZE ||
        payments.n_payments > MULTI_PAYMENT_NETWORK_LIMIT) {
        buffer.clear();
        return false;
    }

    if (fullTxSize > buffer.size()) {
        buffer.resize(fullTxSize);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Serialize MultiPayment (Type 6) - 2 + 29N Bytes
//
// Resizes the outgoing buffer as-needed.
//
// @param const MultiPayment &multipayment
// @param uint8_t *buffer: The serialized buffer at the Assets offset.
//
// @return Asset Length
//
// ---
// Internals:
//
// Number of Payments - 2 Bytes:
// - memmove(buffer, &payments.n_payments, sizeof(uint16_t));
//
// Amounts[] - 8 Bytes * n_payments
// - memmove(&buffer[offset], &payments.amounts.at(i), sizeof(uint64_t))
//
// Addresses - n_payments * vector<array[21]> Bytes
// - std::move(payments.addresses.at(i).begin(), payments.addresses.at(i).end(), &buffer[pos]);
//
// ---
auto MultiPayment::Serialize(const MultiPayment &payments,
                             std::vector<uint8_t> &buffer,
                             const size_t offset) -> uint32_t {
    if (!checkBuffer(payments, buffer, offset)) {
        return 0UL;
    }

    memmove(&buffer.at(offset),                                 // 2 Bytes
            &payments.n_payments,
            sizeof(uint16_t));

    uint32_t pos = offset + sizeof(uint16_t);

    for (uint8_t i = 0U; i < payments.n_payments; ++i) {
        memmove(&buffer[pos],                                   // 8 Bytes
                &payments.amounts.at(i),
                sizeof(uint64_t));

        pos += sizeof(uint64_t);

        std::move(payments.addresses.at(i).begin(),             // 21 Bytes
                  payments.addresses.at(i).end(),
                  &buffer[pos]);

        pos += ADDRESS_HASH_LEN;
    }

    return pos - offset;                                    // 2 + 29N Bytes
}

////////////////////////////////////////////////////////////////////////////////
// Join Array and Vectors of a given 'T' to a comma separated string.
//
// ex:
// - JoinWithOp<uint64_t>(vector(amounts), UintToStringOp));
//
// ---
template<class T, class InputType, typename Operation>
static inline auto JoinWithOp(const InputType &a, Operation op) -> std::string {
    const auto joinOp = [op](const std::string &a,
                             const T &b) -> std::string {
        return a + (a.empty() ? a : ",") + op(b);
    };
    return std::accumulate(a.begin(), a.end(), std::string(), joinOp);
}

////////////////////////////////////////////////////////////////////////////////
// Return a Map of the MultiPayment asset.
// Key strings are comma-separated.
auto MultiPayment::getMap(const MultiPayment &payments)
        -> std::map<std::string, std::string> {
    std::map<std::string, std::string> map;

    map.emplace("n_payments", UintToString(payments.n_payments));

    map.emplace("amounts",
                JoinWithOp<uint64_t>(payments.amounts, UintToString));

    map.emplace("addresses",
                JoinWithOp<AddressHash>(payments.addresses,
                                        Base58::parseAddressHash));

    return map;
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
