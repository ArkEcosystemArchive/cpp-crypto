#include "gtest/gtest.h"

#include "enums/types.h"

TEST(enums, types) {
  ASSERT_EQ(0, Ark::Crypto::Enums::Types::TRANSFER);
  ASSERT_EQ(1, Ark::Crypto::Enums::Types::SECOND_SIGNATURE_REGISTRATION);
  ASSERT_EQ(2, Ark::Crypto::Enums::Types::DELEGATE_REGISTRATION);
  ASSERT_EQ(3, Ark::Crypto::Enums::Types::VOTE);
  ASSERT_EQ(4, Ark::Crypto::Enums::Types::MULTI_SIGNATURE_REGISTRATION);
  ASSERT_EQ(5, Ark::Crypto::Enums::Types::IPFS);
  ASSERT_EQ(6, Ark::Crypto::Enums::Types::TIMELOCK_TRANSFER);
  ASSERT_EQ(7, Ark::Crypto::Enums::Types::MULTI_PAYMENT);
  ASSERT_EQ(8, Ark::Crypto::Enums::Types::DELEGATE_RESIGNATION);
}
