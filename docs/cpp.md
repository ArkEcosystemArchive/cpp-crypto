---
title: "Cpp"
---

# C++

::: warning
This project is still under development. This page will get more content as the project evolves. In the meantime you can view its source on [Github](https://github.com/ArkEcosystem/cpp-crypto/).
:::

[[toc]]

## Installation

* [Arduino IDE](#Arduino-IDE)
* [PlatformIO IDE](#PlatformIO-IDE)
* [Desktop/Server](#Desktop-Server)
  * **Linux >= 16.04**
  * **macOS >= 10.10**
  * **Windows >= 7**

## ARK Transactions

### Devnet

```cpp
// Default Configuration is Devnet
const auto transaction = builder::Transfer()
        .type(0)
        .nonce(1)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .vendorField("this is a devnet transaction")
        .amount(100000000ULL)
        .expiration(0)
        .recipientId("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib")
        .sign("this is a top secret passphrase")
        .secondSign("this is a top secret passphrase too")
        .build();
```

### Mainnet

```cpp
// Use the Configuration Class to create a Mainnet Transaction
const Configuration mainnetCfg(Mainnet);

const auto transaction = builder::Transfer()
        .type(0)
        .nonce(1)
        .senderPublicKey(fixtures::PublicKeyBytes.data())
        .vendorField("this is a devnet transaction")
        .amount(100000000ULL)
        .expiration(0)
        .recipientId("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib")
        .sign("this is a top secret passphrase")
        .secondSign("this is a top secret passphrase too")
        .build(mainnetCfg);
```

### BridgeChain Transaction

```cpp
const Network Radians = {
    "f39a61f04d6136a690a0b675ef6eedbd053665bd343b4e4f03311f12065fb875",
    1, 0xCE, 0x41,
    "2019-10-25T09:05:40.856Z"
};

const Configuration radiansCfg(Radians);

const std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN> senderPublicKeyBytes = {
    {   3, 65, 81, 163, 236, 70, 181, 103, 10, 104, 43, 10, 99, 57, 79, 134, 53,
      135, 209, 188, 151, 72, 59, 27, 108, 112, 235, 88, 231, 240, 174, 209,
      146 }};

const uint8_t radiansRecipient[] = {
    65, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
    90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

auto transaction = builder::Transfer()
        .type(0)
        .nonce(1)
        .senderPublicKey(senderPublicKeyBytes.data())
        .vendorField("this is a Radians transaction")
        .amount(100000000ULL)
        .expiration(0)
        .recipientId(radiansRecipient)
        .sign("this is a top secret passphrase")
        .secondSign("this is a top secret passphrase too")
        .build(radiansCfg);
```

### With custom Fees

```cpp
const Network Radians = {
    "f39a61f04d6136a690a0b675ef6eedbd053665bd343b4e4f03311f12065fb875",
    1, 0xCE, 0x41,
    "2019-10-25T09:05:40.856Z"
};

const FeePolicy customFees = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};

const Configuration customCfg(Radians, MyCustomFees);

auto transaction = builder::Transfer()
        .type(0)
        .nonce(1)
        .senderPublicKey(senderPublicKeyBytes.data())
        .vendorField("this is a Radians transaction")
        .amount(100000000ULL)
        .expiration(0)
        .recipientId(radiansRecipient)
        .sign("this is a top secret passphrase")
        .secondSign("this is a top secret passphrase too")
        .build(customCfg);
```

### Sign a Transactions

```cpp
// ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d
const std::vector<uint8_t> transferBytes = {
    255, 2,   23,  1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 128, 150, 152, 0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  29,  252, 105,
    181, 76,  127, 233, 1,   233, 29,  90,  154, 183, 131, 136, 100, 94,  36,
    39,  234, 48,  69,  2,   33,  0,   213, 80,  81,  245, 174, 199, 216, 148,
    175, 185, 135, 213, 130, 230, 62,  1,   87,  183, 166, 224, 203, 142, 255,
    29,  112, 172, 129, 203, 187, 19,  130, 233, 2,   32,  41,  75,  137, 172,
    177, 6,   232, 17,  180, 138, 7,   42,  85,  89,  21,  190, 164, 170, 15,
    198, 60,  66,  16,  173, 144, 17,  93,  18,  32,  179, 27,  125 };

TransactionData data;

Deserializer::deserialize(&data, transferBytes);

transaction.sign("this is a top secret passphrase");
```

### Serialize (AIP11)

```cpp
// ff02170100000000000100000000000000034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192809698000000000000010000000000000000000000171dfc69b54c7fe901e91d5a9ab78388645e2427ea3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d
const std::vector<uint8_t> transferBytes = {
    255, 2,   23,  1,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   3,   65,  81,  163, 236, 70,  181, 103, 10,  104, 43,  10,  99,
    57,  79,  134, 53,  135, 209, 188, 151, 72,  59,  27,  108, 112, 235, 88,
    231, 240, 174, 209, 146, 128, 150, 152, 0,   0,   0,   0,   0,   0,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  29,  252, 105,
    181, 76,  127, 233, 1,   233, 29,  90,  154, 183, 131, 136, 100, 94,  36,
    39,  234, 48,  69,  2,   33,  0,   213, 80,  81,  245, 174, 199, 216, 148,
    175, 185, 135, 213, 130, 230, 62,  1,   87,  183, 166, 224, 203, 142, 255,
    29,  112, 172, 129, 203, 187, 19,  130, 233, 2,   32,  41,  75,  137, 172,
    177, 6,   232, 17,  180, 138, 7,   42,  85,  89,  21,  190, 164, 170, 15,
    198, 60,  66,  16,  173, 144, 17,  93,  18,  32,  179, 27,  125 };

TransactionData data;

Deserializer::deserialize(&data, transferBytes);
```

### Deserialize (AIP11)

```cpp
const std::array<uint8_t, PUBLICKEY_COMPRESSED_LEN> senderPublicKeyBytes = {
    {   3, 65, 81, 163, 236, 70, 181, 103, 10, 104, 43, 10, 99, 57, 79, 134, 53,
      135, 209, 188, 151, 72, 59, 27, 108, 112, 235, 88, 231, 240, 174, 209,
      146 }};

// base58Decode(AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff)
constexpr uint8_t recipientId[] = {
    23, 29,  252, 105, 181, 76,  127, 233, 1,  233, 29,
    90, 154, 183, 131, 136, 100, 94,  36,  39, 234 };

TransactionData data;

data.network        = 23U;
data.typeGroup      = 1UL;
data.type           = 0UL;
data.nonce          = 1ULL;

std::move(senderPublicKeyBytes,
          senderPublicKeyBytes.end(),
          data.senderPublicKey.begin());

data.fee            = 10000000ULL;

data.asset.transfer.amount      = 100000ULL;
data.asset.transfer.expiration  = 0UL;

std::move(recipientId,
          recipientId + ADDRESS_HASH_LEN,
          data.asset.transfer.recipientId.begin());

const auto serialized = Serializer::serialize(data);
```

## Message

### Sign a Message

```cpp
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
Ark::Crypto::Message message;
message.sign(text, passphrase);
```

### Verify

```cpp
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
PublicKey publicKey = PublicKey::fromHex("0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456");
std::vector<uint8_t> signature = HexToBytes("3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93");

const auto message = Ark::Crypto::Message(text, publicKey, signature);

message.verify();
```

## Identities

### Address

#### Get an address from a passphrase

```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const uint8_t networkVersion = 0x1E;
Address address = Address::fromPassphrase(passphrase, networkVersion);
```

#### Get an address from a public key

```cpp
PublicKey publicKey("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
const uint8_t networkVersion = 0x1E;
Address address = Address::fromPublicKey(publicKey, networkVersion);
```

#### Get an address from a private key

```cpp
PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
const uint8_t networkVersion = 0x1E;
Address address = Address::fromPrivateKey(privateKey, networkVersion);
```

#### Validate an address

```cpp
Address address("DStZXkgpEjxbG355nQ26vnkp95p24U9tsV");
bool isValidAddress = Address::validate(address, networkVersion);
```

### Private Key

#### Get a private key from a passphrase

```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const auto privateKey = PrivateKey::fromPassphrase(passphrase);
```

#### Get a private key instance object from hex

```cpp
const auto privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
```

### Public Key

#### Get a public key from a passphrase

```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const auto publicKey = PublicKey::fromPassphrase(passphrase);
```

#### Get a public key instance object from hex

```cpp
const auto publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
```

### WIF

#### Get a WIF from a passphrase

```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const uint8_t wifByte = 0xaa;
const auto wif = WIF::fromPassphrase(passphrase, wifByte);
```

---

## Arduino IDE

Download and install the Arduino IDE (>=1.8.10) from the following link:  

* `https://www.arduino.cc/en/Main/Software`

### Dependencies

Using the Arduino IDE's built in Library Manager, install the following Libraries:

* [`ArduinoJson@6.12.0`](https://github.com/bblanchon/ArduinoJson)
* [`bcl@0.0.5`](https://github.com/sleepdefic1t/bcl)
* [`BIP66@0.3.2`](https://github.com/sleepdefic1t/BIP66)
* [`micro-ecc@1.0.0`](https://github.com/kmackay/micro-ecc)

### Arduino Example using the Adafruit ESP32 Feather

---

> `extras/ESP32/arkCrypto_esp32.h`

```cpp
/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_CRYPTO_ESP32_H
#define ARK_CRYPTO_ESP32_H

#include "common/configuration.hpp"
#include "common/network.hpp"

#include "crypto/message.hpp"

#include "identities/address.hpp"
#include "identities/privatekey.hpp"
#include "identities/publickey.hpp"
#include "identities/wif.hpp"

#include "transactions/builders/transfer.hpp"
#include "transactions/transaction.hpp"

#endif
```

---

> `extras/ESP32/ESP32.ino`

```cpp
/**
 * This file is part of Ark C++ Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

////////////////////////////////////////////////////////////////////////////////
// ESP32 C++ Crypto Usage Example Sketch
//
// This sketch covers how to use the C++ Crypto library.
// It allows your ESP32 use Ark Ecosystem cryptographic protocols.

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

#include "arkCrypto_esp32.h"

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

static const auto Passphrase        = "this is a top secret passphrase";
static const auto SecondPassphrase  = "this is a top secret passphrase too";
static const auto MessageText       = "Hello World";

static const auto WifByte           = 0xaa;  // Devnet

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
// Sign a Message using a 12-word Passphrase and Verify it.
//
// Given the text "Hello World",
// and the passphrase "this is a top secret passphrase",
// the computed 'Signature" is:
// - "304402200fb4adddd1f1d652b544ea6ab62828a0a65b712ed447e2538db0caebfa68929e02205ecb2e1c63b29879c2ecf1255db506d671c8b3fa6017f67cfd1bf07e6edd1cc8".
//
// ---
void signMessage() {
    Message message;
    message.sign(MessageText, Passphrase);

    const auto signatureString = BytesToHex(message.signature);
    printf("\n\nSignature from Signed Message: %s\n", signatureString.c_str());

    const bool isValid = message.verify();
    printf("\nMessage Signature is valid: %s\n\n", isValid ? "true" : "false");
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
            .secondSign(SecondPassphrase)
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
    signMessage();
    createBridgechainTransaction();
}

////////////////////////////////////////////////////////////////////////////////
void loop() {}

```

---

## PlatformIO IDE

### Requirements

#### Python

* Linux:
  * `sudo apt-get install python`
* macOS:
  * `brew install python`
* Windows Installer Pkg:
  * `https://www.python.org/downloads/windows/`

#### PlatformIO

* Linux/macOS/Windows using PIP:
  * `pip install -U platformio`
* Linux/macOS/Windows using cURL:
  * `python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"`

### Dependencies

The following external libraries are fetched during the build process:

* [`ArduinoJson@6.12.0`](https://github.com/bblanchon/ArduinoJson)
* [`bcl@0.0.5`](https://github.com/sleepdefic1t/bcl)
* [`BIP66@0.3.2`](https://github.com/sleepdefic1t/BIP66)
* [`micro-ecc@1.0.0`](https://github.com/kmackay/micro-ecc)

### Build and Run Live Tests on the ESP32

>| board | command                                      |
>| :---- | :------                                      |
>| ESP32 | `pio run -e esp32_tests -d test/ -t upload`  |

---

## Desktop/Server

Linux, macOS and Windows.

### Requirements

**CMake:**

Installing Cmake:

* Linux:
  * `sudo apt-get -y install cmake`
* macOS:
  * `brew install cmake`
* Windows Installer Pkg:
  * `https://www.cmake.org/download/`

### Dependencies

The following external libraries are cloned during the build process:

* [`ArduinoJson@6.12.0`](https://github.com/bblanchon/ArduinoJson)
* [`bcl@0.0.5`](https://github.com/sleepdefic1t/bcl)
* [`BIP66@0.3.2`](https://github.com/sleepdefic1t/BIP66)
* [`micro-ecc@1.0.0`](https://github.com/kmackay/micro-ecc)

### Building

#### make and build

* `cd cpp-crypto`
* `mkdir build && cd build`
* `cmake -DUNIT_TEST=ON ..`
* `cmake --build .`

#### run tests (Linux, macOS)

* `./test/ark_cpp_crypto_tests`

#### run tests (Windows)

* `.\test\Debug\ark_cpp_crypto_tests.exe`
