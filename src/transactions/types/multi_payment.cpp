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
#include "utils/json.h"
#include "utils/packing.h"
#include "utils/str.hpp"

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
        -> size_t {
    payments->n_payments = unpack2LE(buffer, 0U);               // 2 Bytes

    if (buffer[0] == 0U || payments->n_payments > MULTI_PAYMENT_NETWORK_LIMIT) {
        payments->n_payments = 0UL;
        return 0UL;
    }

    payments->amounts.resize(payments->n_payments);
    payments->addresses.resize(payments->n_payments);

    size_t pos = sizeof(uint16_t);

    for (size_t i = 0UL; i < payments->n_payments; ++i) {
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
// - pack2LE(&buffer.at(offset), &payments.n_payments);
//
// Amounts[] - 8 Bytes * n_payments
// - pack8LE(&buffer.at(pos), &payments.amounts.at(i));
//
// Addresses - n_payments * vector<array[21]> Bytes
// - std::move(payments.addresses.at(i).begin(), payments.addresses.at(i).end(), &buffer[pos]);
//
// ---
auto MultiPayment::Serialize(const MultiPayment &payments,
                             std::vector<uint8_t> &buffer,
                             const size_t offset) -> size_t {
    if (!checkBuffer(payments, buffer, offset)) {
        return 0UL;
    }

    pack2LE(&buffer.at(offset), &payments.n_payments);          // 2 Bytes

    size_t pos = offset + sizeof(uint16_t);

    for (size_t i = 0U; i < payments.n_payments; ++i) {
        pack8LE(&buffer.at(pos), &payments.amounts.at(i));      // 8 Bytes

        pos += sizeof(uint64_t);

        std::move(payments.addresses.at(i).begin(),             // 21 Bytes
                  payments.addresses.at(i).end(),
                  &buffer[pos]);

        pos += ADDRESS_HASH_LEN;
    }

    return pos - offset;                                    // 2 + 29N Bytes
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Map/Json Constants
const auto KEY_PAYMENTS_LABEL   = "payments";
const auto KEY_PAYMENTS_SIZE    = strlen(KEY_PAYMENTS_LABEL);

const auto KEY_N_PAYMENTS_SIZE    = strlen(KEY_N_PAYMENTS_LABEL);

const auto KEY_AMOUNTS_LABEL   = "amounts";
const auto KEY_AMOUNTS_SIZE    = strlen(KEY_AMOUNTS_LABEL);

const auto KEY_ADDRESSES_LABEL   = "addresses";
const auto KEY_ADDRESSES_SIZE    = strlen(KEY_ADDRESSES_LABEL);

const auto KEY_AMOUNT_LABEL   = "amount";
const auto KEY_AMOUNT_SIZE    = strlen(KEY_AMOUNT_LABEL);

const auto KEY_RECIPIENT_ID_LABEL   = "recipientId";
const auto KEY_RECIPIENT_ID_SIZE    = strlen(KEY_RECIPIENT_ID_LABEL);

const auto MULTIPAYMENT_JSON_OBJECT_SIZE = 2U;

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
// Add MultiPayment Asset data to a Transaction Map.
// Key strings are comma-separated.
void MultiPayment::addToMap(const MultiPayment &payments,
                            std::map<std::string, std::string> &map) {
    // Number of Payments
    map.emplace(KEY_N_PAYMENTS_LABEL, UintToString(payments.n_payments));

    // Amounts
    map.emplace(KEY_AMOUNTS_LABEL,
                JoinWithOp<uint64_t>(payments.amounts, UintToString));

    // Addresses
    map.emplace(KEY_ADDRESSES_LABEL,
                JoinWithOp<AddressHash>(payments.addresses,
                                        Base58::parseAddressHash));
}

////////////////////////////////////////////////////////////////////////////////
// Return the Json Capacity of a MultiPayment-type Transaction.
auto MultiPayment::getJsonCapacity(const size_t n_payments) -> size_t {
    return JSON_OBJECT_SIZE(1) + KEY_ASSET_SIZE +
           JSON_OBJECT_SIZE(1) + KEY_PAYMENTS_SIZE +
           JSON_ARRAY_SIZE(n_payments) +
                (n_payments * JSON_OBJECT_SIZE(MULTIPAYMENT_JSON_OBJECT_SIZE)) +
                (n_payments * (KEY_AMOUNTS_SIZE      + UINT64_MAX_CHARS +
                               KEY_RECIPIENT_ID_SIZE + ADDRESS_STR_LEN));
}

////////////////////////////////////////////////////////////////////////////////
// Add MultiPayment data to a `DynamicJsonDocument` using a std::map.
//
// The std::map must already contain MultiPayment data.
//
// ---
void MultiPayment::addToJson(DynamicJsonDocument &jsonDoc,
                             const std::map<std::string, std::string> &map) {
    JsonObject asset = jsonDoc.createNestedObject(KEY_ASSET_LABEL);
    JsonArray payments = asset.createNestedArray(KEY_PAYMENTS_LABEL);

    const auto paymentsStr = map.at(KEY_AMOUNTS_LABEL);
    const auto addressesStr = map.at(KEY_ADDRESSES_LABEL);
    const auto n_payments = strtol(map.at(KEY_N_PAYMENTS_LABEL).c_str(),
                                    nullptr,
                                    BASE_10);

    for (uint8_t i = 0U; i < n_payments; ++i) {
        JsonObject payment_n = payments.createNestedObject();

        // Amount(N)
        payment_n[KEY_AMOUNT_LABEL] = paymentsStr
                .substr(0, paymentsStr.find(',', 0));

        // RecipientId(N)
        payment_n[KEY_RECIPIENT_ID_LABEL] = addressesStr
            .substr(i + (i * ADDRESS_STR_LEN), ADDRESS_STR_LEN);
    }
}

}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark
