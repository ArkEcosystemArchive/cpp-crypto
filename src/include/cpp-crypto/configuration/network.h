/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef NETWORK_H
#define NETWORK_H

#include "networks/abstractnetwork.h"
#include "networks/devnet.h"
#include "networks/mainnet.h"
#include "networks/testnet.h"

#include <vector>

namespace Ark {
namespace Crypto {
namespace Configuration {

using namespace Ark::Crypto::Networks;

/**
 * @brief This is the network configuration class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class Network {
 private:
  AbstractNetwork network_;

 public:
  AbstractNetwork get();
  void set(const AbstractNetwork& network);
};
/**/
};  // namespace Configuration
};  // namespace Crypto
};  // namespace Ark

#endif
