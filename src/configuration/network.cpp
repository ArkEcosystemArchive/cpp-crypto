
#include "configuration/network.h"

Ark::Crypto::Networks::AbstractNetwork Ark::Crypto::Configuration::Network::get() {
  return (this->network_.getBase58Prefix(BASE58_ADDRESS_P2PKH) == 0x00)
    ? (Devnet)
    : (this->network_);
}

/**/

void Ark::Crypto::Configuration::Network::set(
    const Ark::Crypto::Networks::AbstractNetwork& network) {
  this->network_ = network;
};
