
#include "networks/abstractnetwork.h"

#include <cstdint>

uint8_t Ark::Crypto::Networks::AbstractNetwork::getBase58Prefix(
    Base58PrefixType prefix) const {
  switch (prefix) {
    case 0: return this->base58_.ADDRESS_P2PKH;
    case 1: return this->base58_.ADDRESS_P2SH;
    case 2: return this->base58_.WIF;
  };
}

/**/

void Ark::Crypto::Networks::AbstractNetwork::setBase58Prefix(
    Base58PrefixType prefix,
    uint8_t newByte) {
  if (!isLocked_) {
    switch (prefix) {
      case 0: this->base58_.ADDRESS_P2PKH = newByte; break;
      case 1: this->base58_.ADDRESS_P2SH = newByte; break;
      case 2: this->base58_.WIF = newByte; break;
    };
  };
}

/**/

long Ark::Crypto::Networks::AbstractNetwork::getBIP32Prefix(
    BIP32PrefixType prefix) const {
  return (prefix == 0)
    ? this->bip32_.PREFIX_XPUB
    : this->bip32_.PREFIX_XPRV;
}

/**/

void Ark::Crypto::Networks::AbstractNetwork::setBIP32Prefix(
    BIP32PrefixType prefix,
    long newByte) {
  if (!isLocked_) {
    switch (prefix) {
      case 0: this->bip32_.PREFIX_XPUB = newByte; break;
      case 1: this->bip32_.PREFIX_XPRV = newByte; break;
    };
  };
}

/**/

bool Ark::Crypto::Networks::AbstractNetwork::isLocked() const {
  return this->isLocked_;
}

/**/

const char* Ark::Crypto::Networks::AbstractNetwork::epoch() const {
  return this->epoch_;
}

/**/

uint8_t Ark::Crypto::Networks::AbstractNetwork::version() const {
  return uint8_t(base58_.ADDRESS_P2PKH);
}
