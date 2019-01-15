/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "configuration/network.h"

/**
 * @brief Get the network used for crypto operations.
 *
 * @return AbstractNetwork
 **/
Ark::Crypto::Networks::AbstractNetwork Ark::Crypto::Configuration::Network::get() {
  return (this->network_.getBase58Prefix(BASE58_ADDRESS_P2PKH) == 0x00) ? (Devnet) : (this->network_);
}
/**/

/**
 * @brief Set the network used for crypto operations.
 *
 * @param AbstractNetwork network
 **/
void Ark::Crypto::Configuration::Network::set(const Ark::Crypto::Networks::AbstractNetwork& network) {
  this->network_ = network;
};
/**/
