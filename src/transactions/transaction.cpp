#include "transactions/transaction.h"
#include "bcl/Sha256.hpp"
#include "enums/types.h"
#include "helpers/crypto.h"
#include "helpers/crypto_helpers.h"
#include "helpers/json.h"
#include "identities/address.h"
#include "identities/privatekey.h"

#include <sstream>

using namespace Ark::Crypto::Identities;

Ark::Crypto::Transactions::Transaction::Transaction() {}

std::string Ark::Crypto::Transactions::Transaction::getId() const {
  auto bytes = this->toBytes(false, false);
  const auto shaHash = Sha256::getHash(&bytes[0], bytes.size());
  memcpy(&bytes[0], shaHash.value, shaHash.HASH_LEN);
  return BytesToHex(&bytes[0], &bytes[0] + shaHash.HASH_LEN);
}

std::string Ark::Crypto::Transactions::Transaction::sign(const char* passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
  this->senderPublicKey = Identities::PublicKey::fromPrivateKey(privateKey).toString();

  const auto bytes = this->toBytes();
  const auto hash = Sha256::getHash(&bytes[0], bytes.size());

  std::vector<uint8_t> buffer;
  cryptoSign(hash, privateKey, buffer);

  this->signature = BytesToHex(buffer.begin(), buffer.end());
  return this->signature;
}

std::string Ark::Crypto::Transactions::Transaction::secondSign(const char* passphrase) {
  PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
  const auto bytes = this->toBytes(false);
  const auto hash = Sha256::getHash(&bytes[0], bytes.size());

  std::vector<uint8_t> buffer;
  cryptoSign(hash, privateKey, buffer);

  this->secondSignature = BytesToHex(buffer.begin(), buffer.end());
  return this->secondSignature;
}

bool Ark::Crypto::Transactions::Transaction::verify() const {
  return this->internalVerify(this->senderPublicKey, this->toBytes(), this->signature);
}

bool Ark::Crypto::Transactions::Transaction::secondVerify(const char* secondPublicKey) const {
  return this->internalVerify(secondPublicKey, this->toBytes(false), this->secondSignature);
}

bool Ark::Crypto::Transactions::Transaction::internalVerify(
    std::string publicKey,
    std::vector<uint8_t> bytes,
    std::string signature) const {
  const auto hash = Sha256::getHash(&bytes[0], bytes.size());
  const auto key = Identities::PublicKey::fromHex(publicKey.c_str());
  auto signatureBytes = HexToBytes(signature.c_str());
  return cryptoVerify(key, hash, signatureBytes);
}

std::vector<uint8_t> Ark::Crypto::Transactions::Transaction::toBytes(
    bool skipSignature,
    bool skipSecondSignature) const {
  std::vector<uint8_t> bytes;

  pack(bytes, this->type);
  pack(bytes, this->timestamp);

  const auto senderKeyBytes = HexToBytes(this->senderPublicKey.c_str());
  bytes.insert(std::end(bytes), std::begin(senderKeyBytes), std::end(senderKeyBytes));

  const auto skipRecipientId = type
    == Enums::Types::SECOND_SIGNATURE_REGISTRATION
    || type == Enums::Types::MULTI_SIGNATURE_REGISTRATION;

  if (!this->recipientId.empty() && !skipRecipientId) {
    std::vector<std::uint8_t> recipientIdBytes = Address::bytesFromBase58Check(this->recipientId.c_str());
    bytes.insert(std::end(bytes), std::begin(recipientIdBytes), std::end(recipientIdBytes));
  } else {
    std::vector<uint8_t> filler(21, 0);
    bytes.insert(std::end(bytes), std::begin(filler), std::end(filler));
  }

  if (!this->vendorField.empty()) {
    bytes.insert(std::end(bytes), std::begin(this->vendorField), std::end(this->vendorField));

    size_t diff = 64 - vendorField.length();
    if (diff > 0) {
      std::vector<uint8_t> filler(diff, 0);
      bytes.insert(std::end(bytes), std::begin(filler), std::end(filler));
    }

  } else {
    std::vector<uint8_t> filler(64, 0);
    bytes.insert(std::end(bytes), std::begin(filler), std::end(filler));
  }

  pack(bytes, this->amount);
  pack(bytes, this->fee);

  if (type == Enums::Types::SECOND_SIGNATURE_REGISTRATION) {
    const auto publicKeyBytes = HexToBytes(this->asset.signature.publicKey.c_str());
    bytes.insert(std::end(bytes), std::begin(publicKeyBytes), std::end(publicKeyBytes));

  } else if (type == Enums::Types::DELEGATE_REGISTRATION) {
    bytes.insert(std::end(bytes), std::begin(this->asset.delegate.username), std::end(this->asset.delegate.username));

  } else if (type == Enums::Types::VOTE) {
    const auto joined = join(this->asset.votes);
    bytes.insert(std::end(bytes), std::begin(joined), std::end(joined));

  } else if (type == Enums::Types::MULTI_SIGNATURE_REGISTRATION) {
    pack(bytes, this->asset.multiSignature.min);
    pack(bytes, this->asset.multiSignature.lifetime);
    const auto joined = join(this->asset.multiSignature.keysgroup);
    bytes.insert(std::end(bytes), std::begin(joined), std::end(joined));
  }

  if (!skipSignature && !this->signature.empty()) {
    const auto signatureBytes = HexToBytes(this->signature.c_str());
    bytes.insert(std::end(bytes), std::begin(signatureBytes), std::end(signatureBytes));
  }

  if (!skipSecondSignature && !this->secondSignature.empty()) {
    const auto secondSignatureBytes = HexToBytes(this->secondSignature.c_str());
    bytes.insert(std::end(bytes), std::begin(secondSignatureBytes), std::end(secondSignatureBytes));
  }

  return bytes;
}

std::vector<std::pair<const char *const, std::string>> Ark::Crypto::Transactions::Transaction::toArray() {
  //  buffers for variable and non-string type-values.
  std::stringstream amount, assetName, assetValue, fee, signatures, timestamp;
  char network[8], type[8], version[8];

  //  Amount
  amount << this->amount;

  //  Asset
  if (this->type == 0) {  //  Transfer
    //do nothing
  } else if (this->type == 1) { //  Second Signature Registration

    assetName << "publicKey";
    assetValue << this->asset.signature.publicKey;

  } else if (this->type == 2) { //  Delegate Registration

    assetName << "username";
    assetValue << this->asset.delegate.username;

  }else if (this->type == 3) {  //  Vote

    assetName << "votes";
    for (unsigned int i = 0; i < this->asset.votes.size(); ++i) {
      assetValue << this->asset.votes[i];
      if (i < this->asset.votes.size() - 1) {
        assetValue << ",";
      }
    }

  // } else if (this->type == 4) {  //  Multisignature Registration
  //   //  TODO
  // } else if (this->type == 5) {  //  IPFS
  //   //  TBD
  // } else if (this->type == 6) {  //  Timelock Registration
  //   //  TBD
  // } else if (this->type == 7) {  //  Multi-Payment
  //   //  TBD
  // } else if (this->type == 8) {  //  Delegate Resignation
  //   //  TBD
  };

  //  Fee
  fee << this->fee;

  //  Signatures
  for (unsigned int i = 0; i < this->signatures.size(); ++i) {
    signatures << this->signatures[i];
    if (i < this->signatures.size() - 1) {
      signatures << ",";
    }
  }

  //  Network
  sprintf(network, "%d", this->network);

  //  Timestamp
  timestamp << this->timestamp;

  //  Type
  sprintf(type, "%d", this->type);

  //  Version
  sprintf(version, "%d", this->version);

  return {
    {"amount", amount.str()},
    {assetName.str().c_str(), assetValue.str()},
    {"fee", fee.str()},
    {"id", this->id},
    {"network", network},
    {"recipientId", this->recipientId},
    {"secondSignature", this->secondSignature},
    {"senderPublicKey", this->senderPublicKey},
    {"signature", this->signature},
    {"signatures", signatures.str()},
    {"signSignature", this->signSignature},
    {"timestamp", timestamp.str()},
    {"type", type},
    {"vendorField", this->vendorField},
    {"version", version}
  };
}

std::string Ark::Crypto::Transactions::Transaction::toJson() {
  std::vector<std::pair<const char *const, std::string>>  txArray = this->toArray();

  const size_t capacity = JSON_OBJECT_SIZE(15);
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.createObject();

  //  Amount
  root[txArray[0].first] = txArray[0].second;

  //  Asset
  if (this->type == 0) {  //  Transfer
    //do nothing
  } else if (this->type == 1) { //  Second Signature Registration

    JsonObject& asset = root.createNestedObject("asset");
    JsonObject& signature = asset.createNestedObject("signature");
    signature[txArray[1].first] = txArray[1].second;

  } else if (this->type == 2) { //  Delegate Registration

    JsonObject& asset = root.createNestedObject("asset"); 
    JsonObject& delegate = asset.createNestedObject("delegate");
    delegate[txArray[1].first] = txArray[1].second;

  }else if (this->type == 3) {  //  Vote

    JsonObject& asset = root.createNestedObject("asset"); 
    JsonArray& votes = asset.createNestedArray(txArray[1].first);

    std::string::size_type lastPos = txArray[1].second.find_first_not_of(",", 0);
    std::string::size_type pos = txArray[1].second.find_first_of(",", lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
      votes.add(txArray[1].second.substr(lastPos, pos - lastPos));
      lastPos = txArray[1].second.find_first_not_of(",", pos);
      pos = txArray[1].second.find_first_of(",", lastPos);
    }

  // } else if (this->type == 4) {  //  Multisignature Registration
  //   //  TODO
  // } else if (this->type == 5) {  //  IPFS
  //   //  TBD
  // } else if (this->type == 6) {  //  Timelock Registration
  //   //  TBD
  // } else if (this->type == 7) {  //  Multi-Payment
  //   //  TBD
  // } else if (this->type == 8) {  //  Delegate Resignation
  //   //  TBD
  };

  //  Fee
  root[txArray[2].first] = txArray[2].second;

  //  Id
  root[txArray[3].first] = txArray[3].second;

  //  Network
  root[txArray[4].first] = txArray[4].second;

  //  RecipientId
  root[txArray[5].first] = txArray[5].second;

  //  SecondSignature
  if (std::strlen(txArray[6].second.c_str()) > 0) {
    root[txArray[6].first] = txArray[6].second;
  }

  //  SenderPublicKey
  root[txArray[7].first] = txArray[7].second;

  //  Signature
  root[txArray[8].first] = txArray[8].second;

  //  Signatures
  if (this->signatures.size() > 0) {
    JsonArray& signatures = root.createNestedArray("signatures");
    std::string::size_type lastPos = txArray[9].second.find_first_not_of(",", 0);
    std::string::size_type pos = txArray[9].second.find_first_of(",", lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
      signatures.add(txArray[9].second.substr(lastPos, pos - lastPos));
      lastPos = txArray[9].second.find_first_not_of(",", pos);
      pos = txArray[9].second.find_first_of(",", lastPos);
    }
  }

  //  SignSignature
  if (std::strlen(txArray[10].second.c_str()) > 0) {
    root[txArray[10].first] = txArray[10].second;
  }

  //  Timestamp
  root[txArray[11].first] = txArray[11].second;

  //  Type
  root[txArray[12].first] = txArray[12].second;

  //  VendorField
  if (std::strlen(txArray[13].second.c_str()) > 0) {
    root[txArray[13].first] = txArray[13].second;
  }

  //  Version
  if (txArray[14].second != "0") {
    root[txArray[14].first] = txArray[14].second;
  }

  char jsonChar[root.measureLength() + 1];
  root.printTo((char*)jsonChar, sizeof(jsonChar));

  return jsonChar;
}
