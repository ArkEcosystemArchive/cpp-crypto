/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef COMMON_FEE_POLICY_HPP
#define COMMON_FEE_POLICY_HPP

#include <cstdint>
#include <vector>

namespace Ark {
namespace Crypto {

static const uint64_t AMOUNT_ZERO = 0ULL;

typedef std::vector<uint64_t> FeePolicy;

}  // namespace Crypto
}  // namespace Ark

#endif
