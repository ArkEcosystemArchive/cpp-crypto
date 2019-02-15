/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef BUILDER_H
#define BUILDER_H

#include "transactions/transaction.h"

namespace Ark {
namespace Crypto {
namespace Transactions {

class Builder {
 public:
  static Transaction buildTransfer(std::string recipientId, uint64_t amount, std::string vendorField,
                                   std::string passphrase, std::string secondPassphrase = "");
  static Transaction buildSecondSignatureRegistration(std::string passphrase, std::string secondPassphrase = "");
  static Transaction buildDelegateRegistration(std::string username, std::string passphrase,
                                               std::string secondPassphrase = "");
  static Transaction buildVote(std::vector<std::string> votes, std::string passphrase,
                               std::string secondPassphrase = "");
  static Transaction buildMultiSignatureRegistration(uint8_t min, uint8_t lifetime, std::vector<std::string> keysgroup,
                                                     std::string passphrase, std::string secondPassphrase = "");

 private:
  Builder();

  static Transaction sign(Transaction transaction, std::string passphrase, std::string secondPassphrase = "");

  Builder sign(const std::string& passphrase);

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
