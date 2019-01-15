/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "identities/address.h"

/**
 * @brief: constructor
 *
 * @param: const char *const newAddressStr
 **/
Ark::Crypto::Identities::Address::Address(const char *const newAddressStr) {
  (strlen(newAddressStr) == ADDRESS_LENGTH)
      ? void(memmove(this->bytes_, reinterpret_cast<const unsigned char *>(newAddressStr), ADDRESS_LENGTH))
      : void(this->bytes_[COMPRESSED_PUBLICKEY_SIZE] = {'\0'});
}
/**/

Ark::Crypto::Identities::Address::Address(const uint8_t *newAddressBytes) {
  memmove(this->bytes_, newAddressBytes, ADDRESS_LENGTH);
}
/**/

/**
 * @brief: returns bytes of Address
 *
 * @return const uint8_t
 **/
const uint8_t *Ark::Crypto::Identities::Address::toBytes() {
  return this->bytes_;
}
/**/

/**
 * @brief: returns std::string representation of stored bytes
 **/
std::string Ark::Crypto::Identities::Address::toString() const {
  return std::string(this->bytes_, this->bytes_ + ADDRESS_LENGTH);
}
/**/

/**
 * @brief Derive the address from the given passphrase.
 *
 * @param const char* const passphrase
 * @param uint8_t networkVersion
 *
 * @return Address
 **/
Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPassphrase(const char *const passphrase,
                                                                                  uint8_t networkVersion) {
  PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
  return fromPublicKey(publicKey, networkVersion);
}
/**/

/**
 * @brief Derive the address from the given private key.
 *
 * @param PrivateKey privateKey
 * @param uint8_t networkVersion
 *
 * @return Address
 **/
Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPrivateKey(PrivateKey privateKey,
                                                                                  uint8_t networkVersion) {
  PublicKey publicKey = PublicKey::fromPrivateKey(privateKey);
  return fromPublicKey(publicKey, networkVersion);
}
/**/

/**
 * @brief Derive the address from the given public key.
 *
 * @param PublicKey publicKey
 * @param uint8_t networkVersion
 *
 * @return Address
 **/
Ark::Crypto::Identities::Address Ark::Crypto::Identities::Address::fromPublicKey(PublicKey publicKey,
                                                                                 uint8_t networkVersion) {
  std::vector<uint8_t> seed(Ripemd160::HASH_LEN);
  Ripemd160::getHash(publicKey.toBytes(), COMPRESSED_PUBLICKEY_SIZE, &seed[0]);
  std::string s(35, '\0');
  Base58Check::pubkeyHashToBase58Check(&seed[0], networkVersion, &s[0]);
  return {s.c_str()};
}
/**/

/**
 * @brief Validate the given address.
 *
 * @param Address address
 * @param uint8_t networkVersion
 *
 * @return bool
 **/
bool Ark::Crypto::Identities::Address::validate(Address address, uint8_t networkVersion) {
  std::uint8_t pub_key_hash[Ripemd160::HASH_LEN] = {};
  uint8_t version = 0;
  Base58Check::pubkeyHashFromBase58Check(address.toString().c_str(), pub_key_hash, &version);
  return version == networkVersion;
}
/**/

/**
 * @brief Validate the given Address string to the network version.
 *
 * @param const char *const privateKey
 * @param uint8_t networkVersion
 *
 * @return bool
 **/
bool Ark::Crypto::Identities::Address::validate(const char *const addressStr, uint8_t networkVersion) {
  return validate(Address(addressStr), networkVersion);
}
/**/

/**
 * @brief Validate the given Address bytes to the network version.
 *
 * @param const uint8_t *addressBytes
 * @param uint8_t networkVersion
 *
 * @return bool
 **/
bool Ark::Crypto::Identities::Address::validate(const uint8_t *addressBytes, uint8_t networkVersion) {
  return validate(Address(addressBytes), networkVersion);
}
/**/

/**
 * @brief Reads 21 bytes from source and returns an base58 encoded string
 *
 * @param uint8_t *source
 *
 * @return std::string
 **/
std::string Ark::Crypto::Identities::Address::base58encode(const uint8_t *source) {
  // Magic numbers from Base58Check::pubkeyHashToBase58Check
  uint8_t temp[21 + 4] = {};
  char out[ADDRESS_LENGTH + 1] = {};

  uint8_t buf[21 + 4] = {};
  std::memcpy(buf, source, 21);

  Base58Check::bytesToBase58Check(buf, temp, 21, out);

  return std::string(out);
}

/**
 * @brief Decodes the base58 encoded address
 *
 * @param const char* const address
 *
 * @return std::vector<uint8_t>
 **/
std::vector<uint8_t> Ark::Crypto::Identities::Address::bytesFromBase58Check(const char *const address) {
  std::vector<std::uint8_t> recipientIdBytes;
  recipientIdBytes.resize(Ripemd160::HASH_LEN);
  uint8_t version = 0;
  Base58Check::pubkeyHashFromBase58Check(address, &recipientIdBytes[0], &version);
  recipientIdBytes.insert(recipientIdBytes.begin(), version);

  return recipientIdBytes;
}
