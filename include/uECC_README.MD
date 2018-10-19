
# Desktop Platforms
if building for a desktop platform (mac, windows, linux),  
be sure to update your git submodules using the following command from the `Ark-Cpp` folder.

```
git submodule init && git submodule update
```

# IoT Platforms

if you're building for IoT using PlatformIO or the Arduino IDE,  
this folder should be empty.  

PlatformIO manages this libraries dependences.  

Arduino IDE,  
either install the libraries using Arduino's Library Manager,  
or manually cloning/downloading them to your `Arduino/libraries` folder.  


# External Dependencies

- ArduinoJson  
- micro-ecc  
- AUnit (for testing)  
