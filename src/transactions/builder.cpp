
#include "transactions/builder.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "common/configuration.hpp"
#include "defaults/transaction_types.hpp"
#include "identities/address.h"
#include "utils/slot.h"
#include "helpers/crypto_helpers.h"

namespace Ark {
namespace Crypto {
namespace Transactions {

Transaction Builder::buildTransfer(
    std::string recipient,
    uint64_t amount,
    std::string vendorField,
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  if (amount < 1ULL) { return transaction; }

  transaction.version = 0x01;
  transaction.type = defaults::TransactionTypes::Transfer;
  transaction.fee = configuration.getFee(defaults::TransactionTypes::Transfer);
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
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = defaults::TransactionTypes::SecondSignatureRegistration;
  transaction.fee = configuration.getFee(
      defaults::TransactionTypes::SecondSignatureRegistration);

  const auto publicKey = Identities::PublicKey::fromPassphrase(
      secondPassphrase.c_str());
  transaction.asset.signature.publicKey = publicKey.toString();

  sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildDelegateRegistration(
    std::string username,
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = defaults::TransactionTypes::DelegateRegistration;
  transaction.fee = configuration.getFee(
      defaults::TransactionTypes::DelegateRegistration);
  transaction.asset.delegate.username = std::move(username);

  sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
  
  return transaction;
}

/**/

Transaction Builder::buildVote(
    std::vector<std::string> votes,
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = defaults::TransactionTypes::Vote;
  transaction.fee = configuration.getFee(defaults::TransactionTypes::Vote);
  transaction.asset.votes = std::move(votes);

  const auto recipient = Identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version());
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
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  
  transaction.version = 0x01;
  transaction.type = defaults::TransactionTypes::MultiSignatureRegistration;
  transaction.fee = (
      keysgroup.size() + 1)
      * configuration.getFee(defaults::TransactionTypes::MultiSignatureRegistration);
  transaction.asset.multiSignature.min = min;
  transaction.asset.multiSignature.lifetime = lifetime;
  transaction.asset.multiSignature.keysgroup = keysgroup;

  const auto recipient = Identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version());
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
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  transaction.timestamp = static_cast<uint32_t>(
      Utils::Slot::time(configuration.getNetwork()));
  transaction.sign(passphrase.c_str());

  if (secondPassphrase.length() > 0) {
    transaction.secondSign(secondPassphrase.c_str());
  };

  transaction.id = transaction.getId();
}

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark
