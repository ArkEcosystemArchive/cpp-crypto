/**
 * This file is part of Ark C++ Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

////////////////////////////////////////////////////////////////////////////////
// ESP8266 C++ Crypto Usage Example Sketch
//
// This sketch covers how to use the C++ Crypto library.
// It allows your ESP8266 use Ark Ecosystem cryptographic protocols.

////////////////////////////////////////////////////////////////////////////////
// NOTE:
//
// If this Repo was Cloned, run the 'ARDUINO_IDE.sh' script first.
// It's in the 'extras/' folder and extends compatability to the Arduino IDE.

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// This is where you include the 'arkCrypto.h' header.
// This allows your project to use Ark C++ Crypto.
// This header is empty and is just to force the inclusion
// of the library into the Arduino sketch

#include <arkCrypto.h>

////////////////////////////////////////////////////////////////////////////////
// This is a helper header that includes all the required Ark
// headers required for this sketch.
//
// Also set the CPU frequency to 160MHz using the Arduino IDE's 'Tools' menu.

#include "arkCrypto_esp8266.h"

////////////////////////////////////////////////////////////////////////////////
// Misc ARK C++ Crypto headers

#include "networks/devnet.hpp"

#include "utils/hex.hpp"
#include "utils/str.hpp"

////////////////////////////////////////////////////////////////////////////////
// The Main Arduino Header

#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Namespaces

using namespace Ark::Crypto;
using namespace Ark::Crypto::identities;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Sketch Constants

constexpr auto Passphrase   = "this is a top secret passphrase";
constexpr auto WifByte      = 0xaa;  // Devnet

////////////////////////////////////////////////////////////////////////////////
// Create a PrivateKey using a 12-word Passphrase.
//
// Given the passphrase "this is a top secret passphrase",
// the computed PrivateKey is:
// - "d8839c2432bfd0a67ef10a804ba991eabba19f154a3d707917681d45822a5712".
//
// ---
void createPrivateKey() {
    const auto privateKey           = PrivateKey::fromPassphrase(Passphrase);
    const auto privateKeyString     = privateKey.toString();

    printf("\n\nPrivateKey from Passphrase: %s\n\n", privateKeyString.c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Create a Wif(Wallet Import Format) PrivateKey.
//
// Uses a 12-word Passphrase and a Network Wif-byte.
//
// Given the passphrase "this is a top secret passphrase",
// and the Network byte 0xaa(Devnet),
// the computed Wif is: "SGq4xLgZKCGxs7bjmwnBrWcT4C1ADFEermj846KC97FSv1WFD1dA".
//
// --- 
void createWif() {
    const auto wif          = Wif::fromPassphrase(Passphrase, WifByte);
    const auto wifString    = wif.toString();

    printf("\n\nWIF from Passphrase: %s\n\n", wifString.c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Create a PublicKey using a 12-word Passphrase.
//
// Given the passphrase "this is a top secret passphrase",
// the computed PublicKey is:
// - "034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192".
//
// ---
void createPublicKey() {
    const auto publicKey            = PublicKey::fromPassphrase(Passphrase);
    const auto publicKeyString      = publicKey.toString();

    printf("\n\nPublicKey from Passphrase: %s\n\n", publicKeyString.c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Create a Wallet Address using a 12-word Passphrase and a Network Version.
//
// - Ark Devnet is '0x1E'
// - Ark Mainnet is '0x17'.
//
// Given the passphrase "this is a top secret passphrase" using Devnet(0x1E),
// the computed ARK Address is:
// -  "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib"
//
// ---
void createAddress() {
    const auto address = Address::fromPassphrase(Passphrase, Devnet.version);
    const auto addressString = address.toString();

    printf("\n\nARK Address: %s\n\n", addressString.c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Check the Transactions Fees
// ---
void checkFees() {
    Configuration cfg;

    auto i = 0;
    for (auto &fee : cfg.getPolicy()) {
        printf("\n\nType %d fee: %s\n", i, UintToString(fee).c_str());
        ++i;
    }

    // or get the Fee by Transaction Type
    printf("\n\nType 0 default fee: %s\n\n", UintToString(cfg.getFee(0)).c_str());
}

////////////////////////////////////////////////////////////////////////////////
// Create a BridgeChain transaction, tailored for a custom network.
void createBridgechainTransaction() {

    // Custom Bridgechain Network
    const Network BridgechainNetwork = {
        "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
        1, 0x53, 0xaa,
        "2019-04-12T13:00:00.000Z"
    };

    // Load the Custom Network Configuration
    const Configuration cfg(BridgechainNetwork);

    // Use the Transaction Builder to make a transaction.
    const auto bridgechainTransaction = builder::Transfer()
            .recipientId("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib")
            .vendorField("this is a custom bridgechain transaction")
            .sign(Passphrase)
            .build(cfg);

    // Create and Print the Json representation of the Transaction.
    const auto transactionJson = bridgechainTransaction.toJson();
    printf("\n\nBridgechain Transaction: %s\n\n", transactionJson.c_str());
}

////////////////////////////////////////////////////////////////////////////////
void setup() {
    Serial.begin(115200);

    createPrivateKey();
    createWif();
    createPublicKey();
    createAddress();
    checkFees();
    createBridgechainTransaction();
}

////////////////////////////////////////////////////////////////////////////////
void loop() {}
