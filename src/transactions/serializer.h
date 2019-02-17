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

namespace Ark {
namespace Crypto {
namespace Transactions {

class Serializer {
 public:
  Serializer(const Transaction& transaction);
  std::string serialize();

 private:
  void serializeVendorField(std::vector<uint8_t>& bytes);
  void serializeType(std::vector<uint8_t>& bytes);
  void serializeTransfer(std::vector<uint8_t>& bytes);
  void serializeSecondSignatureRegistration(std::vector<uint8_t>& bytes);
  void serializeDelegateRegistration(std::vector<uint8_t>& bytes);
  void serializeVote(std::vector<uint8_t>& bytes);
  void serializeMultiSignatureRegistration(std::vector<uint8_t>& bytes);
  void serializeSignatures(std::vector<uint8_t>& bytes);

  Transaction _transaction;
};

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark

#endif
