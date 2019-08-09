/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "transactions/transaction.h"

#include <cstdint>
#include <string>
#include <vector>

namespace Ark {
namespace Crypto {
namespace Transactions {
/**/
class Serializer {
public:
  Serializer(Transaction transaction);
  std::string serialize() const;

private:
  void serializeVendorField(std::vector<uint8_t>& bytes) const;
  void serializeType(std::vector<uint8_t>& bytes) const;
  void serializeTransfer(std::vector<uint8_t>& bytes) const;
  void serializeSecondSignatureRegistration(std::vector<uint8_t>& bytes) const;
  void serializeDelegateRegistration(std::vector<uint8_t>& bytes) const;
  void serializeVote(std::vector<uint8_t>& bytes) const;
  void serializeMultiSignatureRegistration(std::vector<uint8_t>& bytes) const;
  void serializeSignatures(std::vector<uint8_t>& bytes) const;

  Transaction _transaction;
};
/**/
}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark

#endif
