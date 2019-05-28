
#include "configuration/fee.h"

#include <cstdint>

uint64_t Ark::Crypto::Configuration::Fee::get(
    int type) {
  return this->fees_[type];
};

/**/

void Ark::Crypto::Configuration::Fee::set(
    int type,
    uint64_t fee) {
  this->fees_[type] = fee;
};
