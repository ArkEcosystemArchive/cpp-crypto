/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef NETWORKS_HPP
#define NETWORKS_HPP

#include "common/network.hpp"

namespace Ark {
namespace Crypto {
/**/
class Networks {
 public:
  static const Network Devnet();
  static const Network Mainnet();
  static const Network Testnet();
};
/**/
}  // namespace Crypto
}  // namespace Ark

#endif
