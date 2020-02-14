/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "common/configuration.hpp"

#include "managers/network_manager.hpp"
#include "managers/fee_manager.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Network initialization: Custom Network w/StaticFees
Configuration::Configuration(const Network &network) {
    setNetwork(network);
}

////////////////////////////////////////////////////////////////////////////////
// FeePolicy initialization: ARK Devnet w/Custom Fees
Configuration::Configuration(const FeePolicy &policy) {
    setPolicy(policy);
}

////////////////////////////////////////////////////////////////////////////////
// Network & Fee initialization: Custom Network w/Custom Fees
Configuration::Configuration(const Network &network, const FeePolicy &policy) {
    setNetwork(network);
    setPolicy(policy);
}

////////////////////////////////////////////////////////////////////////////////
// Compares the Network and FeePolicy for equality.
auto Configuration::operator==(const Configuration &other) const -> bool {
    return this->network_ == other.network_ &&
           this->feePolicy_ == other.feePolicy_;
}

////////////////////////////////////////////////////////////////////////////////
// Compares the Network and FeePolicy for inequality.
auto Configuration::operator!=(const Configuration &other) const -> bool {
    return this->network_ != other.network_ ||
           this->feePolicy_ != other.feePolicy_;
}

}  // namespace Crypto
}  // namespace Ark
