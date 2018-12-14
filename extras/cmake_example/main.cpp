#include "arkCrypto.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using std::cout;

int main(int argc, char* argv[]) {
  const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
  const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";

  // Message - sign
  Ark::Crypto::Utils::Message message;
  message.sign(text, passphrase);

  cout << "Message\n";
  cout << "\tText: " << text << '\n';
  cout << "\tPassphrase: " << passphrase << '\n';
  cout << "\tJson: " << message.toJson() << '\n';
  cout << '\n';

  // Message - verify
  auto publicKey = PublicKey::fromHex("0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456");
  auto signature = HexToBytes("3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93");

  message = Ark::Crypto::Utils::Message(
    text,
    publicKey,
    signature
  );

  cout << "Message\n";
  cout << "\tJson: " << message.toJson() << '\n';
  cout << "\tVerified: " << std::boolalpha << message.verify() << '\n';
  cout << '\n';

  // Mnemonic
  const auto new_passphrase = Ark::Crypto::Identities::Mnemonic::generate();
  cout << "Generated Mnemonic: " << new_passphrase << '\n';
  cout << '\n';

  // Address - from passphrase
  const uint8_t networkVersion = 0x1E;
  auto address = Address::fromPassphrase(passphrase, networkVersion);
  cout << "Address from passphrase\n";
  cout << "\tPassphrase: " << passphrase << '\n';
  cout << "\tNetwork Version: 0x" << std::hex << static_cast<uint16_t>(networkVersion) << '\n';
  cout << "\tAddress: " << address.toString() << '\n';
  cout << '\n';

  // Address - from publickey
  publicKey = PublicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  address = Address::fromPublicKey(publicKey, networkVersion);
  cout << "Address from public key\n";
  cout << "\tPublic Key: " << publicKey.toString() << '\n';
  cout << "\tAddress: " << address.toString() << '\n';
  cout << '\n';

  // Address - from privatekey
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  address = Address::fromPrivateKey(privateKey, networkVersion);
  cout << "Address from private key\n";
  cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  cout << "\tAddress: " << address.toString() << '\n';
  cout << '\n';

  // Address - validate
  address = Address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
  auto isValidAddress = Address::validate(address, networkVersion);
  cout << "Valid Address\n";
  cout << "\tAddress: " << address.toString() << '\n';
  cout << "\t Valid Address: " << std::boolalpha << isValidAddress << '\n';
  cout << '\n';

  // Private Key - from passphrase
  privateKey = PrivateKey::fromPassphrase(passphrase);
  cout << "Private Key from passprase\n";
  cout << "\tPassphrase: " << passphrase << '\n';
  cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  cout << '\n';

  // Private Key - object from hex
  privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  cout << "Private Key from hex\n";
  cout << "\tHex: 950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021\n";
  cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  cout << '\n';

  // Public Key - from passphrase
  publicKey = PublicKey::fromPassphrase(passphrase);
  cout << "Public Key from passprase\n";
  cout << "\tPassphrase: " << passphrase << '\n';
  cout << "\tPublic Key: " << publicKey.toString() << '\n';
  cout << '\n';

  // Public Key - object from hex
  publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  cout << "Public Key from hex\n";
  cout << "\tHex: 029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4\n";
  cout << "\tPublic Key: " << publicKey.toString() << '\n';
  cout << '\n';

  // WIF - from passphrase
  const uint8_t wifByte = 0xaa;
  auto wif = WIF::fromPassphrase(passphrase, wifByte);
  cout << "WIF from passphrase\n";
  cout << "\tPassphrase: " << passphrase << '\n';
  cout << "\tWIF Byte: 0x" << std::hex << static_cast<uint16_t>(wifByte) << '\n';
  cout << "\tWIF: " << wif.toString() << std::endl;

  return 0;
}
