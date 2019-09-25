/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

// This is a placeholder 'setup' & 'loop' for CI testing.
// This isn't intended for project or production use.
// It is only used in the 'pio run' command from root in CI;
// successful completion of which asserts that the ARK Cpp-Crypto library builds on its own.
#if (defined PLATFORMIO && !defined UNIT_TEST)

#include <Arduino.h>

void setup() {}
void loop() {}

#endif
