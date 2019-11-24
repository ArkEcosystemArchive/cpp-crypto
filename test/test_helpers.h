/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TEST_HELPERS_H
#define ARK_TEST_HELPERS_H

////////////////////////////////////////////////////////////////////////////////
// Array comparison differs across architectures and environments.
// This helper method avoids have to loop each array for comparison.
//
// @param: const uint8_t *expected
// @param: const uint8_t *actual
// @param: const uint32_t length
//
// @return: bool
// - 'true' if the arrays match.
// - 'false' on mismatch. Also prints info to the console.
//
// ---
static inline bool array_cmp(const uint8_t *expected,
                             const uint8_t *actual,
                             const uint32_t length) {
    for (uint32_t i = 0UL; i < length; ++i) {
        if (expected[i] != actual[i]) {
            printf("\n\nMismatch at element: %d", i);
            printf("\nExpected value: %d", (int)expected[i]);
            printf("\nActual value: %d\n\n", (int)actual[i]);
            return false;
        }
    }

    return true;
}

#endif
