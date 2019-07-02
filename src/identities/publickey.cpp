

#include "identities/publickey.h"

#include "helpers/encoding/hex.h"

#include "uECC.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

Ark::Crypto::Identities::PublicKey::PublicKey(
    const char* newPublicKeyStr) {
  memmove(
      this->bytes_,
      HexToBytes(newPublicKeyStr).data(),
      COMPRESSED_PUBLICKEY_SIZE);
}

/**/

Ark::Crypto::Identities::PublicKey::PublicKey(
    const uint8_t* newPublicKeyBytes) {
  memmove(this->bytes_, newPublicKeyBytes, COMPRESSED_PUBLICKEY_SIZE);
}

/**/

const uint8_t* Ark::Crypto::Identities::PublicKey::toBytes() {
  return this->bytes_;
}

/**/

bool Ark::Crypto::Identities::PublicKey::isValid() {
  return PublicKey::validate(*this);
}

/**/

std::string Ark::Crypto::Identities::PublicKey::toString() const {
  return BytesToHex(this->bytes_, this->bytes_ + COMPRESSED_PUBLICKEY_SIZE);
}

/**/

Ark::Crypto::Identities::PublicKey Ark::Crypto::Identities::PublicKey::fromPassphrase(
    const char* passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
  return PublicKey::fromPrivateKey(privateKey);
}

/**/

Ark::Crypto::Identities::PublicKey Ark::Crypto::Identities::PublicKey::fromPrivateKey(
    PrivateKey privateKey) {
  std::vector<uint8_t> publicKey(COMPRESSED_PUBLICKEY_SIZE);
  const struct uECC_Curve_t *curve = uECC_secp256k1();
  uint8_t pub[64] = {};
  // TODO: using the current uECC implementation, a private key value of "1" will return a false negative.
  // It appears to be not supported given the following issue: https://github.com/kmackay/micro-ecc/issues/128
  const uint8_t *privkeyBytes = privateKey.toBytes();
  // Don't check the return inline with the assert.  MSVC optimizer does bad things.
  uECC_compute_public_key(
      &privkeyBytes[0],
      pub,
      curve);  
  uECC_compress(pub, &publicKey[0], curve);
  return {
    BytesToHex(&publicKey[0], &publicKey[0] + COMPRESSED_PUBLICKEY_SIZE).c_str()
  };
}

/**/

Ark::Crypto::Identities::PublicKey Ark::Crypto::Identities::PublicKey::fromHex(
    const char* publicKey) {
  return { publicKey };
}

/**/

bool Ark::Crypto::Identities::PublicKey::validate(
    PublicKey publicKey) {
  // compressed publicKey bytes (uint8_t*)
  auto publicKeyBytes = publicKey.toBytes();
  // create uncompressed publicKey buffer (uint8_t[64])             
  uint8_t uncompressedPublicKey[64] = {};
  // define the curve-type
  const struct uECC_Curve_t *curve = uECC_secp256k1();

  // decompress the key     
  uECC_decompress(publicKeyBytes, uncompressedPublicKey, curve);  

  // validate the uncompressed publicKey
  return (uECC_valid_public_key(uncompressedPublicKey, curve) != 0);
}

/**/

bool Ark::Crypto::Identities::PublicKey::validate(
    const char* publicKeyStr) {
  return validate(PublicKey(publicKeyStr));
}

/**/

bool Ark::Crypto::Identities::PublicKey::validate(
    const uint8_t* publicKeyBytes) {
  return validate(PublicKey(publicKeyBytes));
}
