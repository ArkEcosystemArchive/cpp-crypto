/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_COMMON_FEE_POLICY_HPP
#define ARK_COMMON_FEE_POLICY_HPP

#include <cstdint>
#include <vector>

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
// Fee Policy Container
using FeePolicy = std::vector<uint64_t>;

}  // namespace Crypto
}  // namespace Ark

#endif
