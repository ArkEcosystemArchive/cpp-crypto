

# OS Builds

### dependencies

**CMake:**  
> Use an installer package from the following link:  
> ```https://www.cmake.org/download/```

or    
**Homebrew:**  
> `brew install cmake`

#

> note: all other dependencies will be automatically installed via CMake and Hunter Package Manager.

#

### make and build
**`cd`** into **`.../cpp-crypto/`**  
then run the following commands:  
> init & update micro-ecc submodule  
>`git submodule init && git submodule update`

> make and build  
> `cmake . && cmake --build .`

#

### run tests
> `./bin/Ark-Cpp-Crypto-tests`
