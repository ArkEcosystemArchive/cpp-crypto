#include "transactions/deserializer.h"
#include "bcl/Sha256.hpp"
#include "enums/types.h"
#include "helpers/crypto.h"
#include "identities/address.h"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace Ark {
namespace Crypto {
namespace Transactions {

Deserializer::Deserializer(const std::string& serialized)
    : _serialized(serialized), _binary(HexToBytes(serialized.c_str())), _assetOffset(0) {}

Transaction Deserializer::deserialize() {
  Transaction transaction;

  deserializeHeader(transaction);
  deserializeType(transaction);
  deserializeSignatures(transaction);

  if (transaction.version == 1) {
    handleVersionOne(transaction);
  }

  return transaction;
}

void Deserializer::deserializeHeader(Transaction& transaction) {
  unpack(&transaction.header, &this->_binary[0]);     // 1 Byte
  unpack(&transaction.version, &this->_binary[1]);    // 1 Byte
  unpack(&transaction.network, &this->_binary[2]);    // 1 Byte
  unpack(&transaction.type, &this->_binary[3]);       // 1 Byte
  unpack(&transaction.timestamp, &this->_binary[4]);  // 4 Byte

  // 33 Byte
  transaction.senderPublicKey = BytesToHex(this->_binary.begin() + 8, this->_binary.begin() + 33 + 8);

  unpack(&transaction.fee, &this->_binary[41]);  // 8 Byte

  uint8_t vendorFieldOffset = (41 + 8 + 1) * 2;
  uint8_t vendorFieldLength = 0;
  unpack(&vendorFieldLength, &this->_binary[49]);  // 1 Byte
  if (vendorFieldLength > 0) {
    transaction.vendorFieldHex = this->_serialized.substr(vendorFieldOffset, vendorFieldLength * 2);
  }

  _assetOffset = vendorFieldOffset + vendorFieldLength * 2;
}

void Deserializer::deserializeType(Transaction& transaction) {
  switch (transaction.type) {
    case Enums::Types::TRANSFER: {
      deserializeTransfer(transaction);
      break;
    }
    case Enums::Types::SECOND_SIGNATURE_REGISTRATION: {
      deserializeSecondSignatureRegistration(transaction);
      break;
    }
    case Enums::Types::DELEGATE_REGISTRATION: {
      deserializeDelegateRegistration(transaction);
      break;
    }
    case Enums::Types::VOTE: {
      deserializeVote(transaction);
      break;
    }
    case Enums::Types::MULTI_SIGNATURE_REGISTRATION: {
      deserializeMultiSignatureRegistration(transaction);
      break;
    }
    case Enums::Types::IPFS: {
      break;
    }
    case Enums::Types::TIMELOCK_TRANSFER: {
      break;
    }
    case Enums::Types::MULTI_PAYMENT: {
      break;
    }
    case Enums::Types::DELEGATE_RESIGNATION: {
      break;
    }
  }
}

void Deserializer::deserializeTransfer(Transaction& transaction) {
  unpack(&transaction.amount, &this->_binary[_assetOffset / 2]);
  unpack(&transaction.expiration, &this->_binary[_assetOffset / 2 + 8]);
  transaction.recipientId = Identities::Address::base58encode(&this->_binary[(_assetOffset / 2) + 12]);

  _assetOffset += (8 + 4 + 21) * 2;
}

void Deserializer::deserializeSecondSignatureRegistration(Transaction& transaction) {
  transaction.asset.signature.publicKey = this->_serialized.substr(_assetOffset, 66);
  _assetOffset += 66;
}

void Deserializer::deserializeDelegateRegistration(Transaction& transaction) {
  uint8_t usernameLength = 0;
  unpack(&usernameLength, &this->_binary[_assetOffset / 2]);
  usernameLength &= 0xff;

  std::string username = this->_serialized.substr((_assetOffset / 2 + 1) * 2, usernameLength * 2);
  std::vector<uint8_t> bytes = HexToBytes(username.c_str());
  transaction.asset.delegate.username = std::string(bytes.begin(), bytes.end());

  _assetOffset += (usernameLength + 1) * 2;
}

void Deserializer::deserializeVote(Transaction& transaction) {
  uint8_t voteLength = 0;
  unpack(&voteLength, &this->_binary[_assetOffset / 2]);
  voteLength &= 0xff;

  for (uint8_t i = 0; i < voteLength; i++) {
    std::string vote = this->_serialized.substr(_assetOffset + 2 + i * 2 * 32, 68);
    vote = (vote[1] == '1' ? "+" : "-") + vote.substr(2);
    transaction.asset.votes.push_back(vote);
  }

  _assetOffset += 2 + voteLength * 34 * 2;
}

void Deserializer::deserializeMultiSignatureRegistration(Transaction& transaction) {
  uint8_t min = 0;
  unpack(&min, &this->_binary[_assetOffset / 2]);
  min &= 0xff;

  uint8_t count = 0;
  unpack(&count, &this->_binary[_assetOffset / 2 + 1]);
  count &= 0xff;

  uint8_t lifetime = 0;
  unpack(&lifetime, &this->_binary[_assetOffset / 2 + 2]);
  lifetime &= 0xff;

  transaction.asset.multiSignature.min = min;
  transaction.asset.multiSignature.lifetime = lifetime;

  for (uint8_t i = 0; i < count; i++) {
    std::string key = this->_serialized.substr(_assetOffset + 6 + i * 66, 66);
    transaction.asset.multiSignature.keysgroup.push_back(key);
  }

  _assetOffset += 6 + count * 66;
}

static uint8_t parseSignatureLength(const std::string& hex) {
  assert(hex.length() <= 2);
  unsigned int length;
  sscanf(hex.c_str(), "%x", &length);
  return static_cast<uint8_t>(length + 2);
}

void Deserializer::deserializeSignatures(Transaction& transaction) {
  std::string signature = this->_serialized.substr(_assetOffset);

  size_t multiSignatureOffset = 0;
  if (!signature.empty()) {
    size_t signatureLength = parseSignatureLength(signature.substr(2, 2));
    transaction.signature = this->_serialized.substr(_assetOffset, signatureLength * 2);
    multiSignatureOffset += signatureLength * 2;
    transaction.secondSignature = this->_serialized.substr((_assetOffset + signatureLength * 2));

    if (!transaction.secondSignature.empty()) {
      if (transaction.secondSignature.substr(0, 2) == "ff") {
        transaction.secondSignature = "";
      } else {
        size_t secondSignatureLength = parseSignatureLength(transaction.secondSignature.substr(2, 2));
        transaction.secondSignature = transaction.secondSignature.substr(0, secondSignatureLength * 2);
        multiSignatureOffset += secondSignatureLength * 2;
      }
    }

    std::string signatures = this->_serialized.substr(_assetOffset + multiSignatureOffset);
    if (!signatures.empty() && signatures.substr(0, 2) == "ff") {
      signatures = signatures.substr(2);

      while (!signatures.empty()) {
        size_t multiSignatureLength = parseSignatureLength(signatures.substr(2, 2));
        if (multiSignatureLength > 0) {
          transaction.signatures.push_back(signatures.substr(0, multiSignatureLength * 2));
        }

        signatures = signatures.substr(multiSignatureLength * 2);
      }
    }
  }
}

void Deserializer::handleVersionOne(Transaction& transaction) {
  transaction.signSignature = transaction.secondSignature;

  if (transaction.type == Enums::Types::VOTE) {
    const auto publicKey = Identities::PublicKey::fromHex(transaction.senderPublicKey.c_str());
    const auto address = Identities::Address::fromPublicKey(publicKey, transaction.network);
    transaction.recipientId = address.toString();
  }

  if (transaction.type == Enums::Types::MULTI_SIGNATURE_REGISTRATION) {
    std::for_each(transaction.asset.multiSignature.keysgroup.begin(), transaction.asset.multiSignature.keysgroup.end(),
                  [](std::string& key) { key.insert(0, "+"); });
  }

  if (!transaction.vendorFieldHex.empty()) {
    const auto bytes = HexToBytes(transaction.vendorFieldHex.c_str());
    transaction.vendorField = std::string(bytes.begin(), bytes.end());
  }

  if (transaction.id.empty()) {
    transaction.id = transaction.getId();
  }

  if (transaction.type == Enums::Types::SECOND_SIGNATURE_REGISTRATION ||
      transaction.type == Enums::Types::MULTI_SIGNATURE_REGISTRATION) {
    const auto publicKey = Identities::PublicKey::fromHex(transaction.senderPublicKey.c_str());
    const auto address = Identities::Address::fromPublicKey(publicKey, transaction.network);
    transaction.recipientId = address.toString();
  }
}

}  // namespace Transactions
}  // namespace Crypto
}  // namespace Ark
