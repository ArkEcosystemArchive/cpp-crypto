---
title: "Cpp"
---

# Cpp

::: warning
This project is still under development. This page will get more content as the project evolves. In the meantime you can view its source on [Github](https://github.com/ArkEcosystem/cpp-crypto/).
:::

[[toc]]

## Installation
-   [Arduino](#Arduino)
-   [Linux >= 16.04](#OS)
-   [macOS >= 10.10](#OS)
-   [Windows >= 7](#OS)

### ARK Transactions

#### Devnet

```cpp
const auto DevnetTransaction = Builder::buildTransfer(
        "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
        100000000ULL,
        "this is a devnet transaction",
        "this is a top secret passphrase",
        "this is a top secret passphrase too");
```

#### Mainnet

```cpp
const Configuration MainnetConfiguration(Mainnet);

const auto MainnetTransaction = Builder::buildTransfer(
        "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
        100000000ULL,
        "this is a mainnet transaction",
        "this is a top secret passphrase",
        "this is a top secret passphrase too",
        MainnetConfiguration);
```

#### BridgeChain Transaction

```cpp
static const Network MyBridgechainNetwork = {
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};

const Configuration MyBridgechainConfiguration(MyBridgechainNetwork);

const auto MyBridgechainTransaction = Builder::buildTransfer(
        "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
        100000000ULL,
        "this is a custom bridgechain transaction",
        "this is a top secret passphrase",
        "this is a top secret passphrase too",
        MyBridgechainConfiguration);
```


#### With custom Fees

```cpp
static const Network MyBridgechainNetwork = {
  "16c891512149d6d3ff1b70e65900936140bf853a4ae79b5515157981dcc706df",
  1, 0x53, 0xaa,
  "2019-04-12T13:00:00.000Z"
};

const FeePolicy MyCustomFees = {
  900000000ULL, 800000000ULL, 700000000ULL, 600000000ULL, 500000000ULL,
  400000000ULL, 300000000ULL, 200000000ULL, 100000000ULL, 0ULL
};

ßconst Configuration MyBridgechainConfiguration(MyBridgechainNetwork,
                                                MyCustomFees);

const auto MyBridgechainTransaction = Builder::buildTransfer(
        "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
        100000000ULL,
        "",
        "this is a top secret passphrase",
        "",
        MyBridgechainConfiguration);
```

### Sign

```cpp
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";

Ark::Crypto::Message message;
message.sign(text, passphrase);
```

### Serialize (AIP11)

```cpp

```

### Deserialize (AIP11)

```cpp

```

## Message

### Sign

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

Ark::Crypto::Message message(
    text,
    publicKey,
    signature
);

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
PrivateKey privateKey = PrivateKey::fromPassphrase(passphrase);
```

#### Get a private key instance object from hex
```cpp
PrivateKey privateKey = PrivateKey::fromHex("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
```

### Public Key

#### Get a public key from a passphrase
```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
```

#### Get a public key instance object from hex
```cpp
PublicKey publicKey = PublicKey::fromHex("029fdf41a7d69d8efc7b236c21b9509a23d862ea4ed8b13a56e31eee58dbfd97b4");
```

### WIF

#### Get a WIF from a passphrase
```cpp
const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
const uint8_t wifByte = 0xaa;
WIF wif = WIF::fromPassphrase(passphrase, wifByte);
```

# Arduino

Download and install the Arduino IDE (>=1.8.5) from the following link:
-   `https://www.arduino.cc/en/Main/Software`

Using the Arduino IDE's built in Library Manager,
install the following Libraries:
-   `micro-ecc`
-   `AUnit`

#### Arduino Example using the Adafruit Feather ESP32

### Requirements:

**Arduino IDE:**  
Download and install the Arduino IDE (>=1.8.5) from the following link:

> `https://www.arduino.cc/en/Main/Software`

### Dependencies:

Using the Arduino IDE's built in Library Manager,

install the following Libraries:
-   ArduinoJson
-   BIP66
-   micro-ecc

### Using with the Arduino IDE

> include the following header in your Arduino Sketch:

```cpp
#include <arkCrypto.h>
```

### Arduino Example using the Adafruit Feather ESP32

```cpp
#include <arkCrypto.h>

void setup()
{
  Serial.begin(115200);

  Address address = Address::fromPassphrase(passphrase, networkVersion);
  Serial.println(address.toString().c_str());

  PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
  Serial.println(privateKey.toString().c_str());

  const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";

  PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
  Serial.println(publicKey.toString().c_str());

  const uint8_t wifByte = 0xaa;
  WIF wif = WIF::fromPassphrase(passphrase, wifByte);
  Serial.println(wif.toString().c_str());

  const auto actual = Ark::Crypto::Transactions::Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", 100000000, "", "Secret passphrase");
  Serial.println(actual.type);

  const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
  Ark::Crypto::Message message;
  message.sign(text, passphrase);
  Serial.println(BytesToHex(message.signature).c_str());
}

void loop() {}
```

## PlatformIO

### Dependencies

**Python:**

Use an installer package from the following link:

> `https://www.python.org/downloads/`

#

**PlatformIO:**

install PlatformIO if not already installed

> `pip install -U platformio`

_or_

> `python -c "$(curl -fsSL > https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"`

#

### Running the tests on an Arduino board using PlatformIO

**`cd` into the ".../cpp-crypto/test" directory:**

> `cd test`

**execute the following command to upload and run tests on your board:**  

| board    | command                         |
|:-------- | :------------------------------ |
| ESP8266  | `pio run -e esp8266 -t upload`  |
| ESP32    | `pio run -e esp32 -t upload`    |

#


# OS Builds

## Dependencies

**CMake:**

Use an installer package:

> `https://www.cmake.org/download/`

Homebrew:

> `brew install cmake`

_note: all other library dependencies will be automatically installed via CMake and Git submodule._

## Make and Build

### Linux/macOS

> `./build.sh`

### Windows

> `./build.cmd`

### CMake (manually)

1) `mkdir build && cd build`
2) `cmake ..`
3) `./tests/ark_tests`

## Build and Run Tests

### Linux/macOS

> `./run_tests.sh`

### Windows

> `./run_tests.cmd`

### CMake (manually)

1) `mkdir build && cd build`
2) `cmake ..`
3) `./tests/ark_tests`
