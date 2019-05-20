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
  const auto text = "Hello World";
  const auto passphrase = "this is a top secret passphrase";

  // Message - sign
  Ark::Crypto::Utils::Message message;
  message.sign(text, passphrase);

  Serial.println("Message");
  Serial.print("\tText: "); Serial.print(text); Serial.println();
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tJson: "); Serial.print(message.toJson().c_str()); Serial.println();
  Serial.println();

  // Message - verify
  auto publicKey = PublicKey::fromHex("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  auto signature = HexToBytes("304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8");

  message = Ark::Crypto::Utils::Message(
    text,
    publicKey,
    signature
  );

  Serial.println("Message");
  Serial.print("\tJson: "); Serial.print(message.toJson().c_str()); Serial.println();
  Serial.print("\tVerified: "); Serial.print(message.verify()); Serial.println();
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
  publicKey = PublicKey("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  address = Address::fromPublicKey(publicKey, networkVersion);
  Serial.println("Address from public key");
  Serial.print("\tPublic Key: "); Serial.print(publicKey.toString().c_str()); Serial.println();
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.println();

  // Address - from privatekey
  PrivateKey privateKey("d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712");
  address = Address::fromPrivateKey(privateKey, networkVersion);
  Serial.println("Address from private key");
  Serial.print("\tPrivate Key: "); Serial.print(privateKey.toString().c_str()); Serial.println();
  Serial.print("\tAddress: "); Serial.print(address.toString().c_str()); Serial.println();
  Serial.println();

  // Address - validate
  address = Address("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib");
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
  privateKey = PrivateKey::fromHex("d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712");
  Serial.println("Private Key from hex");
  Serial.println("\tHex: d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712");
  Serial.print("\tPrivate Key: "); Serial.print(privateKey.toString().c_str()); Serial.println();
  Serial.println();

  // Public Key - from passphrase
  publicKey = PublicKey::fromPassphrase(passphrase);
  Serial.println("Public Key from passprase");
  Serial.print("\tPassphrase: "); Serial.print(passphrase); Serial.println();
  Serial.print("\tPublic Key: "); Serial.print(publicKey.toString().c_str()); Serial.println();
  Serial.println();

  // Public Key - object from hex
  publicKey = PublicKey::fromHex("034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
  Serial.println("Public Key from hex");
  Serial.println("\tHex: 034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192");
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
