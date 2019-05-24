#include "helpers/crypto.h"

#include <cassert>
#include "bcl/Ecdsa.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Uint256.hpp"
#include "helpers/crypto_helpers.h"
#include "rfc6979/rfc6979.h"
#include "uECC.h"
#include "bip66.h"

void cryptoSign(Sha256Hash hash, Ark::Crypto::Identities::PrivateKey privateKey, std::vector<uint8_t>& signature) {
  Uint256 r;
  Uint256 s;

  uint8_t nonce32[32] = {};
  nonce_function_rfc6979(nonce32, hash.value, privateKey.toBytes(), nullptr, nullptr, 0);

  auto ret = Ecdsa::sign(Uint256(privateKey.toBytes()), hash, Uint256(nonce32), r, s);
  assert(ret);

  std::vector<uint8_t> rValue(PRIVATEKEY_SIZE), sValue(PRIVATEKEY_SIZE);
  r.getBigEndianBytes(&rValue[0]);
  s.getBigEndianBytes(&sValue[0]);

  BIP66::encode(rValue, sValue, signature);
}

bool cryptoVerify(Ark::Crypto::Identities::PublicKey publicKey, Sha256Hash hash, std::vector<uint8_t>& signature) {
  /* Get the Uncompressed PublicKey */
  auto publicKeyBytes = publicKey.toBytes();                      // compressed publicKey bytes (uint8_t*)
  uint8_t uncompressedPublicKey[64] = {};                         // create uncompressed publicKey buffer (uint8_t[64])
  const struct uECC_Curve_t* curve = uECC_secp256k1();            // define the curve-type
  uECC_decompress(publicKeyBytes, uncompressedPublicKey, curve);  // decompress the key
  if (uECC_valid_public_key(uncompressedPublicKey, curve) == 0) {
    return false;
  };  // validate the uncompressed publicKey

  /* Split uncompressed publicKey into (x,y) coordinate buffers */
  char xBuffer[65] = "\0";
  char yBuffer[65] = "\0";
  for (int i = 0; i < 32; i++) {
    snprintf(&xBuffer[i * 2], 64, "%02x", uncompressedPublicKey[i]);
    snprintf(&yBuffer[i * 2], 64, "%02x", uncompressedPublicKey[i + 32]);
  }

  /* Create curvepoint of uncompressed publicKey(x,y) */
  FieldInt x(xBuffer);  // convert xBuffer to FieldInteger
  FieldInt y(yBuffer);  // convert yBuffer to FieldInteger
  CurvePoint curvePoint(x, y);

  /* Decode signature from DER into r & s buffers */
  std::vector<uint8_t> rValue(PRIVATEKEY_SIZE), sValue(PRIVATEKEY_SIZE);

  BIP66::decode(signature, rValue, sValue);

  Uint256 r256(rValue.data());  // create Uint256/BigNumber from r-value buffer
  Uint256 s256(sValue.data());  // create Uint256/BigNumber from s-value buffer

  /* Verify */
  return Ecdsa::verify(curvePoint, hash, r256, s256);
}
