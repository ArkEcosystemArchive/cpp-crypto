
#include "gtest/gtest.h"

#include "enums/types.h"

TEST(enums, types) {
  ASSERT_EQ(0U, Ark::Crypto::Enums::Types::TRANSFER);
  ASSERT_EQ(1U, Ark::Crypto::Enums::Types::SECOND_SIGNATURE_REGISTRATION);
  ASSERT_EQ(2U, Ark::Crypto::Enums::Types::DELEGATE_REGISTRATION);
  ASSERT_EQ(3U, Ark::Crypto::Enums::Types::VOTE);
  ASSERT_EQ(4U, Ark::Crypto::Enums::Types::MULTI_SIGNATURE_REGISTRATION);
  ASSERT_EQ(5U, Ark::Crypto::Enums::Types::IPFS);
  ASSERT_EQ(6U, Ark::Crypto::Enums::Types::TIMELOCK_TRANSFER);
  ASSERT_EQ(7U, Ark::Crypto::Enums::Types::MULTI_PAYMENT);
  ASSERT_EQ(8U, Ark::Crypto::Enums::Types::DELEGATE_RESIGNATION);
}
