

# Arduino Builds


### requirements:

**Arduino IDE:**  
Download and install the Arduino IDE (>=1.8.5) from the following link:  
```https://www.arduino.cc/en/Main/Software```

#

### dependencies:

Using the Arduino IDE's built in Library Manager,  
install the following Libraries  
- micro-ecc
- AUnit
- ArduinoJson

#

### Using with the Arduino IDE
> include the following header in your Arduino Sketch:  
```cpp
#include <arkCrypto.h>
```

#

### Arduino Example using the Adafruit Feather ESP8266

```cpp
#include "arkCrypto.h"

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
  Ark::Crypto::Utils::Message message;
  message.sign(text, passphrase);
  Serial.println(BytesToHex(message.signature).c_str());
}

void loop() {}
```
