/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "configuration/fee.h"

/**
 * @brief Get the transaction fee for the given type.
 *
 * @param const int type
 * @return uint64_t
 **/
uint64_t Ark::Crypto::Configuration::Fee::get(int type) {
  return this->fees_[type];
};
/**/

/**
 * @brief Set the transaction fee for the given type.
 *
 * @param const int type
 * @param const uint64_t fee
 **/
void Ark::Crypto::Configuration::Fee::set(int type, uint64_t fee) {
  this->fees_[type] = fee;
};
/**/
