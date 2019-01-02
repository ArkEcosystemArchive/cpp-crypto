#include "arkCrypto.h"

#include <string>
#include <vector>
#include <cstdint>

#include <arduino.h>

void setup() {
  Serial.begin(115200);

  while (!Serial) { delay(100); };
  // ^for the Arduino Leonardo/Micro only
}

void loop() {
  const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
  const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";

  // Message - sign
  Ark::Crypto::Utils::Message message;
  message.sign(text, passphrase);

  Serial.println("Message");
  Serial.print("\tText: "); Serial.print(text); Serial.println();
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tJson: "); Serial.print(message.toJson().c_str()); Serial.println();
  Serial.println();

  // Message - verify
  auto publicKey = PublicKey::fromHex("0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456");
  auto signature = HexToBytes("3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93");

  message = Ark::Crypto::Utils::Message(
    text,
    publicKey,
    signature
  );

  Serial.println("Message");
  Serial.print("\tJson: "); Serial.print(message.toJson().c_str()); Serial.println();
  Serial.print("\tVerified: "); Serial.print(message.verify()); Serial.println();
  Serial.println();

  // Mnemonic
  const auto new_passphrase = Ark::Crypto::Identities::Mnemonic::generate();
  Serial.print("Generated Mnemonic: "); Serial.print(new_passphrase.c_str()); Serial.println();
  Serial.println();

  // Address - from passphrase
  const uint8_t networkVersion = 0x1E;
  auto address = Address::fromPassphrase(passphrase, networkVersion);
  Serial.println("Address from passphrase");
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tNetwork Version: 0x"); Serial.print(static_cast<uint16_t>(networkVersion)); Serial.println();
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.println();

  // Address - from publickey
  publicKey = PublicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  address = Address::fromPublicKey(publicKey, networkVersion);
  Serial.println("Address from public key");
  Serial.print("\tPublic Key: "); Serial.print(publicKey.toString().c_str()); Serial.println();
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.println();

  // Address - from privatekey
  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  address = Address::fromPrivateKey(privateKey, networkVersion);
  Serial.println("Address from private key");
  Serial.print("\tPrivate Key: "); Serial.print(privateKey.toString().c_str()); Serial.println();
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.println();

  // Address - validate
  address = Address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
  auto isValidAddress = Address::validate(address, networkVersion);
  Serial.println("Valid Address");
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.print("\t Valid Address: "); Serial.print(isValidAddress); Serial.println();
  Serial.println();

  // Private Key - from passphrase
  privateKey = PrivateKey::fromPassphrase(passphrase);
  Serial.println("Private Key from passprase");
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tPrivate Key: "); Serial.print(privateKey.toString().c_str()); Serial.println();
  Serial.println();

  // Private Key - object from hex
  privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  Serial.println("Private Key from hex");
  Serial.println("\tHex: 950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  Serial.print("\tPrivate Key: "); Serial.print(privateKey.toString().c_str()); Serial.println();
  Serial.println();

  // Public Key - from passphrase
  publicKey = PublicKey::fromPassphrase(passphrase);
  Serial.println("Public Key from passprase");
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tPublic Key: "); Serial.print(publicKey.toString().c_str()); Serial.println();
  Serial.println();

  // Public Key - object from hex
  publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  Serial.println("Public Key from hex");
  Serial.println("\tHex: 029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
  Serial.print("\tPublic Key: "); Serial.print(publicKey.toString().c_str()); Serial.println();
  Serial.println();

  // WIF - from passphrase
  const uint8_t wifByte = 0xaa;
  auto wif = WIF::fromPassphrase(passphrase, wifByte);
  Serial.println("WIF from passphrase");
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tWIF Byte: "); Serial.print(static_cast<uint16_t>(wifByte)); Serial.println();
  Serial.print("\tWIF: "); Serial.print(wif.toString().c_str()); Serial.println();

}
