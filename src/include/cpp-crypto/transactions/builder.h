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

#include <cstdint>
#include <string>
#include <vector>

#include "transactions/transaction.h"
#include "common/configuration.hpp"

namespace Ark {
namespace Crypto {
namespace Transactions {
/**/
class Builder {
public:
  /**
  * Builder::buildTransfer()
  *
  * note: The 'Type 0'/Transfer amount must be greater than 0 ARKtoshi.
  * If amount is not > 0, Builder will return an empty Transaction object and
  * validation will fail.
  **/
  static Transaction buildTransfer(
      std::string recipient,
      uint64_t amount,
      std::string vendorField,
      std::string passphrase,
      std::string secondPassphrase = "",
      const Configuration& configuration = {});
  /**/

  static Transaction buildSecondSignatureRegistration(
      std::string passphrase,
      std::string secondPassphrase = "",
      const Configuration& configuration = {});

  static Transaction buildDelegateRegistration(
      std::string username,
      std::string passphrase,
      std::string secondPassphrase = "",
      const Configuration& configuration = {});

  static Transaction buildVote(
      std::vector<std::string> votes,
      std::string passphrase,
      std::string secondPassphrase = "",
      const Configuration& configuration = {});

  static Transaction buildMultiSignatureRegistration(
      uint8_t min,
      uint8_t lifetime,
      std::vector<std::string>& keysgroup,
      std::string passphrase,
      std::string secondPassphrase = "",
      const Configuration& configuration = {});

private:
  Builder();

  static void sign(
      Transaction& transaction,
      const std::string& passphrase,
      const std::string& secondPassphrase = "",
      const Configuration& configuration = {});

  Builder sign(const std::string& passphrase);

private:
  void serializeVendorField(const std::vector<uint8_t>& bytes);
  void serializeType(const std::vector<uint8_t>& bytes);
  void serializeTransfer(const std::vector<uint8_t>& bytes);
  void serializeSecondSignatureRegistration(const std::vector<uint8_t>& bytes);
  void serializeDelegateRegistration(const std::vector<uint8_t>& bytes);
  void serializeVote(const std::vector<uint8_t>& bytes);
  void serializeMultiSignatureRegistration(const std::vector<uint8_t>& bytes);
  void serializeSignatures(const std::vector<uint8_t>& bytes);

  Transaction _transaction;
};
/**/
};  // namespace Transactions
};  // namespace Crypto
};  // namespace Ark

#endif
