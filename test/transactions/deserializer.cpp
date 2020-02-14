/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/deserializer.hpp"
#include "transactions/transaction_data.hpp"

#include "transactions/defaults/offsets.hpp"

#include "types/fixtures/transfer.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
// Break deserialization with an invalid version.
// All other cases are tested via transaction types.
TEST(transactions_deserializer, deserialize_invalid_version) {
    TransactionData data;

    // break serialization by changing the Tx version to 0.
    // the API only accepts v1 or v2.
    auto invalidBytes = TYPE_0_BYTES;
    invalidBytes.at(1) = 0U;

    ASSERT_FALSE(Deserializer::deserialize(&data, invalidBytes));

}

////////////////////////////////////////////////////////////////////////////////
// Deserialize with an unknown type.
// For compatiblity with future Tx types, this should not fail.
// All other cases are tested via transaction types.
TEST(transactions_deserializer, deserialize_unknown_type_no_fail) {
    TransactionData data;

    auto unknownTypeBytes = TYPE_0_BYTES;
    const auto unknowntype = 100U;
    unknownTypeBytes.at(TYPE_OFFSET) = unknowntype;

    ASSERT_TRUE(Deserializer::deserialize(&data, unknownTypeBytes));
}
