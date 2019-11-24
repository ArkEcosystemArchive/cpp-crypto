/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_BUILDERS_IPFS_HPP
#define ARK_TRANSACTIONS_BUILDERS_IPFS_HPP

#include <cstdint>
#include <cstring>

#include "transactions/builders/common.hpp"

#include "interfaces/constants.h"

namespace Ark {
namespace Crypto {
namespace transactions {
namespace builder {

////////////////////////////////////////////////////////////////////////////////
// Forward Declaration
class Ipfs;

////////////////////////////////////////////////////////////////////////////////
class Ipfs : public Common<Ipfs> {
  public:
    ////////////////////////////////////////////////////////////////////////////
    // Ipfs hash
    Ipfs &ipfs(const uint8_t *ipfsHash, const size_t length) {
        this->transaction.data.asset.ipfs.dag.insert(
            this->transaction.data.asset.ipfs.dag.begin(),
            ipfsHash,
            ipfsHash + length);
        return *this;
    }
};

}  // namespace builder
}  // namespace transactions
}  // namespace Crypto
}  // namespace Ark

#endif
