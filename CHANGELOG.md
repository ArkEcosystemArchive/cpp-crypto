# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased

## Version 0.2.0 - 2019-02-07

### Added

- Added `toJson()` method to `Transaction` class ([#54](https://github.com/ArkEcosystem/cpp-crypto/pull/54))
- Added `ArduinoJson` dependency and Arduino Sketch paths to `library.json` ([#55](https://github.com/ArkEcosystem/cpp-crypto/pull/55))

### Changed

- Removed unused Arduino Adapter Header ([#50](https://github.com/ArkEcosystem/cpp-crypto/pull/50))
- Renamed `Helpers` class to avoid naming collision with Cpp-Client `Helpers` ([#51](https://github.com/ArkEcosystem/cpp-crypto/pull/51))
- Refactored Timestamps & `Slots` to use milliseconds and avoid integer overflow ([#53](https://github.com/ArkEcosystem/cpp-crypto/pull/53))

### Fixed

- Fixed the way the Arduino IDE Script restores converted directories ([#49](https://github.com/ArkEcosystem/cpp-crypto/pull/49))
- Corrected PIO Builds to determine dependency versions explicitly ([#52](https://github.com/ArkEcosystem/cpp-crypto/pull/52))