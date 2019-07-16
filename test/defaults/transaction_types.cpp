
#include "gtest/gtest.h"

#include <arkCrypto.h>

namespace {
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

/**/

TEST(defaults, transaction_types) {  // NOLINT
  ASSERT_EQ(kTransferType,                    defaults::TransactionTypes::Transfer);
  ASSERT_EQ(kSecondSignatureRegistrationType, defaults::TransactionTypes::SecondSignatureRegistration);
  ASSERT_EQ(kDelegateRegistrationType,        defaults::TransactionTypes::DelegateRegistration);
  ASSERT_EQ(kVoteType,                        defaults::TransactionTypes::Vote);
  ASSERT_EQ(kMultiSignatureRegistrationType,  defaults::TransactionTypes::MultiSignatureRegistration);
  ASSERT_EQ(kIpfsType,                        defaults::TransactionTypes::Ipfs);
  ASSERT_EQ(kTimelockTransferType,            defaults::TransactionTypes::TimelockTransfer);
  ASSERT_EQ(kMultiPaymentType,                defaults::TransactionTypes::MultiPayment);
  ASSERT_EQ(kDelegateResignationType,         defaults::TransactionTypes::DelegateResignation);
}
