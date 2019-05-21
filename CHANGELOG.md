# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [0.5.0] - 2019-02-20

### Changed

- removed bip39 and mnemonic feature ([#86])

## [0.4.0] - 2019-05-20

### Changed

- updated vendorField to support 255 bytes in Core v2.4 ([#84])
- updated ArduinoJson package to version v.6.10.0 ([#76])
- updated tests to use Core fixtures ([#74])
- improved Windows support ([#83])

### Fixed

- properly handle 0 ARKtoshi Transaction amounts.

## [0.3.1] - 2019-02-19

### Fixed

- fixed PIO submodule ignore paths in `./platformio.ini` ([#70])
- added `./src/lib` to build flags for PIO in `./library.json` ([#69])

## [0.3.0] - 2019-02-16

## [0.3.0-arduino] - 2019-02-16

### Added

- Arduino CircleCI config ([#61])

### Changed

- updated `keywords.txt` ([#64])
- updated `./library.json` package export settings ([#64])
- removed unnecessary files ([#64]):
  - `./appveyor.yml`.
  - `./CMakeSettings.json`.
  - `./test/travis.yml`.
  - `uECC_README.md`.
  - submodule from `cmake_example`.
- moved external packages to `./src/lib/` ([#64]):
  - `./src/bcl`.
  - `./src/rfc6979`.
  - `./src/stl`.
  - `./date`.
- moved `./docs` to `./extras` in arduino builds ([#64])
- updated `ARDUINO_IDE.sh` script to reflect `lib/` changes ([#64])
- automated `ARDUINO_IDE.sh` script ([#60])

## [0.2.0] - 2019-02-07

### Added

- Added `toJson()` method to `Transaction` class ([#54])
- Added `ArduinoJson` dependency and Arduino Sketch paths to `library.json` ([#55])

### Changed

- Removed unused Arduino Adapter Header ([#50])
- Renamed `Helpers` class to avoid naming collision with Cpp-Client `Helpers` ([#51])
- Refactored Timestamps & `Slots` to use milliseconds and avoid integer overflow ([#53])

### Fixed

- Fixed the way the Arduino IDE Script restores converted directories ([#49])
- Corrected PIO Builds to determine dependency versions explicitly ([#52])

[unreleased]: https://github.com/ArkEcosystem/cpp-crypto/compare/0.2.0...develop
[0.2.0]: https://github.com/ArkEcosystem/cpp-crypto/compare/0.1.0..0.2.0
[#54]: https://github.com/ArkEcosystem/cpp-crypto/pull/54
[#55]: https://github.com/ArkEcosystem/cpp-crypto/pull/55
[#50]: https://github.com/ArkEcosystem/cpp-crypto/pull/50
[#51]: https://github.com/ArkEcosystem/cpp-crypto/pull/51
[#49]: https://github.com/ArkEcosystem/cpp-crypto/pull/49
[#52]: https://github.com/ArkEcosystem/cpp-crypto/pull/52
[#53]: https://github.com/ArkEcosystem/cpp-crypto/pull/53
[#60]: https://github.com/ArkEcosystem/cpp-crypto/pull/60
[#61]: https://github.com/ArkEcosystem/cpp-crypto/pull/61
[#64]: https://github.com/ArkEcosystem/cpp-crypto/pull/64
[#69]: https://github.com/ArkEcosystem/cpp-crypto/pull/69
[#70]: https://github.com/ArkEcosystem/cpp-crypto/pull/70
