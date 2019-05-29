
#include "identities/wif.h"

#include "helpers/encoding/hex.h"

#include "bcl/Base58Check.hpp"
#include "bcl/Uint256.hpp"

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>

Ark::Crypto::Identities::WIF::WIF(
    const char* newWIFStr) {
  (strlen(newWIFStr) == WIF_SIZE)
      ? void(memmove(
            this->bytes_,
            reinterpret_cast<const unsigned char *>(newWIFStr),
            WIF_SIZE))
      : void(this->bytes_[WIF_SIZE - 1] = {'\0'});
}

/**/

Ark::Crypto::Identities::WIF::WIF(
    const uint8_t* newWIFBytes) {
  memmove(this->bytes_, newWIFBytes, WIF_SIZE);
}

/**/

const uint8_t *Ark::Crypto::Identities::WIF::toBytes() {
  return this->bytes_;
};

/**/

std::string Ark::Crypto::Identities::WIF::toString() const {
  return std::string(this->bytes_, this->bytes_ + WIF_SIZE);
}

/**/

bool Ark::Crypto::Identities::WIF::validate(WIF wif) {
  const auto wifString = wif.toString();
  return strrchr(wifString.c_str(), '\0') == nullptr;
}

/**/

Ark::Crypto::Identities::WIF Ark::Crypto::Identities::WIF::fromPassphrase(
    const char* passphrase,
    uint8_t wifByte) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
  std::string wifStr(53, '\0');
  Base58Check::privateKeyToBase58Check(
      Uint256(privateKey.toString().c_str()),
      wifByte,
      true,
      &wifStr[0]);
  return { wifStr.c_str() };
}
