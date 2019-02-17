/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ABSTRACT_NETWORK_H
#define ABSTRACT_NETWORK_H

#include <cstring>
#include <unordered_map>
#include <vector>

namespace Ark {
namespace Crypto {
namespace Networks {

/**
 * @brief Base58 Prefix Type
 **/
enum Base58PrefixType : int { BASE58_ADDRESS_P2PKH = 0, BASE58_ADDRESS_P2SH, BASE58_WIF };
/**/

/**
 * @brief Base58 Prefix Container
 **/
struct base58_t {
  uint8_t ADDRESS_P2PKH;
  uint8_t ADDRESS_P2SH;
  uint8_t WIF;
};
/**/

/**
 * @brief BIP32 Prefix Type
 **/
enum BIP32PrefixType : int { BIP32_PREFIX_XPUB = 0, BIP32_PREFIX_XPRV };
/**/
/**
 * @brief BIP32 Prefix Container
 **/
struct bip32_t {
  long PREFIX_XPUB;
  long PREFIX_XPRV;
};
/**/

/**
 * @brief This is the abstract network class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class AbstractNetwork {
 protected:
  base58_t base58_;
  bip32_t bip32_;
  char epoch_[34];
  bool isLocked_;

 public:
  AbstractNetwork() = default;

  /**
   * @brief Abstract Network Parameter Instantiation interface
   *
   * @param base58_t base58
   * @param bip32_t bip32
   * @param char epoch[34]
   * @param bool isEditable // default false
   **/
  AbstractNetwork(base58_t base58, bip32_t bip32, const char* epoch, bool locked = true)
      : base58_(base58), bip32_(bip32), epoch_(), isLocked_(locked) {
    std::strncpy(this->epoch_, epoch, 34);
  };
  /**/

  virtual ~AbstractNetwork() = default;

  uint8_t getBase58Prefix(Base58PrefixType prefix) const;
  void setBase58Prefix(Base58PrefixType prefix, uint8_t newByte);

  long getBIP32Prefix(BIP32PrefixType prefix) const;
  void setBIP32Prefix(BIP32PrefixType prefix, long newByte);

  bool isLocked() const;

  const char* epoch() const;
  uint8_t version() const;
};
/**/
};  // namespace Networks
};  // namespace Crypto
};  // namespace Ark

#endif
