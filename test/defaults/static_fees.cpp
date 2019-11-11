
#include "gtest/gtest.h"

#include <cstdint>

#include "defaults/static_fees.hpp"
using namespace Ark::Crypto;

namespace {
constexpr const uint64_t kTransfer                    = 10000000ULL;
constexpr const uint64_t kSecondSignatureRegistration = 500000000ULL;
constexpr const uint64_t kDelegateRegistration        = 2500000000ULL;
constexpr const uint64_t kVote                        = 100000000ULL;
constexpr const uint64_t kMultiSignatureRegistration  = 500000000ULL;
constexpr const uint64_t kIpfs                        = 0ULL;
constexpr const uint64_t kTimelockTransfer            = 0ULL;
constexpr const uint64_t kMultiPayment                = 0ULL;
constexpr const uint64_t kDelegateResignation         = 2500000000ULL;
constexpr const uint8_t TransferType                    = 0;
constexpr const uint8_t SecondSignatureRegistrationType = 1;
constexpr const uint8_t DelegateRegistrationType        = 2;
constexpr const uint8_t VoteType                        = 3;
constexpr const uint8_t MultiSignatureRegistrationType  = 4;
constexpr const uint8_t IpfsType                        = 5;
constexpr const uint8_t TimelockTransferType            = 6;
constexpr const uint8_t MultiPaymentType                = 7;
constexpr const uint8_t DelegateResignationType         = 8;
}  //namespace

TEST(defaults, fees_static) {  // NOLINT
  const auto feePolicy = StaticFeePolicy;
  ASSERT_EQ(kTransfer,                    feePolicy.at(TransferType));
  ASSERT_EQ(kSecondSignatureRegistration, feePolicy.at(SecondSignatureRegistrationType));
  ASSERT_EQ(kDelegateRegistration,        feePolicy.at(DelegateRegistrationType));
  ASSERT_EQ(kVote,                        feePolicy.at(VoteType));
  ASSERT_EQ(kMultiSignatureRegistration,  feePolicy.at(MultiSignatureRegistrationType));
  ASSERT_EQ(kIpfs,                        feePolicy.at(IpfsType));
  ASSERT_EQ(kTimelockTransfer,            feePolicy.at(TimelockTransferType));
  ASSERT_EQ(kMultiPayment,                feePolicy.at(MultiPaymentType));
  ASSERT_EQ(kDelegateResignation,         feePolicy.at(DelegateResignationType));
}
