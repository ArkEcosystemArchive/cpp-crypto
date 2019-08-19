/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include <arkCrypto.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "utils/hex.hpp"

int main(int argc, char* argv[]) {
  const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
  const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";

  // Message - sign
  Ark::Crypto::Utils::Message message;
  message.sign(text, passphrase);

  std::cout << "Message\n";
  std::cout << "\tText: " << text << '\n';
  std::cout << "\tPassphrase: " << passphrase << '\n';
  std::cout << "\tJson: " << message.toJson() << '\n';
  std::cout << '\n';

  // Message - verify
  auto publicKey = PublicKey::fromHex("0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456");
  auto signature = HexToBytes("3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93");

  message = Ark::Crypto::Utils::Message(
    text,
    publicKey,
    signature
  );

  std::cout << "Message\n";
  std::cout << "\tJson: " << message.toJson() << '\n';
  std::cout << "\tVerified: " << std::boolalpha << message.verify() << '\n';
  std::cout << '\n';

  // Address - from passphrase
  const uint8_t networkVersion = 0x1E;
  auto address = Address::fromPassphrase(passphrase, networkVersion);
  std::cout << "Address from passphrase\n";
  std::cout << "\tPassphrase: " << passphrase << '\n';
  std::cout << "\tNetwork Version: 0x" << std::hex << static_cast<uint16_t>(networkVersion) << '\n';
  std::cout << "\tAddress: " << address.toString() << '\n';
  std::cout << '\n';

  // Address - from publickey
  publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  address = Address::fromPublicKey(publicKey.toBytes().data(), networkVersion);
  std::cout << "Address from public key\n";
  std::cout << "\tPublic Key: " << publicKey.toString() << '\n';
  std::cout << "\tAddress: " << address.toString() << '\n';
  std::cout << '\n';

  // Address - from privatekey
  PrivateKey privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  address = Address::fromPrivateKey(privateKey.toBytes().data(), networkVersion);
  std::cout << "Address from private key\n";
  std::cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  std::cout << "\tAddress: " << address.toString() << '\n';
  std::cout << '\n';

  // Address - validate
  address = Address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
  auto isValidAddress = Address::validate(address, networkVersion);
  std::cout << "Valid Address\n";
  std::cout << "\tAddress: " << address.toString() << '\n';
  std::cout << "\t Valid Address: " << std::boolalpha << isValidAddress << '\n';
  std::cout << '\n';

  // Private Key - from passphrase
  privateKey = PrivateKey::fromPassphrase(passphrase);
  std::cout << "Private Key from passprase\n";
  std::cout << "\tPassphrase: " << passphrase << '\n';
  std::cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  std::cout << '\n';

  // Private Key - object from hex
  privateKey = std::move(PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021"));
  std::cout << "Private Key from hex\n";
  std::cout << "\tHex: 950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021\n";
  std::cout << "\tPrivate Key: " << privateKey.toString() << '\n';
  std::cout << '\n';

  // Public Key - from passphrase
  publicKey = PublicKey::fromPassphrase(passphrase);
  std::cout << "Public Key from passprase\n";
  std::cout << "\tPassphrase: " << passphrase << '\n';
  std::cout << "\tPublic Key: " << publicKey.toString() << '\n';
  std::cout << '\n';

  // Public Key - object from hex
  publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  std::cout << "Public Key from hex\n";
  std::cout << "\tHex: 029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4\n";
  std::cout << "\tPublic Key: " << publicKey.toString() << '\n';
  std::cout << '\n';

  // WIF - from passphrase
  const uint8_t wifByte = 0xaa;
  auto wif = Wif::fromPassphrase(passphrase, wifByte);
  std::cout << "WIF from passphrase\n";
  std::cout << "\tPassphrase: " << passphrase << '\n';
  std::cout << "\tWIF Byte: 0x" << std::hex << static_cast<uint16_t>(wifByte) << '\n';
  std::cout << "\tWIF: " << wif.toString() << std::endl;

  return 0;
}