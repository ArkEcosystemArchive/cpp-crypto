
#include "helpers/crypto.h"

#include "bcl/Ecdsa.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Uint256.hpp"
#include "helpers/crypto_helpers.h"
#include "rfc6979/rfc6979.h"
#include "uECC.h"
#include "bip66.h"

void cryptoSign(
    const Sha256Hash& hash,
    const Ark::Crypto::identities::PrivateKey& privateKey,
    std::vector<uint8_t>& signature) {
  // create r & s-values
  Uint256 r;
  Uint256 s;

  // create the nonce
  uint8_t nonce32[32] = {};
  nonce_function_rfc6979(
      nonce32,
      hash.value,
      privateKey.toBytes().data(),
      nullptr, nullptr, 0);

  // sign the hash using privateKey-bytes and nonce.
  // outputs r & s-values.
  Ecdsa::sign(
      Uint256(privateKey.toBytes().data()),
      hash,
      Uint256(nonce32),
      r, s);

  // create r & s-value uint8_t vector
  std::vector<uint8_t> rValue(PRIVATEKEY_SIZE);
  std::vector<uint8_t> sValue(PRIVATEKEY_SIZE);

  // plate big-endian bytes into r & s-value buffers
  r.getBigEndianBytes(&rValue[0]);
  s.getBigEndianBytes(&sValue[0]);

  // encode r & s-values into a BIP66/DER-encoded signature.
  BIP66::encode(rValue, sValue, signature);
}

/**/

bool cryptoVerify(
    const Ark::Crypto::identities::PublicKey& publicKey,
    const Sha256Hash& hash,
    const std::vector<uint8_t>& signature) {
  // Get the Uncompressed PublicKey

  // compressed publicKey bytes (uint8_t*)
  auto publicKeyBytes = publicKey.toBytes();

  // create uncompressed publicKey buffer (uint8_t[64])
  uint8_t uncompressedPublicKey[64] = {};

  // define the curve-type
  const struct uECC_Curve_t* curve = uECC_secp256k1();

  // decompress the key
  uECC_decompress(publicKeyBytes.data(), uncompressedPublicKey, curve);
  if (uECC_valid_public_key(uncompressedPublicKey, curve) == 0) {
    return false;
  };  // validate the uncompressed publicKey

  // Split uncompressed publicKey into (x,y) coordinate buffers
  char xBuffer[65] = "\0";
  char yBuffer[65] = "\0";
  for (int i = 0; i < 32; i++) {
    snprintf(&xBuffer[i * 2], 64, "%02x", uncompressedPublicKey[i]);
    snprintf(&yBuffer[i * 2], 64, "%02x", uncompressedPublicKey[i + 32]);
  }

  // Create curvepoint of uncompressed publicKey(x,y)
  // convert xBuffer & yBuffer to FieldInteger
  FieldInt x(xBuffer);
  FieldInt y(yBuffer);
  CurvePoint curvePoint(x, y);

  /// Decode signature from DER into r & s buffers
  std::vector<uint8_t> rValue(PRIVATEKEY_SIZE);
  std::vector<uint8_t> sValue(PRIVATEKEY_SIZE);
  BIP66::decode(signature, rValue, sValue);

  // create Uint256/BigNumber from r & s-value buffers
  Uint256 r256(rValue.data());
  Uint256 s256(sValue.data());

  // Verify
  return Ecdsa::verify(curvePoint, hash, r256, s256);
}
