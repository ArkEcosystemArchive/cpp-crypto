/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

/**
 * ATMEL SAMD M4 Cpp-Crypto Usage Example Sketch
 *
 * This sketch covers how to use the Cpp-Crypto library.
 * It allows your ATMEL SAMD M4 use Ark Ecosystem cryptographic protocols.
 */

 /**
 * NOTE: At the time of this writing, the Cpp-Crypto library requires running the 'ARDUINO_IDE.sh' bash script located in the 'extras' folder.
 * This converts our library to be compatible with the Arduino IDE.
 */

/****************************************/

/**
 * This is where you include the 'arkCrypto.h' header.
 * This allows your project to use Ark Cpp-Crypto.
 */
#include <arkCrypto.h>
/**/

/****************************************/

void checkCrypto() {
  /**
   * Create a BridgeChain transaction, tailored for your custom network.
   */
  static const Network MyBridgechainNetwork = {
    "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
    1, 0x53, 0xaa,
    "2019-04-12T13:00:00.000Z"
  };

  const Configuration MyBridgechainConfiguration(MyBridgechainNetwork);

  auto myBridgechainTransaction = Builder::buildTransfer(
          "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
          100000000ULL,
          "this is a custom bridgechain transaction",
          "this is a top secret passphrase",
          "this is a top secret passphrase too",
          MyBridgechainConfiguration);

    Serial.print("\nBridgechain Transaction: ");
    Serial.println(myBridgechainTransaction.toJson().c_str());

  /**/

  /********************/

  /**
   * This is how you can check the default 'Network' "Transaction 'Fees' by type.
   * In this example, it should return a 'uint64_t' integer of '10000000' as the default 'Fee' for a 'Transaction' of 'Type' '0'.
   */
    Configuration config;
    unsigned long typeZeroTransactionFee = config.getFee(0);
    Serial.print("\nType 0 default Transaction Fee: ");
    Serial.println(typeZeroTransactionFee); // The response is a 'uint64_t' integer.

  /**/

  /********************/

  /**
   * The following methods allows you to create an ARK address.
   * This is done by passing a 12-word 'Passphrase' and the 'Network' 'Version' "byte".
   * The 'Version" "byte" is a BASE58 P2PKH byte. Ark Devnet is '0x1E'; Ark Mainnet is '0x17'.
   *
   * Given the passphrase "this is a top secret passphrase",
   * and the 'Devnet' 'Version' byte (0x1E); the ARK Address should be "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib"
   */
  const auto passphrase = "this is a top secret passphrase";
  const uint8_t networkVersion = 0x1E;

  Address arkAddress = Address::fromPassphrase(passphrase, networkVersion);
    Serial.print("\nARK Address: ");
    Serial.println(arkAddress.toString().c_str()); // The 'Address' object is a type. Use 'toString()' to view the output. Arduino requires a 'c_str()' to 'print'.
  /**/


  /********************/

  /**
   * The following methods allows create a 'PrivateKey'.
   * This is done by passing a 12-word 'Passphrase'.
   *
   * Given the passphrase "this is a top secret passphrase",
   * the 'PrivateKey" should be "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712".
   * This is a 'SHA256' of your "Passphrase".
   */
  const auto passphrase2 = "this is a top secret passphrase";
  PrivateKey privateKeyFromPassphrase = PrivateKey::fromPassphrase(passphrase2);
    Serial.print("\nPrivateKey from Passphrase: ");
    Serial.println(privateKeyFromPassphrase.toString().c_str()); // The 'PrivateKey' object is a type. Use 'toString()' to view the output. Arduino requires a 'c_str()' to 'print'.
  /**/

  /********************/

  /**
   * The following methods allows create a 'PublicKey'.
   * This is done by passing a 12-word 'Passphrase'.
   *
   * Given the passphrase "this is a top secret passphrase",
   * the 'PublicKey" should be "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192".
   */
  const auto passphrase3 = "this is a top secret passphrase";
  PublicKey publicKeyFromPassphrase = PublicKey::fromPassphrase(passphrase3);
    Serial.print("\nPublicKey from Passphrase: ");
    Serial.println(publicKeyFromPassphrase.toString().c_str()); // the 'PublicKey' object is a type. Use 'toString()' to view the output. Arduino requires a 'c_str()' to 'print'.
  /**/

  /********************/

  /**
   * The following methods allows create a 'WIF'-style "PrivateKey".
   * 'WIF' stands for "Wallet Import Format"
   * This is done by passing a 12-word 'Passphrase' and the 'Network' 'WIF' "byte".
   * The 'WIF" "byte" is a BASE58 WIF byte. Ark Devnet is '0xaa'; Ark Mainnet is also '0xaa'.

   *
   * Given the passphrase "this is a top secret passphrase",
   * and the 'Devnet' 'WIF' byte (0xaa);
   * The 'WIF" should be "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA".
   */
  const auto passphrase4 = "this is a top secret passphrase";
  const uint8_t wifByte = 0xaa;
  Wif wifFromPassphrase = Wif::fromPassphrase(passphrase4, wifByte);
    Serial.print("\nWIF from Passphrase: ");
    Serial.println(wifFromPassphrase.toString().c_str()); // the 'WIF' object is a type. Use 'toString()' to view the output. Arduino requires a 'c_str()' to 'print'.
  /**/
};

/****************************************/

void setup()
{
  Serial.begin(115200); // Begin your Serial Connection. This allows you to monitor your boards output.

  checkCrypto(); // Begin Crypto example usage.
};

/****************************************/

void loop() {}; // We can leave this empty, as we don't want to repeat anything in this example.
