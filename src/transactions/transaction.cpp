#include "transactions/transaction.h"
#include "bcl/Sha256.hpp"
#include "enums/types.h"
#include "helpers/crypto.h"
#include "helpers/crypto_helpers.h"
#include "helpers/json.h"
#include "identities/address.h"
#include "identities/privatekey.h"

#include <map>

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
  if (bytes.empty()) { return false; };

  const auto hash = Sha256::getHash(&bytes[0], bytes.size());
  const auto key = Identities::PublicKey::fromHex(publicKey.c_str());
  auto signatureBytes = HexToBytes(signature.c_str());
  return cryptoVerify(key, hash, signatureBytes);
}

std::vector<uint8_t> Ark::Crypto::Transactions::Transaction::toBytes(
    bool skipSignature,
    bool skipSecondSignature) const {
  std::vector<uint8_t> bytes;

  if (this->type == 0 && amount < 1ull) { return bytes; };

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

  if (!this->vendorField.empty() && vendorField.length() <= 255) {
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

std::map<std::string, std::string> Ark::Crypto::Transactions::Transaction::toArray() {
  //  buffers for variable and non-string type-values.
  char amount[24],
      assetName[16],
      assetValue[512],
      fee[24],
      network[8],
      signatures[512],
      timestamp[36],
      type[8],
      version[8];

  //  Amount
  sprintf(amount, "%llu", this->amount);

  //  Asset
  if (this->type == 0) {  //  Transfer
    //do nothing
  } else if (this->type == 1) { //  Second Signature Registration

    strcpy(assetName, "publicKey");
    strcpy(assetValue, this->asset.signature.publicKey.c_str());

  } else if (this->type == 2) { //  Delegate Registration

    strcpy(assetName, "username");
    strcpy(assetValue, this->asset.delegate.username.c_str());

  } else if (this->type == 3) {  //  Vote

    strcpy(assetName, "votes");
    strcpy(assetValue, "");
    for (unsigned int i = 0; i < this->asset.votes.size(); ++i) {
      strcat(assetValue, this->asset.votes[i].c_str());

      if (i < this->asset.votes.size() - 1) {
        strcat(assetValue, ",");
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
  // fee << this->fee;
  sprintf(fee, "%llu",  this->fee);

  //  Signatures
  strcpy(signatures, "");
  for (unsigned int i = 0; i < this->signatures.size(); ++i) {
    strcat(signatures, this->signatures[i].c_str());
    if (i < this->signatures.size() - 1) {
      strcpy(signatures, ",");
    }
  }

  //  Network
  sprintf(network, "%d", this->network);

  //  Timestamp
  sprintf(timestamp, "%d", this->timestamp);

  //  Type
  sprintf(type, "%d", this->type);

  //  Version
  sprintf(version, "%d", this->version);

  return {
    { "amount", amount },
    { assetName, assetValue },
    { "fee", fee },
    { "id", this->id },
    { "network", network },
    { "recipientId", this->recipientId },
    { "secondSignature", this->secondSignature },
    { "senderPublicKey", this->senderPublicKey },
    { "signature", this->signature },
    { "signatures", signatures },
    { "signSignature", this->signSignature },
    { "timestamp", timestamp },
    { "type", type },
    { "vendorField", this->vendorField },
    { "version", version }
  };
}

std::string Ark::Crypto::Transactions::Transaction::toJson() {
  std::map<std::string, std::string> txArray = this->toArray();

  const size_t docCapacity = 900;
  DynamicJsonDocument doc(docCapacity);

  //  Amount
  doc["amount"] = txArray["amount"];

  //  Asset
  if (this->type == 0) {  //  Transfer
    //do nothing
  } else if (this->type == 1) { //  Second Signature Registration

    JsonObject tAsset = doc.createNestedObject("asset");
    JsonObject signature = tAsset.createNestedObject("signature");
    signature["publicKey"] = txArray["publicKey"];

  } else if (this->type == 2) { //  Delegate Registration

    JsonObject dAsset = doc.createNestedObject("asset");
    JsonObject delegate = dAsset.createNestedObject("delegate");
    delegate["username"] = txArray["username"];

  }else if (this->type == 3) {  //  Vote

    JsonObject vAsset = doc.createNestedObject("asset");
    JsonArray votes = vAsset.createNestedArray("votes");

    std::string::size_type lastPos = txArray["votes"].find_first_not_of(",", 0);
    std::string::size_type pos = txArray["votes"].find_first_of(",", lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
      votes.add(txArray["votes"].substr(lastPos, pos - lastPos));
      lastPos = txArray["votes"].find_first_not_of(",", pos);
      pos = txArray["votes"].find_first_of(",", lastPos);
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
  doc["fee"] = txArray["fee"];

  //  Id
  doc["id"] = txArray["id"];

  //  Network
  if (txArray["network"] != "0") {
    doc["network"] = txArray["network"];
  }

  //  RecipientId
  doc["recipientId"] = txArray["recipientId"];

  //  SecondSignature
  if (std::strlen(txArray["secondSignature"].c_str()) > 0) {
    doc["secondSignature"] = txArray["secondSignature"];
  }

  //  SenderPublicKey
  doc["senderPublicKey"] = txArray["senderPublicKey"];

  //  Signature
  doc["signature"] = txArray["signature"];

  //  Signatures
  if (this->signatures.size() > 0) {
    JsonArray signatures = doc.createNestedArray("signatures");
    std::string::size_type lastPos = txArray["signatures"].find_first_not_of(",", 0);
    std::string::size_type pos = txArray["signatures"].find_first_of(",", lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
      signatures.add(txArray["signatures"].substr(lastPos, pos - lastPos));
      lastPos = txArray["signatures"].find_first_not_of(",", pos);
      pos = txArray["signatures"].find_first_of(",", lastPos);
    }
  }

  //  SignSignature
  if (std::strlen(txArray["signSignature"].c_str()) > 0) {
    doc["signSignature"] = txArray["signSignature"];
  }

  //  Timestamp
  doc["timestamp"] = txArray["timestamp"];

  //  Type
  doc["type"] = txArray["type"];

  //  VendorField
  if (std::strlen(txArray["vendorField"].c_str()) > 0) {
    doc["vendorField"] = txArray["vendorField"];
  }

  //  Version
  if (txArray["version"] != "0") {
    doc["version"] = txArray["version"];
  }

  char jsonChar[docCapacity];
  serializeJson(doc, jsonChar, docCapacity);

  return jsonChar;
}
