#include "gtest/gtest.h"

#include "arkCrypto.h"

TEST(enums, fees)
{
    Ark::Crypto::Enums::Fees fees;
    
    auto feeZERO = fees.TRANSFER;
    ASSERT_TRUE(10000000 == feeZERO);

    auto feeONE = fees.SECOND_SIGNATURE_REGISTRATION;
    ASSERT_TRUE(500000000 == feeONE);

    auto feeTWO = fees.DELEGATE_REGISTRATION;
    ASSERT_TRUE(2500000000 == feeTWO);

    auto feeTHREE = fees.VOTE;
    ASSERT_TRUE(100000000 == feeTHREE);

    auto feeFOUR = fees.MULTI_SIGNATURE_REGISTRATION;
    ASSERT_TRUE(500000000 == feeFOUR);

    auto feeFIVE = fees.IPFS;
    ASSERT_TRUE(0 == feeFIVE);

    auto feeSIX = fees.TIMELOCK_TRANSFER;
    ASSERT_TRUE(0 == feeSIX);

    auto feeSEVEN = fees.MULTI_PAYMENT;
    ASSERT_TRUE(0 == feeSEVEN);

    auto feeEIGHT = fees.DELEGATE_RESIGNATION;
    ASSERT_TRUE(0 == feeEIGHT);
}
