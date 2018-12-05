/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef DER_H
#define DER_H

#include <cstdint>
#include <vector>

const auto DEFAULT_PRIVATEKEY_SIZE = 32u;

/**
 * DER Encode/Decode Helpers
 **/
std::vector<uint8_t>& toDER(std::vector<uint8_t>& buffer);

/**/

void decodeDER(std::vector<uint8_t>& signature, std::vector<uint8_t>& r, std::vector<uint8_t>& s);

/**/

void encodeDER(const std::vector<uint8_t>& r, const std::vector<uint8_t>& s, std::vector<uint8_t>& signature);

/**/

void encodeDER(uint8_t packed_signature[DEFAULT_PRIVATEKEY_SIZE * 2], std::vector<uint8_t>& signature);

#endif
