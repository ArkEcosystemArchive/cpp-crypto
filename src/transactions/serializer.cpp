#include "serializer.h"
#include "helpers/helpers.h"
#include "identities/address.h"
#include "configuration/network.h"
#include "enums/types.h"

namespace Ark {
namespace Crypto {
namespace Transactions {

// TODO: remove class ?
Serializer::Serializer(const Transaction& transaction) : _transaction(transaction)
{

}

std::string Serializer::serialize()
{
    std::vector<uint8_t> bytes;
    bytes.push_back(0xff);
    bytes.push_back(_transaction.version > 0 ? _transaction.version : 0x01);
    bytes.push_back(_transaction.network > 0 ? _transaction.network : Configuration::Network().get().version());
    bytes.push_back(_transaction.type);

    pack(bytes, _transaction.timestamp);

    std::vector<uint8_t> senderPublicKeyBytes = HexToBytes(_transaction.senderPublicKey.c_str());
    bytes.insert(bytes.end(), senderPublicKeyBytes.begin(), senderPublicKeyBytes.end());

    pack(bytes, _transaction.fee);

    serializeVendorField(bytes);
    serializeType(bytes);
    serializeSignatures(bytes);

    return BytesToHex(bytes);
}

void Serializer::serializeVendorField(std::vector<uint8_t>& bytes)
{
    if (_transaction.vendorField.length() > 0) {
        uint8_t vendorFieldLength = static_cast<uint8_t>(_transaction.vendorField.length());
        bytes.push_back(vendorFieldLength);
        bytes.insert(bytes.end(), std::begin(_transaction.vendorField), std::end(_transaction.vendorField));

    } else if (_transaction.vendorFieldHex.length() > 0) {
        uint8_t vendorFieldHexLength = static_cast<uint8_t>(_transaction.vendorFieldHex.length() / 2);
        bytes.push_back(vendorFieldHexLength);
        bytes.insert(bytes.end(), std::begin(_transaction.vendorFieldHex), std::end(_transaction.vendorFieldHex));
    } else {
        bytes.push_back(0x00);
    }
}

void Serializer::serializeType(std::vector<uint8_t>& bytes)
{
    switch (_transaction.type) {
    case Enums::Types::TRANSFER: {
        serializeTransfer(bytes);
        break;
    }
    case Enums::Types::SECOND_SIGNATURE_REGISTRATION: {
        serializeSecondSignatureRegistration(bytes);
        break;
    }
    case Enums::Types::DELEGATE_REGISTRATION: {
        serializeDelegateRegistration(bytes);
        break;
    }
    case Enums::Types::VOTE: {
        serializeVote(bytes);
        break;
    }
    case Enums::Types::MULTI_SIGNATURE_REGISTRATION: {
        serializeMultiSignatureRegistration(bytes);
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

void Serializer::serializeTransfer(std::vector<uint8_t>& bytes)
{
    pack(bytes, _transaction.amount);
    pack(bytes, _transaction.expiration);

    std::vector<uint8_t> recipientIdBytes = Identities::Address::bytesFromBase58Check(_transaction.recipientId.c_str());
    bytes.insert(bytes.end(), recipientIdBytes.begin(), recipientIdBytes.end());
}

void Serializer::serializeSecondSignatureRegistration(std::vector<uint8_t>& bytes)
{
    std::vector<uint8_t> publicKeyBytes = HexToBytes(_transaction.asset.signature.publicKey.c_str());
    bytes.insert(bytes.end(), publicKeyBytes.begin(), publicKeyBytes.end());
}

void Serializer::serializeDelegateRegistration(std::vector<uint8_t>& bytes)
{
    const auto username = _transaction.asset.delegate.username;
    bytes.push_back(static_cast<uint8_t>(username.size()));
    bytes.insert(bytes.end(), username.begin(), username.end());
}

void Serializer::serializeVote(std::vector<uint8_t>& bytes)
{
    std::string votes;
    for (uint8_t i = 0; i < _transaction.asset.votes.size(); i++) {
        std::string vote = _transaction.asset.votes[i];
        votes += (vote[0] == '+' ? "01" : "00") + vote.substr(1);
    }

    std::vector<uint8_t> voteBytes = HexToBytes(votes.c_str());
    bytes.push_back(static_cast<uint8_t>(_transaction.asset.votes.size()));
    bytes.insert(bytes.end(), voteBytes.begin(), voteBytes.end());
}

void Serializer::serializeMultiSignatureRegistration(std::vector<uint8_t>& bytes)
{
    std::string keysgroup;
    if (_transaction.version == 1) {
        for (uint8_t i = 0; i < _transaction.asset.multiSignature.keysgroup.size(); i++) {
            keysgroup += _transaction.asset.multiSignature.keysgroup[i].substr(1);
        }
    } else {
        keysgroup = join(_transaction.asset.multiSignature.keysgroup);
    }

    bytes.push_back(_transaction.asset.multiSignature.min);
    bytes.push_back(static_cast<uint8_t>(_transaction.asset.multiSignature.keysgroup.size()));
    bytes.push_back(_transaction.asset.multiSignature.lifetime);

    std::vector<uint8_t> keysgroupBytes = HexToBytes(keysgroup.c_str());
    bytes.insert(bytes.end(), keysgroupBytes.begin(), keysgroupBytes.end());
}

void Serializer::serializeSignatures(std::vector<uint8_t>& bytes)
{
    if (_transaction.signature.length() > 0) {
        std::vector<uint8_t> signatureBytes = HexToBytes(_transaction.signature.c_str());
        bytes.insert(bytes.end(), signatureBytes.begin(), signatureBytes.end());
    }

    if (_transaction.secondSignature.length() > 0) {
        std::vector<uint8_t> secondSignatureBytes = HexToBytes(_transaction.secondSignature.c_str());
        bytes.insert(bytes.end(), secondSignatureBytes.begin(), secondSignatureBytes.end());
    } else if (_transaction.signSignature.length() > 0) {
        std::vector<uint8_t> signSignatureBytes = HexToBytes(_transaction.signSignature.c_str());
        bytes.insert(bytes.end(), signSignatureBytes.begin(), signSignatureBytes.end());
    }

    if (_transaction.signatures.size() > 0) {
        bytes.push_back(0xff);
        std::string joined = join(_transaction.signatures);
        for (uint8_t i = 0; i < _transaction.signatures.size(); i++) {
            std::vector<uint8_t> signatureBytes = HexToBytes(_transaction.signatures[i].c_str());
            bytes.insert(bytes.end(), std::begin(signatureBytes), std::end(signatureBytes));
        }
    }
}


}
}
}



