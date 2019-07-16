
#include "identities/address.h"

#include "identities/privatekey.h"
#include "identities/publickey.h"

#include "helpers/encoding/hex.h"

#include "bcl/Base58Check.hpp"

#include <string>

Ark::Crypto::Identities::Address::Address(
    const char* newAddressStr) {
  (strlen(newAddressStr) == ADDRESS_LENGTH)
      ? void(memmove(
            this->bytes_,
            reinterpret_cast<const unsigned char *>(newAddressStr),
            ADDRESS_LENGTH))
      : void(this->bytes_[COMPRESSED_PUBLICKEY_SIZE] = {'\0'});
}
/**/

Ark::Crypto::Identities::Address::Address(
    const uint8_t* newAddressBytes) {
  memmove(this->bytes_, newAddressBytes, ADDRESS_LENGTH);
}

/**/

const uint8_t *Ark::Crypto::Identities::Address::toBytes() {
  return this->bytes_;
}

/**/

std::string Ark::Crypto::Identities::Address::toString() const {
  return std::string(this->bytes_, this->bytes_ + ADDRESS_LENGTH);
}

/**/

Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPassphrase(
    const char* passphrase,
    uint8_t networkVersion) {
  PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
  return fromPublicKey(publicKey, networkVersion);
}

/**/

Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPrivateKey(
    PrivateKey privateKey,
    uint8_t networkVersion) {
  PublicKey publicKey = PublicKey::fromPrivateKey(privateKey);
  return fromPublicKey(publicKey, networkVersion);
}

/**/

Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPublicKey(
    PublicKey publicKey,
    uint8_t networkVersion) {
  std::vector<uint8_t> seed(Ripemd160::HASH_LEN);
  Ripemd160::getHash(
      publicKey.toBytes(),
      COMPRESSED_PUBLICKEY_SIZE,
      &seed[0]);
  std::string s(35, '\0');
  Base58Check::pubkeyHashToBase58Check(&seed[0], networkVersion, &s[0]);
  return { s.c_str() };
}

/**/

bool Ark::Crypto::Identities::Address::validate(
    Address address,
    uint8_t networkVersion) {
  std::uint8_t pub_key_hash[Ripemd160::HASH_LEN] = {};
  uint8_t version = 0;
  Base58Check::pubkeyHashFromBase58Check(
      address.toString().c_str(),
      pub_key_hash,
      &version);
  return version == networkVersion;
}

/**/

bool Ark::Crypto::Identities::Address::validate(
    const char* addressStr,
    uint8_t networkVersion) {
  return validate(Address(addressStr), networkVersion);
}

/**/

bool Ark::Crypto::Identities::Address::validate(
    const uint8_t* addressBytes,
    uint8_t networkVersion) {
  return validate(Address(addressBytes), networkVersion);
}

/**/

std::string Ark::Crypto::Identities::Address::base58encode(
    const uint8_t* source) {
  // Magic numbers from Base58Check::pubkeyHashToBase58Check
  uint8_t temp[21 + 4] = {};
  char out[ADDRESS_LENGTH + 1] = {};

  uint8_t buf[21 + 4] = {};
  std::memcpy(buf, source, 21);

  Base58Check::bytesToBase58Check(buf, temp, 21, out);

  return std::string(out);
}

/**/

std::vector<uint8_t> Ark::Crypto::Identities::Address::bytesFromBase58Check(
    const char* address) {
  std::vector<std::uint8_t> recipientBytes;
  recipientBytes.resize(Ripemd160::HASH_LEN);
  uint8_t version = 0;
  Base58Check::pubkeyHashFromBase58Check(
      address,
      &recipientBytes[0],
      &version);
  recipientBytes.insert(recipientBytes.begin(), version);

  return recipientBytes;
}
