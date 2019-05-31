
#include "gtest/gtest.h"

#include "identities/wif.h"
using namespace Ark::Crypto::Identities;

namespace { // NOLINT
  // ARK Core test fixtures:
  // https://github.com/ARKEcosystem/core/blob/develop/__tests__/unit/crypto/identities/fixture.json
  const auto Passphrase = "this is a top secret passphrase";
  const uint8_t TestWIFBytes[52] = {
    83,  71, 113,  52, 120,  76, 103,  90,  75,  67,  71, 120, 115,
    55,  98, 106, 109, 119, 110,  66, 114,  87,  99,  84,  52,  67,
    49,  65,  68,  70,  69, 101, 114, 109, 106,  56,  52,  54,  75,
    67,  57,  55,  70,  83, 118,  49,  87,  70,  68,  49, 100,  65
  };
  const uint8_t WIFByte = 0xaa;
  const auto AddressString = "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA";
}  // namespace

/**/

TEST(identities, wif_from_bytes) {
  WIF wif(TestWIFBytes);
  ASSERT_STREQ(AddressString, wif.toString().c_str());
}

/**/

TEST(identities, wif_from_passphrase) {
  WIF wif = WIF::fromPassphrase(Passphrase, WIFByte);
  ASSERT_STREQ(AddressString, wif.toString().c_str());
}

/**/

TEST(identities, wif_from_string) {
  WIF wif(AddressString);
  ASSERT_STREQ(AddressString, wif.toString().c_str());
}

/**/

TEST(identities, wif_get_bytes) {
  WIF wif(AddressString);
  const auto wifBytes = wif.toBytes();
  for (unsigned int i = 0; i < WIF_SIZE; i++) {
    ASSERT_EQ(wifBytes[i], TestWIFBytes[i]);
  };
}

/**/

TEST(identities, wif_invalid) {
  const auto invalidWIFStr = "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1d";
  WIF wif(invalidWIFStr);
  ASSERT_FALSE(WIF::validate(wif));
}
