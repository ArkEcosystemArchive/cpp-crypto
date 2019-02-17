---
title: "Cpp"
---

# Cpp

[[toc]]

## Installation
* [Arduino](#Arduino)

### Sign

```cpp
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
const auto passphrase = "viable weasel wage promote praise inflict jaguar tackle color unusual exclude direct";

Ark::Crypto::Utils::Message message;
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
Ark::Crypto::Utils::Message message;
message.sign(text, passphrase);
```

### Verify

```cpp
const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
PublicKey publicKey = PublicKey::fromHex("0275776018638e5c40f1b922901e96cac2caa734585ef302b4a2801ee9a338a456");
std::vector<uint8_t> signature = HexToBytes("3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93");

Ark::Crypto::Utils::Message message(
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

#

# Arduino
**Arduino IDE:**
Download and install the Arduino IDE (>=1.8.5) from the following link:
```https://www.arduino.cc/en/Main/Software```

Using the Arduino IDE's built in Library Manager,
install the following Libraries:
```micro-ecc```
```AUnit```

#### Ensure all git submodules have been cloned
##### Note that future goals include ensuring that all dependent libaries are registered in the PIO Library Manager to avoid the use of git submodules for PIO builds

    cd Cpp-Crypto
    git submodule update --init --recursive

#### Arduino Example using the Adafruit Feather ESP8266

```cpp
#include "arkCrypto.h"

void setup()
{
    Serial.begin(115200);

    const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";
    const uint8_t networkVersion = 0x1E;
    Address address = Address::fromPassphrase(passphrase, networkVersion);
    .println(address.toString().c_str());

    PrivateKey privateKey("950981ce17df662dbc1d25305f8597a71309fb8f7232203a0944477e2534b021");
    Serial.println(privateKey.toString().c_str());

    const auto passphrase = "bullet parade snow bacon mutual deposit brass floor staff list concert ask";

    PublicKey publicKey = PublicKey::fromPassphrase(passphrase);
    Serial.println(publicKey.toString().c_str());

    const uint8_t wifByte = 0xaa;
    WIF wif = WIF::fromPassphrase(passphrase, wifByte);
    Serial.println(wif.toString().c_str());


    const auto actual = Ark::Crypto::Transactions::Builder::buildTransfer(
            "D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
            100000000,
            "",
            "Secret passphrase"
    );
    Serial.println(actual.type);


    const auto text = "Computer science is no more about computers than astronomy is about telescopes.";
    Ark::Crypto::Utils::Message message;
    message.sign(text, passphrase);
    Serial.println(BytesToHex(message.signature).c_str());
}

void loop() {}
```

**PlatformIO IDE:**

#### Python:
Use an installer package from the following link or use your preferred method to install Python:
```https://www.python.org/downloads/```

Install PlatformIO:

    pip install -U platformio
or

    python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"

Install AUnit (2778), micro-ecc (1665)

    platformio lib -g install 2778 1665

#### Ensure all git submodules have been cloned
##### Note that future goals include ensuring that all dependent libaries are registered in the PIO Library Manager to avoid the use of git submodules for PIO builds

    cd Cpp-Crypto
    git submodule update --init --recursive

#### running the tests on an Arduino board

    cd test

#### execute the following command to upload test to your board

>| board | command |
>|:-- |:-- |
>| ESP8266 | ```pio run -e esp8266 -t upload``` |
>| ESP32 | ```pio run -e esp32 -t upload``` |

#

# OS
## Linux, macOS and Windows

**CMake:**

Use an installer package from the following link, Homebrew, or use your preferred method:
```https://www.cmake.org/download/```

using
**Homebrew:**

    brew install cmake

> note: all other dependencies will be automatically installed via CMake and Hunter Package Manager.

### make and build
    cd cpp-crypto
    cmake . && cmake --build .

### run tests (Linux, macOS)
    ./test/Ark-Cpp-Crypto-tests

### run tests (Windows)
    .\test\Debug\Ark-Cpp-Crypto-tests.exe
