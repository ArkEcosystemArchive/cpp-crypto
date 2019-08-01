
#include "gtest/gtest.h"

#include <arkCrypto.h>

namespace {
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

/**/

TEST(defaults, transaction_types) {  // NOLINT
  ASSERT_EQ(TransferType,                    TransactionTypes::Transfer);
  ASSERT_EQ(SecondSignatureRegistrationType, TransactionTypes::SecondSignatureRegistration);
  ASSERT_EQ(DelegateRegistrationType,        TransactionTypes::DelegateRegistration);
  ASSERT_EQ(VoteType,                        TransactionTypes::Vote);
  ASSERT_EQ(MultiSignatureRegistrationType,  TransactionTypes::MultiSignatureRegistration);
  ASSERT_EQ(IpfsType,                        TransactionTypes::Ipfs);
  ASSERT_EQ(TimelockTransferType,            TransactionTypes::TimelockTransfer);
  ASSERT_EQ(MultiPaymentType,                TransactionTypes::MultiPayment);
  ASSERT_EQ(DelegateResignationType,         TransactionTypes::DelegateResignation);
}
