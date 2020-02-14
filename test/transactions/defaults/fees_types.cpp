/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "transactions/defaults/fees.hpp"
#include "transactions/defaults/types.hpp"

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
TEST(transactions_defaults, fees_and_types) {  // NOLINT
  const auto feePolicy = StaticFeePolicy;

    ASSERT_EQ(TRANSFER_FEE,                 feePolicy.at(TRANSFER_TYPE));
    ASSERT_EQ(SECOND_SIGNATURE_FEE,         feePolicy.at(SECOND_SIGNATURE_TYPE));
    ASSERT_EQ(DELEGATE_REGISTRATION_FEE,    feePolicy.at(DELEGATE_REGISTRATION_TYPE));
    ASSERT_EQ(VOTE_FEE,                     feePolicy.at(VOTE_TYPE));
    ASSERT_EQ(MULTI_SIGNATURE_FEE,          feePolicy.at(MULTI_SIGNATURE_TYPE));
    ASSERT_EQ(IPFS_FEE,                     feePolicy.at(IPFS_TYPE));
    ASSERT_EQ(MULTI_PAYMENT_FEE,            feePolicy.at(MULTI_PAYMENT_TYPE));
    ASSERT_EQ(DELEGATE_RESIGNATION_FEE,     feePolicy.at(DELEGATE_RESIGNATION_TYPE));
    ASSERT_EQ(HTLC_LOCK_FEE,                feePolicy.at(HTLC_LOCK_TYPE));
    ASSERT_EQ(HTLC_CLAIM_FEE,               feePolicy.at(HTLC_CLAIM_TYPE));
    ASSERT_EQ(HTLC_REFUND_FEE,              feePolicy.at(HTLC_REFUND_TYPE));
}
