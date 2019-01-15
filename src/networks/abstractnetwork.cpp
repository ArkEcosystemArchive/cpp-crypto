/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "networks/abstractnetwork.h"

/**
 * @brief get the networks Base58 prefix byte given a prefix name
 *
 * @param Base58PrefixType prefix
 * @return uint8_t
 **/
uint8_t Ark::Crypto::Networks::AbstractNetwork::getBase58Prefix(Base58PrefixType prefix) const {
  switch (prefix) {
    case 0:
      return this->base58_.ADDRESS_P2PKH;
    case 1:
      return this->base58_.ADDRESS_P2SH;
    case 2:
      return this->base58_.WIF;
    default:
      return 0;
  }
}
/**/

/**
 * @brief sets the networks Base58 prefix given a prefix name and byte
 *
 * @param Base58PrefixType prefix
 * @param uint8_t newByte
 **/
void Ark::Crypto::Networks::AbstractNetwork::setBase58Prefix(Base58PrefixType prefix, uint8_t newByte) {
  if (!isLocked_) {
    switch (prefix) {
      case 0:
        this->base58_.ADDRESS_P2PKH = newByte;
      case 1:
        this->base58_.ADDRESS_P2SH = newByte;
      case 2:
        this->base58_.WIF = newByte;
    };
  }
}
/**/

/**
 * @brief get the networks BIP32 prefix byte given a prefix name
 *
 * @param Base58PrefixType prefix
 * @return long
 **/
long Ark::Crypto::Networks::AbstractNetwork::getBIP32Prefix(BIP32PrefixType prefix) const {
  return (prefix == 0) ? this->bip32_.PREFIX_XPUB : this->bip32_.PREFIX_XPRV;
}
/**/

/**
 * @brief sets the networks BIP32 prefix given a prefix name and byte
 *
 * @param BIP32PrefixType prefix
 * @param long newByte
 **/
void Ark::Crypto::Networks::AbstractNetwork::setBIP32Prefix(BIP32PrefixType prefix, long newByte) {
  if (!isLocked_) {
    switch (prefix) {
      case 0:
        this->bip32_.PREFIX_XPUB = newByte;
        break;
      case 1:
        this->bip32_.PREFIX_XPRV = newByte;
        break;
    };
  }
}
/**/

/**
 * Get the network epoch.
 *
 * @return const char*
 **/
bool Ark::Crypto::Networks::AbstractNetwork::isLocked() const {
  return this->isLocked_;
}
/**/

/**
 * Get the network epoch.
 *
 * @return const char*
 **/
const char* Ark::Crypto::Networks::AbstractNetwork::epoch() const {
  return this->epoch_;
}
/**/

/**
 * Get the network version as number.
 *
 * @return int
 **/
uint8_t Ark::Crypto::Networks::AbstractNetwork::version() const {
  return uint8_t(base58_.ADDRESS_P2PKH);
}
/**/
