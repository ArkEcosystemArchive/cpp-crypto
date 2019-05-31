
#include "gtest/gtest.h"

#include "enums/fees.h"

TEST(enums, fees) {
  auto feeZERO = Ark::Crypto::Enums::Fees::TRANSFER;
  ASSERT_EQ(10000000ULL, feeZERO);

  auto feeONE = Ark::Crypto::Enums::Fees::SECOND_SIGNATURE_REGISTRATION;
  ASSERT_EQ(500000000ULL, feeONE);

  auto feeTWO = Ark::Crypto::Enums::Fees::DELEGATE_REGISTRATION;
  ASSERT_EQ(2500000000ULL, feeTWO);

  auto feeTHREE = Ark::Crypto::Enums::Fees::VOTE;
  ASSERT_EQ(100000000ULL, feeTHREE);

  auto feeFOUR = Ark::Crypto::Enums::Fees::MULTI_SIGNATURE_REGISTRATION;
  ASSERT_EQ(500000000ULL, feeFOUR);

  auto feeFIVE = Ark::Crypto::Enums::Fees::IPFS;
  ASSERT_EQ(0ULL, feeFIVE);

  auto feeSIX = Ark::Crypto::Enums::Fees::TIMELOCK_TRANSFER;
  ASSERT_EQ(0ULL, feeSIX);

  auto feeSEVEN = Ark::Crypto::Enums::Fees::MULTI_PAYMENT;
  ASSERT_EQ(0ULL, feeSEVEN);

  auto feeEIGHT = Ark::Crypto::Enums::Fees::DELEGATE_RESIGNATION;
  ASSERT_EQ(0ULL, feeEIGHT);
}
