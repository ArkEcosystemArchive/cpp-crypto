/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARK_TRANSACTIONS_TYPES_FIXTURES_SECOND_SIGNATURE_V1_HPP
#define ARK_TRANSACTIONS_TYPES_FIXTURES_SECOND_SIGNATURE_V1_HPP

#include <cstdint>
#include <vector>

#include "common.hpp"

namespace v1 {

////////////////////////////////////////////////////////////////////////////////

static constexpr const uint8_t TYPE_1_TYPE          = 1U;
static constexpr const uint32_t TYPE_1_TIMESTAMP    = 41271867UL;
static constexpr const uint64_t TYPE_1_FEE          = 500000000ULL;

////////////////////////////////////////////////////////////////////////////////

// ff011e013bc27502034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed1920065cd1d000000000003699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c
static const std::vector<uint8_t> TYPE_1_BYTES = {
    255, 1,   30,  1,   59,  194, 117, 2,   3,   65,  81,  163, 236, 70,
    181, 103, 10,  104, 43,  10,  99,  57,  79,  134, 53,  135, 209, 188,
    151, 72,  59,  27,  108, 112, 235, 88,  231, 240, 174, 209, 146, 0,
    101, 205, 29,  0,   0,   0,   0,   0,   3,   105, 158, 150, 107, 37,
    37,  249, 8,   138, 105, 65,  216, 217, 79,  120, 105, 150, 74,  0,
    14,  254, 101, 120, 61,  120, 172, 130, 225, 25,  159, 230, 9,   48,
    68,  2,   32,  42,  171, 73,  71,  125, 211, 83,  30,  68,  115, 25,
    109, 8,   251, 215, 192, 14,  187, 121, 34,  61,  94,  170, 234, 240,
    44,  82,  196, 4,   26,  134, 207, 2,   32,  26,  125, 130, 101, 95,
    155, 29,  34,  175, 62,  169, 78,  111, 24,  54,  73,  187, 70,  16,
    205, 236, 163, 185, 226, 13,  108, 135, 115, 248, 105, 131, 28 };

// 03699e966b2525f9088a6941d8d94f7869964a000efe65783d78ac82e1199fe609
static constexpr const uint8_t TYPE_1_SECOND_PUBLICKEY[] = {
    3,   105, 158, 150, 107, 37,  37,  249, 8,   138, 105,
    65,  216, 217, 79,  120, 105, 150, 74,  0,   14,  254,
    101, 120, 61,  120, 172, 130, 225, 25,  159, 230, 9 };

// 304402202aab49477dd3531e4473196d08fbd7c00ebb79223d5eaaeaf02c52c4041a86cf02201a7d82655f9b1d22af3ea94e6f183649bb4610cdeca3b9e20d6c8773f869831c
static constexpr const uint8_t TYPE_1_SIGNATURE[] = {
    48,  68,  2,   32,  42,  171, 73,  71,  125, 211, 83,  30,  68,  115,
    25,  109, 8,   251, 215, 192, 14,  187, 121, 34,  61,  94,  170, 234,
    240, 44,  82,  196, 4,   26,  134, 207, 2,   32,  26,  125, 130, 101,
    95,  155, 29,  34,  175, 62,  169, 78,  111, 24,  54,  73,  187, 70,
    16,  205, 236, 163, 185, 226, 13,  108, 135, 115, 248, 105, 131, 28 };

////////////////////////////////////////////////////////////////////////////////

}  // namespace v1

#endif
