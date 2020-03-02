#!/usr/bin/env bash

# This file is part of Ark Cpp Crypto.
#
# (c) Ark Ecosystem <info@ark.io>
#
# For the full copyright and license information, please view the LICENSE
# file that was distributed with this source code.

# #########
# This script extends support to the Arduino IDE.
#
# The Arduino IDE doesn't support extending its search path outside of the 'src' folder.
# The Ark Cpp-Crypto SDK exposes its public interface via the 'include' folder.
#
# This script moves the headers from 'include' into their relative directories in the 'src' folder;
# it then delete the 'include' folder.
#
# Additionally, once this script has been ran, it can be executed again to undo these changes.
# (i.e. recreates the directory tree and moves headers back to 'include'.)
# #########

# Flags
# You can skip the interface by passing '--auto'; eg 'bash ARDUINO_IDE.sh -auto'
AUTO='0'
if [ "$1" == "--auto" ]; then
  AUTO='1'
fi

# Directories
EXTRAS_DIR=$(dirname "$0")
PROJECT_ROOT="${EXTRAS_DIR}"/../
SRC_DIR="${EXTRAS_DIR}"/../src
INCLUDE_DIR="${EXTRAS_DIR}"/../src/include
INCLUDE_CPP_CRYPTO_DIR="${INCLUDE_DIR}"/cpp-crypto

EXTRAS_BACKUP_DIR="${EXTRAS_DIR}"/BACKUP

SRC_LIB_DIR="${SRC_DIR}"/lib
EXTRAS_LIB_DIR="${EXTRAS_BACKUP_DIR}"/lib

SRC_COMMON_DIR="${SRC_DIR}"/common
INCLUDE_COMMON_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/common

SRC_CRYPTO_DIR="${SRC_DIR}"/crypto
INCLUDE_CRYPTO_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/crypto

SRC_IDENTITIES_DIR="${SRC_DIR}"/identities
INCLUDE_IDENTITIES_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/identities

SRC_INTERFACES_DIR="${SRC_DIR}"/interfaces
INCLUDE_INTERFACES_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/interfaces

INCLUDE_NETWORKS_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/networks
SRC_NETWORKS_DIR="${SRC_DIR}"/networks

INCLUDE_TRANSACTIONS_DIR="${INCLUDE_CPP_CRYPTO_DIR}"/transactions
SRC_TRANSACTIONS_DIR="${SRC_DIR}"/transactions

INCLUDE_TRANSACTIONS_BUILDERS_DIR="${INCLUDE_TRANSACTIONS_DIR}"/builders
SRC_TRANSACTIONS_BUILDERS_DIR="${SRC_TRANSACTIONS_DIR}"/builders

if [[ $AUTO == '0' ]]; then
  # Interface
  printf '\n\n%s\n\n' "👋  Welcome Aboard  🚢"
  sleep 1

  if [[ -d "${INCLUDE_DIR}" ]]; then
    printf '%s\n' "🤖   This script extends compatibility to the Arduino IDE  🤖"
    sleep 1
    printf '%s\n' "💪   All header files will be moved to their 'src' folders  💪"
    sleep 1
  else
    printf '%s\n' "🤖   Looks like this library was already converted to support the Arduino IDE  🤖"
    sleep 1
    printf '%s\n' "💪   All header files will be moved back to the 'include' folder  💪"
    sleep 1
  fi

  printf '%s\n\n' "🛑   These changes are permanent, any unsaved changes will be lost  🛑"
  sleep 2

  # Prompts for continuation
  read -p "Are you sure you want to continue? (Y/n):" -n 1 -r
  printf '\n'
  if [[ "${REPLY}" =~ ^[Nn]$ ]]; then
    printf '\n%s\n\n%s\n\n' "👌   Exiting script..." "No Changes were made  👍"
    exit 0
  else
    printf '\n%s\n\n' "👌   Let's go!"
  fi

fi # /if [[ "${AUTO}" ]]; then

if [[ -d "${INCLUDE_DIR}" ]]; then
  # This will run if headers are in the 'include' directory tree.
  printf '%s\n' "****************************************"

  printf '%s\n' "Creating destination directories."
  mkdir "${SRC_INTERFACES_DIR}"
  mkdir "${SRC_NETWORKS_DIR}"
  mkdir "${EXTRAS_BACKUP_DIR}"
  mkdir "${EXTRAS_LIB_DIR}"

  printf '%s\n' "Moving 'arkCrypto.h' to 'src' directory."
  mv "${INCLUDE_CPP_CRYPTO_DIR}"/arkCrypto.h "${SRC_DIR}"

  printf '%s\n' "Moving 'common' headers."
  mv "${INCLUDE_COMMON_DIR}"/configuration.hpp  "${SRC_COMMON_DIR}"
  mv "${INCLUDE_COMMON_DIR}"/fee_policy.hpp     "${SRC_COMMON_DIR}"
  mv "${INCLUDE_COMMON_DIR}"/network.hpp        "${SRC_COMMON_DIR}"

  printf '%s\n' "Moving 'crypto' headers."
  mv "${INCLUDE_CRYPTO_DIR}"/message.hpp  "${SRC_CRYPTO_DIR}"
  mv "${INCLUDE_CRYPTO_DIR}"/slot.hpp     "${SRC_CRYPTO_DIR}"

  printf '%s\n' "Moving 'identites' headers."
  mv "${INCLUDE_IDENTITIES_DIR}"/address.hpp      "${SRC_IDENTITIES_DIR}"
  mv "${INCLUDE_IDENTITIES_DIR}"/keys.hpp         "${SRC_IDENTITIES_DIR}"
  mv "${INCLUDE_IDENTITIES_DIR}"/privatekey.hpp   "${SRC_IDENTITIES_DIR}"
  mv "${INCLUDE_IDENTITIES_DIR}"/publickey.hpp    "${SRC_IDENTITIES_DIR}"
  mv "${INCLUDE_IDENTITIES_DIR}"/wif.hpp          "${SRC_IDENTITIES_DIR}"

  printf '%s\n' "Moving 'interfaces' headers."
  mv "${INCLUDE_INTERFACES_DIR}"/constants.h      "${SRC_INTERFACES_DIR}"
  mv "${INCLUDE_INTERFACES_DIR}"/identities.hpp   "${SRC_INTERFACES_DIR}"

  printf '%s\n' "Moving 'networks' headers."
  mv "${INCLUDE_NETWORKS_DIR}"/devnet.hpp   "${SRC_NETWORKS_DIR}"
  mv "${INCLUDE_NETWORKS_DIR}"/mainnet.hpp  "${SRC_NETWORKS_DIR}"
  mv "${INCLUDE_NETWORKS_DIR}"/testnet.hpp  "${SRC_NETWORKS_DIR}"

  printf '%s\n' "Moving 'transactions' headers."
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/builder.hpp                 "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/transfer.hpp                "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/second_signature.hpp        "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/delegate_registration.hpp   "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/vote.hpp                    "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/ipfs.hpp                    "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/multi_payment.hpp           "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/delegate_resignation.hpp    "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/htlc_lock.hpp               "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/htlc_claim.hpp              "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"/htlc_refund.hpp             "${SRC_TRANSACTIONS_BUILDERS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_DIR}"/transaction_data.hpp                 "${SRC_TRANSACTIONS_DIR}"
  mv "${INCLUDE_TRANSACTIONS_DIR}"/transaction.hpp                      "${SRC_TRANSACTIONS_DIR}"

  printf '%s\n' "Backing up, moving, and removing dependencies from the 'src/lib' directory."
  mv "${SRC_LIB_DIR}"/date      "${EXTRAS_LIB_DIR}"
  mv "${SRC_LIB_DIR}"/rfc6979   "${SRC_DIR}"

  printf '%s\n' "Moving Docs to the './extras' directory."
  mv "${PROJECT_ROOT}"/docs "${EXTRAS_DIR}"

  printf '%s\n' "Removing old directories 🗑"
  rm -rf "${INCLUDE_DIR}"
  rm -rf "${SRC_LIB_DIR}"

  printf '%s\n' "****************************************"

  printf '\n%s\n%s\n' "All Done!" "👏 👏 👏 👏 👏"
  printf '\n%s\n\n' "You can now use Cpp-Crypto with the Arduino IDE  👍"
  exit 0
else
  # This will run if headers are already in the 'src' directory tree.
  printf '%s\n' "****************************************"

  printf '%s\n' "Creating the 'include' directory tree  🗂"
  mkdir "${INCLUDE_DIR}"
  mkdir "${INCLUDE_CPP_CRYPTO_DIR}"
  mkdir "${INCLUDE_COMMON_DIR}"
  mkdir "${INCLUDE_CRYPTO_DIR}"
  mkdir "${INCLUDE_IDENTITIES_DIR}"
  mkdir "${INCLUDE_INTERFACES_DIR}"
  mkdir "${INCLUDE_NETWORKS_DIR}"
  mkdir "${INCLUDE_TRANSACTIONS_DIR}"
  mkdir "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"

  printf '%s\n' "Moving 'arkCrypto.h' back to the 'include/cpp-crypto/' directory."
  mv "${SRC_DIR}"/arkCrypto.h "${INCLUDE_CPP_CRYPTO_DIR}"

  printf '%s\n' "Moving 'common' headers."
  mv "${SRC_COMMON_DIR}"/configuration.hpp  "${INCLUDE_COMMON_DIR}"
  mv "${SRC_COMMON_DIR}"/fee_policy.hpp     "${INCLUDE_COMMON_DIR}"
  mv "${SRC_COMMON_DIR}"/network.hpp        "${INCLUDE_COMMON_DIR}"

  printf '%s\n' "Moving 'crypto' headers."
  mv "${SRC_CRYPTO_DIR}"/message.hpp  "${INCLUDE_CRYPTO_DIR}"
  mv "${SRC_CRYPTO_DIR}"/slot.hpp     "${INCLUDE_CRYPTO_DIR}"

  printf '%s\n' "Moving 'identities' headers."
  mv "${SRC_IDENTITIES_DIR}"/address.hpp      "${INCLUDE_IDENTITIES_DIR}"
  mv "${SRC_IDENTITIES_DIR}"/keys.hpp         "${INCLUDE_IDENTITIES_DIR}"
  mv "${SRC_IDENTITIES_DIR}"/privatekey.hpp   "${INCLUDE_IDENTITIES_DIR}"
  mv "${SRC_IDENTITIES_DIR}"/publickey.hpp    "${INCLUDE_IDENTITIES_DIR}"
  mv "${SRC_IDENTITIES_DIR}"/wif.hpp          "${INCLUDE_IDENTITIES_DIR}"

  printf '%s\n' "Moving 'interfaces' headers."
  mv "${SRC_INTERFACES_DIR}"/constants.h      "${INCLUDE_INTERFACES_DIR}"
  mv "${SRC_INTERFACES_DIR}"/identities.hpp   "${INCLUDE_INTERFACES_DIR}"

  printf '%s\n' "Moving 'networks' headers."
  mv "${SRC_NETWORKS_DIR}"/devnet.hpp   "${INCLUDE_NETWORKS_DIR}"
  mv "${SRC_NETWORKS_DIR}"/mainnet.hpp  "${INCLUDE_NETWORKS_DIR}"
  mv "${SRC_NETWORKS_DIR}"/testnet.hpp  "${INCLUDE_NETWORKS_DIR}"

  printf '%s\n' "Moving 'transactions' headers."
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/builder.hpp                 "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/transfer.hpp                "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/second_signature.hpp        "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/delegate_registration.hpp   "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/vote.hpp                    "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/ipfs.hpp                    "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/multi_payment.hpp           "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/delegate_resignation.hpp    "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/htlc_lock.hpp               "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/htlc_claim.hpp              "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_BUILDERS_DIR}"/htlc_refund.hpp             "${INCLUDE_TRANSACTIONS_BUILDERS_DIR}"
  mv "${SRC_TRANSACTIONS_DIR}"/transaction_data.hpp                 "${INCLUDE_TRANSACTIONS_DIR}"
  mv "${SRC_TRANSACTIONS_DIR}"/transaction.hpp                      "${INCLUDE_TRANSACTIONS_DIR}"

  printf '%s\n' "Restoring the 'lib' directory."
  mkdir "${SRC_LIB_DIR}"
  mv "${EXTRAS_LIB_DIR}"/date   "${SRC_LIB_DIR}"
  mv "${SRC_DIR}"/rfc6979       "${SRC_LIB_DIR}"

  printf '%s\n' "Moving Docs back to the project root directory."
  mv "${EXTRAS_DIR}"/docs "${PROJECT_ROOT}"

  printf '%s\n' "Removing old directories 🗑"
  rm -rf "${EXTRAS_BACKUP_DIR}"
  rm -rf "${SRC_INTERFACES_DIR}"
  rm -rf "${SRC_NETWORKS_DIR}"

  printf '%s\n' "****************************************"

  printf '\n%s\n%s\n' "All Done!" "👏 👏 👏 👏 👏"
  printf '\n%s\n\n' "Arduino IDE compatibility has been reverted  👍"
  exit 0
fi
