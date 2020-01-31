/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "types/fixtures/transfer_v1.hpp"

#include "transactions/transaction.hpp"

#include "test_helpers.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_transaction, v1_vendorField) {  // NOLINT

    Transaction transaction;
    transaction.deserialize(v1::TYPE_0_BYTES_VF);

    ASSERT_STREQ(R"({"version":1,"network":23,"type":0,"timestamp":"83506245","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"10000000","vendorField":"Hello World","amount":"1","expiration":0,"recipientId":"AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff","id":"b410f29636882f747608f784be2adf181f30db08a93341df57e9415cfd5b023a","signature":"304402204209261f274cb4d71b0504a3827d9670ac8cca1cb4aab6b3fc55b0b63a9f03e502205cbb25435d7279e536958cf8fa588c86ebe2a00571073a96a79084906ee0d509"})",
                 transaction.toJson().c_str());
}
