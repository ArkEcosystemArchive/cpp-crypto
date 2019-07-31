
#include "transactions/builder.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "common/configuration.hpp"
#include "defaults/transaction_types.hpp"
#include "identities/address.hpp"
#include "utils/slot.h"
#include "helpers/crypto_helpers.h"
#include "identities/publickey.hpp"

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

  transaction.type = defaults::TransactionTypes::Transfer;
  transaction.fee = configuration.getFee(defaults::TransactionTypes::Transfer);
  transaction.recipient = std::move(recipient);
  transaction.amount = amount;
  transaction.vendorField = std::move(vendorField);

  return sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
}

/**/

Transaction Builder::buildSecondSignatureRegistration(
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  transaction.type = defaults::TransactionTypes::SecondSignatureRegistration;
  transaction.fee = configuration.getFee(
      defaults::TransactionTypes::SecondSignatureRegistration);

    transaction.asset.signature.publicKey =
        identities::PublicKey::fromPassphrase(secondPassphrase.c_str())
        .toString();

  return sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
}

/**/

Transaction Builder::buildDelegateRegistration(
    std::string username,
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  transaction.type = defaults::TransactionTypes::DelegateRegistration;
  transaction.fee = configuration.getFee(
      defaults::TransactionTypes::DelegateRegistration);
  transaction.asset.delegate.username = std::move(username);

  return sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
}

/**/

Transaction Builder::buildVote(
    std::vector<std::string> votes,
    std::string passphrase,
    std::string secondPassphrase,
    const Configuration& configuration) {
  Transaction transaction;
  transaction.type = defaults::TransactionTypes::Vote;
  transaction.fee = configuration.getFee(defaults::TransactionTypes::Vote);
  transaction.asset.votes = std::move(votes);

  const auto recipient = identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version());
  transaction.recipient = recipient.toString();

  return sign(transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
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
  transaction.type = defaults::TransactionTypes::MultiSignatureRegistration;
  transaction.fee = (
      keysgroup.size() + 1)
      * configuration.getFee(defaults::TransactionTypes::MultiSignatureRegistration);
  transaction.asset.multiSignature.min = min;
  transaction.asset.multiSignature.lifetime = lifetime;
  transaction.asset.multiSignature.keysgroup = keysgroup;

  const auto recipient = identities::Address::fromPassphrase(
      passphrase.c_str(),
      configuration.getNetwork().version());
  transaction.recipient = recipient.toString();

  return sign(
      transaction,
      std::move(passphrase),
      std::move(secondPassphrase));
}

/**/

Transaction Builder::sign(
    Transaction transaction,
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

  return transaction;
}

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark
