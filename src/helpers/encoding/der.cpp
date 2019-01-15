/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "helpers/encoding/der.h"

#include <cassert>
#include <cstring>
#include <string>
#include <vector>

/**
 * DER Encode/Decode Helpers
 **/
std::vector<uint8_t>& toDER(std::vector<uint8_t>& buffer) {
  // if the sign bit is set, pad with a 0x00 byte
  if (buffer.size() > 1 && (buffer[0] & 0x80) != 0) {
    buffer.insert(buffer.begin(), 0x00);
  }
  return buffer;
}

/**/

void decodeDER(std::vector<uint8_t>& signature, std::vector<uint8_t>& r, std::vector<uint8_t>& s) {
  // Adapted from https://github.com/bitcoinjs/bip66/blob/master/index.js
  assert(signature.size() > 8);                  // DER sequence length is too short
  assert(signature.size() < 72);                 // DER sequence length is too long
  assert(signature[0] == 0x30);                  // Expected DER sequence
  assert(signature[1] == signature.size() - 2);  // DER sequence length is invalid
  assert(signature[2] == 0x02);                  // Expected DER integer

  /* Get the length of the signatures R-value (signature 4th-byte/signature[3]) */
  int lenR = signature[3];
  assert(lenR != 0);                      // R length is zero
  assert(5u + lenR <= signature.size());  // R length is too long
  assert(signature[4 + lenR] == 0x02);    // Expected DER integer (2)

  /* Get the length of the signatures R-value (signature 6th-byte/signature[5]) */
  int lenS = signature[5 + lenR];
  assert(lenS != 0);                               // S length is zero
  assert((6u + lenR + lenS) == signature.size());  // S length is invalid

  assert(signature[4] != 0x80);  // R value is negative
  assert((lenR > 1));            // && (signature[4] == 0x00) && !(signature[5] == 0x80)); // R value excessively padded

  assert(signature[lenR + 6] != 0x80);  // S value is negative
  assert(lenS >
         1);  // && (signature[lenR + 6] != 0x00) && !(signature[lenR + 7] == 0x80)); // S value excessively padded

  /* non-BIP66 - extract R, S values */
  r = std::vector<uint8_t>(&signature[4], &signature[4] + lenR);
  s = std::vector<uint8_t>(&signature[6 + lenR], &signature[6 + lenR] + lenS);
}

/**/

void encodeDER(const std::vector<uint8_t>& r, const std::vector<uint8_t>& s, std::vector<uint8_t>& signature) {
  /* Adapted from https://github.com/bitcoinjs/bip66/blob/master/index.js */
  auto lenR = r.size();
  auto lenS = s.size();
  assert(lenR != 0);  // must be non zero
  assert(lenS != 0);
  assert(lenR <= 33);  // must be less than 34 bytes
  assert(lenS <= 33);
  assert((r[0] & 0x80) == 0);  // must not be negative
  assert((s[0] & 0x80) == 0);
  assert(lenR == 1 || r[0] != 0x00 || (r[1] & 0x80) != 0);  // must have zero pad for negative number
  assert(lenS == 1 || s[0] != 0x00 || (s[1] & 0x80) != 0);

  auto it = r.begin();
  while (lenR > 1 && *it == 0 && *(it + 1) < 0x80) {
    --lenR;
    ++it;
  }
  it = s.begin();
  while (lenS > 1 && *it == 0 && *(it + 1) < 0x80) {
    --lenS;
    ++it;
  }

  signature.clear();
  signature.reserve(6 + lenR + lenS);

  /* 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S] */
  signature.push_back(0x30);                                       // [0]
  signature.push_back(static_cast<uint8_t>(6 + lenR + lenS - 2));  // [1]
  signature.push_back(0x02);                                       // [2]
  signature.push_back(static_cast<uint8_t>(lenR));                 // [3]
  signature.insert(signature.end(), r.begin(), r.end());           //[4]
  signature.push_back(0x02);                                       // [4 + lenR]
  signature.push_back(static_cast<uint8_t>(lenS));                 // [5 + lenR]
  signature.insert(signature.end(), s.begin(), s.end());           //[6 + lenR]
}

/**/

void encodeDER(uint8_t packed_signature[DEFAULT_PRIVATEKEY_SIZE * 2], std::vector<uint8_t>& signature) {
  std::vector<uint8_t> r(DEFAULT_PRIVATEKEY_SIZE);
  std::vector<uint8_t> s(DEFAULT_PRIVATEKEY_SIZE);

  memcpy(&r[0], packed_signature, DEFAULT_PRIVATEKEY_SIZE);
  memcpy(&s[0], packed_signature + DEFAULT_PRIVATEKEY_SIZE, DEFAULT_PRIVATEKEY_SIZE);

  encodeDER(toDER(r), toDER(s), signature);
}
