/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "identities/privatekey.hpp"
#include "identities/publickey.hpp"

#include <map>
#include <string>
#include <vector>

namespace Ark {
namespace Crypto {
namespace Transactions {
/**/
struct TransactionAsset {
  struct {
    std::string publicKey;
  } signature;

  struct {
    std::string username;
  } delegate;

  std::vector<std::string> votes;

  struct {
    uint8_t min;
    uint8_t lifetime;
    std::vector<std::string> keysgroup;
  } multiSignature;
};
/**/
class Transaction {
public:
  Transaction() = default;
  Transaction(const Transaction&) = default;
  Transaction& operator=(const Transaction&) = default;
  Transaction(Transaction&&) = default;
  Transaction& operator=(Transaction&&) = default;

  std::string getId() const;

  std::string sign(const char* passphrase);
  std::string secondSign(const char* passphrase);

  bool verify() const;
  bool secondVerify(const char* secondPublicKey) const;

  std::vector<uint8_t> toBytes(bool skipSignature = true, bool skipSecondSignature = true) const;
  std::map<std::string, std::string> toArray() const;
  std::string toJson() const;

  uint8_t header = 0;
  uint8_t network = 0;
  uint8_t type = 0;
  uint8_t version = 0;
  TransactionAsset asset = {};
  uint32_t timelock_type = 0;
  std::vector<std::string> signatures = {};
  std::string id = "";
  std::string recipient = "";
  std::string senderPublicKey = "";
  std::string signature = "";
  std::string secondSignature = "";
  std::string signSignature = "";
  std::string vendorField = "";
  std::string vendorFieldHex = "";
  uint32_t expiration = 0;
  uint32_t timestamp = 0;
  uint64_t amount = 0;
  uint64_t fee = 0;
  uint64_t timelock = 0;

private:
  bool internalVerify(
      const std::string& publicKey,
      std::vector<uint8_t> bytes,
      const std::string& signature) const;
};
/**/
};  // namespace Transactions
};  // namespace Crypto
};  // namespace Ark

#endif
