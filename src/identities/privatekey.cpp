
#include "identities/privatekey.h"

#include "helpers/encoding/hex.h"

#include "bcl/Base58Check.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Sha256Hash.hpp"

#include <cstdint>
#include <cstring>
#include <string>

Ark::Crypto::Identities::PrivateKey::PrivateKey(
    const char* newPrivateKeyStr) {
  memmove(
      this->bytes_,
      HexToBytes(newPrivateKeyStr).data(),
      PRIVATEKEY_SIZE);
}

/**/

Ark::Crypto::Identities::PrivateKey::PrivateKey(
    const uint8_t* newPrivateKeyBytes) {
  memmove(this->bytes_, newPrivateKeyBytes, PRIVATEKEY_SIZE);
}

/**/

const uint8_t *Ark::Crypto::Identities::PrivateKey::toBytes() {
  return this->bytes_;
};

/**/

std::string Ark::Crypto::Identities::PrivateKey::toString() const {
  return BytesToHex(this->bytes_, this->bytes_ + PRIVATEKEY_SIZE);
}

/**/

Ark::Crypto::Identities::PrivateKey Ark::Crypto::Identities::PrivateKey::fromPassphrase(
    const char* passphrase) {
  std::vector<uint8_t> privateKey(PRIVATEKEY_SIZE);
  auto hash = Sha256::getHash(
      reinterpret_cast<const unsigned char *>(passphrase),
      strlen(passphrase));
  memcpy(&privateKey[0], hash.value, privateKey.size());
  return {
    BytesToHex(&privateKey[0], &privateKey[0] + PRIVATEKEY_SIZE).c_str()
  };
}

/**/

Ark::Crypto::Identities::PrivateKey Ark::Crypto::Identities::PrivateKey::fromHex(
    const char* privateKey) {
  return { privateKey };
}

/**/

Ark::Crypto::Identities::PrivateKey Ark::Crypto::Identities::PrivateKey::fromWIFString(
    const char* wifStr,
    uint8_t wifByte) {
  Uint256 bigNum;
  bool compressed = true;
  Base58Check::privateKeyFromBase58Check(
      wifStr,
      bigNum,
      &wifByte,
      &compressed);
  std::vector<uint8_t> privateKey(PRIVATEKEY_SIZE);
  bigNum.getBigEndianBytes(&privateKey[0]);
  return {
    BytesToHex(&privateKey[0], &privateKey[0] + PRIVATEKEY_SIZE).c_str()
  };
}

/**/

bool Ark::Crypto::Identities::PrivateKey::validate(
    PrivateKey privateKey) {
  return PrivateKey::validate(privateKey.toString().c_str());
}

/**/

bool Ark::Crypto::Identities::PrivateKey::validate(
    const char* privateKeyStr) {
  // check length
  return ((strlen(privateKeyStr) / 2) == PRIVATEKEY_SIZE);
}

/**/

bool Ark::Crypto::Identities::PrivateKey::validate(
    const uint8_t* privateKeyBytes) {
  return validate(PrivateKey(privateKeyBytes));
}
