
#include "transactions/builder.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "common/configuration.hpp"
#include "defaults/transaction_types.hpp"
#include "identities/address.hpp"
#include "crypto/slot.hpp"
#include "utils/crypto_helpers.h"
#include "identities/publickey.hpp"

namespace Ark {
namespace Crypto {
namespace Transactions {

Transaction Builder::buildTransfer(
    std::string recipient,
    uint64_t amount,
    std::string vendorField,
    const std::string& passphrase,
    const std::string&secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  if (amount < 1ULL) { return transaction; }

  transaction.version = 0x01;
  transaction.type = TransactionTypes::Transfer;
  transaction.fee = configuration.getFee(TransactionTypes::Transfer);
  transaction.recipient = std::move(recipient);
  transaction.amount = amount;
  transaction.vendorField = std::move(vendorField);

  sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildSecondSignatureRegistration(
    const std::string& passphrase,
    const std::string& secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = TransactionTypes::SecondSignatureRegistration;
  transaction.fee = configuration.getFee(
      TransactionTypes::SecondSignatureRegistration);

    transaction.asset.signature.publicKey =
        identities::PublicKey::fromPassphrase(secondPassphrase.c_str())
        .toString();

  sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildDelegateRegistration(
    std::string username,
    const std::string& passphrase,
    const std::string& secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = TransactionTypes::DelegateRegistration;
  transaction.fee = configuration.getFee(TransactionTypes::DelegateRegistration);
  transaction.asset.delegate.username = std::move(username);

  sign(transaction,
       std::move(passphrase),
       std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildVote(
    std::vector<std::string> votes,
    const std::string& passphrase,
    const std::string& secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = TransactionTypes::Vote;
  transaction.fee = configuration.getFee(TransactionTypes::Vote);
  transaction.asset.votes = std::move(votes);

  const auto recipient = identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version);
  transaction.recipient = recipient.toString();

  sign(transaction,
       std::move(passphrase),
       std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildMultiSignatureRegistration(
    uint8_t min,
    uint8_t lifetime,
    std::vector<std::string>& keysgroup,
    const std::string& passphrase,
    const std::string& secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = TransactionTypes::MultiSignatureRegistration;
  transaction.fee =
      (keysgroup.size() + 1) *
      configuration.getFee(TransactionTypes::MultiSignatureRegistration);
  transaction.asset.multiSignature.min = min;
  transaction.asset.multiSignature.lifetime = lifetime;
  transaction.asset.multiSignature.keysgroup = keysgroup;

  const auto recipient = identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version);
  transaction.recipient = recipient.toString();

  sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
  
  return transaction;
}

/**/

void Builder::sign(
    Transaction& transaction,
    const std::string& passphrase,
    const std::string& secondPassphrase,
    const Configuration& configuration) {
  transaction.timestamp = static_cast<uint32_t>(
        Slot::time(configuration.getNetwork()));
  transaction.sign(passphrase.c_str());

  if (secondPassphrase.length() > 0) {
    transaction.secondSign(secondPassphrase.c_str());
  };

  transaction.id = transaction.getId();
}

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark
