/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_CRYPTO_SLOTS_HPP
#define ARK_CRYPTO_SLOTS_HPP

#include <cstdint>

#include "common/network.hpp"

namespace Ark {
namespace Crypto {

////////////////////////////////////////////////////////////////////////////////
class Slot {
  public:
    static uint64_t epoch(const Network &network);
    static uint64_t time(const Network &network);
};

}  // namespace Crypto
}  // namespace Ark

#endif
