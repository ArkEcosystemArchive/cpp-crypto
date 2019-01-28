#include "transactions/builder.h"
#include "configuration/fee.h"
#include "configuration/network.h"
#include "enums/types.h"
#include "helpers/crypto_helpers.h"
#include "identities/address.h"
#include "utils/slot.h"

namespace Ark {
namespace Crypto {
namespace Transactions {

Transaction Builder::buildTransfer(std::string recipientId, uint64_t amount, std::string vendorField,
                                   std::string passphrase, std::string secondPassphrase) {
  Transaction transaction;
  transaction.type = Enums::Types::TRANSFER;
  transaction.fee = Configuration::Fee().get(Enums::Types::TRANSFER);
  transaction.recipientId = std::move(recipientId);
  transaction.amount = std::move(amount);
  transaction.vendorField = std::move(vendorField);

  return sign(transaction, std::move(passphrase), std::move(secondPassphrase));
}

Transaction Builder::buildSecondSignatureRegistration(std::string passphrase, std::string secondPassphrase) {
  Transaction transaction;
  transaction.type = Enums::Types::SECOND_SIGNATURE_REGISTRATION;
  transaction.fee = Configuration::Fee().get(Enums::Types::SECOND_SIGNATURE_REGISTRATION);

  const auto publicKey = Identities::PublicKey::fromPassphrase(secondPassphrase.c_str());
  transaction.asset.signature.publicKey = publicKey.toString();

  return sign(transaction, std::move(passphrase), secondPassphrase);
}

Transaction Builder::buildDelegateRegistration(std::string username, std::string passphrase,
                                               std::string secondPassphrase) {
  Transaction transaction;
  transaction.type = Enums::Types::DELEGATE_REGISTRATION;
  transaction.fee = Configuration::Fee().get(Enums::Types::DELEGATE_REGISTRATION);
  transaction.asset.delegate.username = std::move(username);

  return sign(transaction, std::move(passphrase), std::move(secondPassphrase));
}

Transaction Builder::buildVote(std::vector<std::string> votes, std::string passphrase, std::string secondPassphrase) {
  Transaction transaction;
  transaction.type = Enums::Types::VOTE;
  transaction.fee = Configuration::Fee().get(Enums::Types::VOTE);
  transaction.asset.votes = std::move(votes);

  const auto recipient =
      Identities::Address::fromPassphrase(passphrase.c_str(), Configuration::Network().get().version());
  transaction.recipientId = recipient.toString();

  return sign(transaction, passphrase, std::move(secondPassphrase));
}

Transaction Builder::buildMultiSignatureRegistration(uint8_t min, uint8_t lifetime, std::vector<std::string> keysgroup,
                                                     std::string passphrase, std::string secondPassphrase) {
  Transaction transaction;
  transaction.type = Enums::Types::MULTI_SIGNATURE_REGISTRATION;
  transaction.fee = (keysgroup.size() + 1) * Configuration::Fee().get(Enums::Types::MULTI_SIGNATURE_REGISTRATION);
  transaction.asset.multiSignature.min = min;
  transaction.asset.multiSignature.lifetime = lifetime;
  transaction.asset.multiSignature.keysgroup = keysgroup;

  const auto recipient =
      Identities::Address::fromPassphrase(passphrase.c_str(), Configuration::Network().get().version());
  transaction.recipientId = recipient.toString();

  return sign(transaction, passphrase, std::move(secondPassphrase));
}

Transaction Builder::sign(Transaction transaction, std::string passphrase, std::string secondPassphrase) {
  transaction.timestamp = static_cast<uint32_t>(Utils::Slot::time(Configuration::Network().get()));
  transaction.sign(passphrase.c_str());

  if (secondPassphrase.length() > 0) {
    transaction.secondSign(secondPassphrase.c_str());
  }

  transaction.id = transaction.getId();

  return transaction;
}

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark
