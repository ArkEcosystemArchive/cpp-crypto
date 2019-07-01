
#include "gtest/gtest.h"

#include <cstdint>

#include <arkCrypto.h>

namespace {
static const uint64_t kTransfer                    = 10000000ULL;
static const uint64_t kSecondSignatureRegistration = 500000000ULL;
static const uint64_t kDelegateRegistration        = 2500000000ULL;
static const uint64_t kVote                        = 100000000ULL;
static const uint64_t kMultiSignatureRegistration  = 500000000ULL;
static const uint64_t kIpfs                        = 0ULL;
static const uint64_t kTimelockTransfer            = 0ULL;
static const uint64_t kMultiPayment                = 0ULL;
static const uint64_t kDelegateResignation         = 2500000000ULL;
static const uint8_t kTransferType                    = 0;
static const uint8_t kSecondSignatureRegistrationType = 1;
static const uint8_t kDelegateRegistrationType        = 2;
static const uint8_t kVoteType                        = 3;
static const uint8_t kMultiSignatureRegistrationType  = 4;
static const uint8_t kIpfsType                        = 5;
static const uint8_t kTimelockTransferType            = 6;
static const uint8_t kMultiPaymentType                = 7;
static const uint8_t kDelegateResignationType         = 8;
}  //namespace

TEST(defaults, fees_static) {  // NOLINT
  const auto feePolicy = defaults::Fees::StaticFeePolicy();
  ASSERT_EQ(kTransfer,                    feePolicy[kTransferType]);
  ASSERT_EQ(kSecondSignatureRegistration, feePolicy[kSecondSignatureRegistrationType]);
  ASSERT_EQ(kDelegateRegistration,        feePolicy[kDelegateRegistrationType]);
  ASSERT_EQ(kVote,                        feePolicy[kVoteType]);
  ASSERT_EQ(kMultiSignatureRegistration,  feePolicy[kMultiSignatureRegistrationType]);
  ASSERT_EQ(kIpfs,                        feePolicy[kIpfsType]);
  ASSERT_EQ(kTimelockTransfer,            feePolicy[kTimelockTransferType]);
  ASSERT_EQ(kMultiPayment,                feePolicy[kMultiPaymentType]);
  ASSERT_EQ(kDelegateResignation,         feePolicy[kDelegateResignationType]);
}
