# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased

## [0.3.0] - 2019-02-16
## [0.3.0-arduino] - 2019-02-16

### Added
- Arduino CircleCI config

### Changed
- updated `keywords.txt`.
- updated `./library.json` package export settings.
- removed unnecessary files:
  - `./appveyor.yml`.
  - `./CMakeSettings.json`.
  - `./test/travis.yml`.
  - `uECC_README.md`.
  - submodule from `cmake_example`
- moved external packages to `./src/lib/`:
  - `./src/bcl`.
  - `./src/rfc6979`.
  - `./src/stl`.
  - `./date`.
- moved `./docs` to `./extras` in arduino builds.
- automated `ARDUINO_IDE.sh` script.
- updated `ARDUINO_IDE.sh` script to reflect `lib/` changes.

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
