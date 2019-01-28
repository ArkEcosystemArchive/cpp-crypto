/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "helpers/encoding/hex.h"
#include "helpers/crypto_helpers.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"
#include "transactions/transaction.h"

namespace Ark {
namespace Crypto {
namespace Transactions {

class Deserializer {
 public:
  Deserializer(const std::string& serialized);
  Transaction deserialize();

 private:
  void deserializeHeader(Transaction& transaction);
  void deserializeType(Transaction& transaction);
  void deserializeTransfer(Transaction& transaction);
  void deserializeSecondSignatureRegistration(Transaction& transaction);
  void deserializeDelegateRegistration(Transaction& transaction);
  void deserializeVote(Transaction& transaction);
  void deserializeMultiSignatureRegistration(Transaction& transaction);
  void deserializeIPFS(Transaction& transaction);
  void deserializeTimelock(Transaction& transaction);
  void deserializeMultiPayment(Transaction& transaction);
  void deserializeDelegateResignation(Transaction& transaction);
  void deserializeSignatures(Transaction& transaction);
  void handleVersionOne(Transaction& transaction);

  std::string _serialized;
  std::vector<uint8_t> _binary;
  uint32_t _assetOffset;
};

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark

#endif
