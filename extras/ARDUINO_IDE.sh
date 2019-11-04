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
EXTRAS_DIR=$(dirname $0)
PROJECT_ROOT=${EXTRAS_DIR}/../
INCLUDE_DIR=${EXTRAS_DIR}/../src/include
INCLUDE_CPP_CRYPTO_DIR=${INCLUDE_DIR}/cpp-crypto
SRC_DIR=${EXTRAS_DIR}/../src

EXTRAS_BACKUP_DIR=${EXTRAS_DIR}/BACKUP

SRC_LIB_DIR=${SRC_DIR}/lib
EXTRAS_LIB_DIR=${EXTRAS_BACKUP_DIR}/lib

SRC_COMMON_DIR=${SRC_DIR}/common
INCLUDE_COMMON_DIR=${INCLUDE_CPP_CRYPTO_DIR}/common

SRC_CRYPTO_DIR=${SRC_DIR}/crypto
INCLUDE_CRYPTO_DIR=${INCLUDE_CPP_CRYPTO_DIR}/crypto

SRC_DEFAULTS_DIR=${SRC_DIR}/defaults
INCLUDE_DEFAULTS_DIR=${INCLUDE_CPP_CRYPTO_DIR}/defaults

SRC_IDENTITIES_DIR=${SRC_DIR}/identities
INCLUDE_IDENTITIES_DIR=${INCLUDE_CPP_CRYPTO_DIR}/identities

SRC_INTERFACES_DIR=${SRC_DIR}/interfaces
INCLUDE_INTERFACES_DIR=${INCLUDE_CPP_CRYPTO_DIR}/interfaces

INCLUDE_NETWORKS_DIR=${INCLUDE_CPP_CRYPTO_DIR}/networks
SRC_NETWORKS_DIR=${SRC_DIR}/networks

INCLUDE_TRANSACTIONS_DIR=${INCLUDE_CPP_CRYPTO_DIR}/transactions
SRC_TRANSACTIONS_DIR=${SRC_DIR}/transactions

if [[ $AUTO == '0' ]]; then

# Interface
echo -e "\n\n👋  Welcome Aboard  🚢\n\n"
sleep 1

if [[ -d ${INCLUDE_DIR} ]]; then
  echo -e "🤖  This script extends compatibility to the Arduino IDE  🤖\n"
  sleep 1
  echo -e "💪  All header files will be moved to their 'src' folders  💪\n"
  sleep 1
else
  echo -e "🤖  Looks like this library was already converted to support the Arduino IDE  🤖\n"
  sleep 1
  echo -e "💪  All header files will be moved back to the 'include' folder  💪\n"
  sleep 1
fi

echo -e "\n🛑  These changes are permanent, any unsaved changes will be lost  🛑\n"
sleep 2

# Prompts for continuation
read -p "⚠️  Are you sure you want to continue? (Y/n):" -n 1 -r
echo
if [[ ${REPLY} =~ ^[Nn]$ ]]; then
  echo -e "\n\n👌 Exiting script...\nNo Changes were made 👍\n\n";
  exit 0;
else
  echo -e "\n\n👌 Let's go!\n";
fi

fi  # /if [[ ${AUTO} ]]; then

if [[ -d ${INCLUDE_DIR} ]]; then
  # This will run if headers are in the 'include' directory tree.
  echo -e "****************************************\n"
  echo -e "Moving 'arkCrypto.h' to 'src' directory.\n"
  mv ${INCLUDE_CPP_CRYPTO_DIR}/arkCrypto.h ${SRC_DIR}

  echo -e "Moving 'common' headers.\n"
  mv ${INCLUDE_COMMON_DIR}/configuration.hpp  ${SRC_COMMON_DIR}
  mv ${INCLUDE_COMMON_DIR}/fee_policy.hpp     ${SRC_COMMON_DIR}
  mv ${INCLUDE_COMMON_DIR}/network.hpp        ${SRC_COMMON_DIR}

  echo -e "Moving 'crypto' headers.\n"
  mv ${INCLUDE_CRYPTO_DIR}/message.hpp  ${SRC_CRYPTO_DIR}
  mv ${INCLUDE_CRYPTO_DIR}/slot.hpp     ${SRC_CRYPTO_DIR}

  echo -e "Moving 'defaults' headers.\n"
  mkdir ${SRC_DEFAULTS_DIR}
  mv ${INCLUDE_DEFAULTS_DIR}/static_fees.hpp        ${SRC_DEFAULTS_DIR}
  mv ${INCLUDE_DEFAULTS_DIR}/transaction_types.hpp  ${SRC_DEFAULTS_DIR}

  echo -e "Moving 'identites' headers.\n"
  mv ${INCLUDE_IDENTITIES_DIR}/address.hpp    ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/keys.hpp       ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/privatekey.hpp ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/publickey.hpp  ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/wif.hpp        ${SRC_IDENTITIES_DIR}

  echo -e "Moving 'interfaces' headers.\n"
  mkdir ${SRC_INTERFACES_DIR}
  mv ${INCLUDE_INTERFACES_DIR}/identities.hpp ${SRC_INTERFACES_DIR}

  echo -e "Moving 'networks' headers.\n"
  mkdir ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/devnet.hpp   ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/mainnet.hpp  ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/testnet.hpp  ${SRC_NETWORKS_DIR}

  echo -e "Moving 'transactions' headers.\n"
  mv ${INCLUDE_TRANSACTIONS_DIR}/builder.h      ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/deserializer.h ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/serializer.h   ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/transaction.h  ${SRC_TRANSACTIONS_DIR}

  echo -e "Backing up, moving, and removing dependencies from the 'src/lib' directory.\n"
  mkdir ${EXTRAS_BACKUP_DIR}
  mkdir ${EXTRAS_LIB_DIR}
  mv ${SRC_LIB_DIR}/date        ${EXTRAS_LIB_DIR}
  mv ${SRC_LIB_DIR}/bcl         ${SRC_DIR}
  mv ${SRC_LIB_DIR}/rfc6979     ${SRC_DIR}

  echo -e "Moving Docs to the './extras' directory.\n"
  mv ${PROJECT_ROOT}/docs ${EXTRAS_DIR}

  echo -e "Removing old directories 🗑\n"
  rm -rf ${INCLUDE_DIR}
  rm -rf ${SRC_LIB_DIR}

  echo -e "****************************************\n"

  echo -e "\nAll Done!\n👏👏👏👏👏\n"
  echo -e "\nYou can now use Cpp-Crypto with the Arduino IDE 👍\n\n"
  exit 0

else
  # This will run if headers are already in the 'src' directory tree.
  echo -e "****************************************\n"

  echo -e "Creating the 'include' directory tree 🗂\n"
  mkdir ${INCLUDE_DIR}
  mkdir ${INCLUDE_CPP_CRYPTO_DIR}
  mkdir ${INCLUDE_COMMON_DIR}
  mkdir ${INCLUDE_CRYPTO_DIR}
  mkdir ${INCLUDE_DEFAULTS_DIR}
  mkdir ${INCLUDE_IDENTITIES_DIR}
  mkdir ${INCLUDE_INTERFACES_DIR}
  mkdir ${INCLUDE_NETWORKS_DIR}
  mkdir ${INCLUDE_TRANSACTIONS_DIR}

  echo -e "Moving 'arkCrypto.h' back to the 'include/cpp-crypto/' directory.\n"
  mv ${SRC_DIR}/arkCrypto.h ${INCLUDE_CPP_CRYPTO_DIR}

  echo -e "Moving 'common' headers.\n"
  mv ${SRC_COMMON_DIR}/configuration.hpp  ${INCLUDE_COMMON_DIR}
  mv ${SRC_COMMON_DIR}/fee_policy.hpp     ${INCLUDE_COMMON_DIR}
  mv ${SRC_COMMON_DIR}/network.hpp        ${INCLUDE_COMMON_DIR}

  echo -e "Moving 'crypto' headers.\n"
  mv ${SRC_CRYPTO_DIR}/message.hpp  ${INCLUDE_CRYPTO_DIR}
  mv ${SRC_CRYPTO_DIR}/slot.hpp     ${INCLUDE_CRYPTO_DIR}

  echo -e "Moving 'defaults' headers.\n"
  mv ${SRC_DEFAULTS_DIR}/static_fees.hpp        ${INCLUDE_DEFAULTS_DIR}
  mv ${SRC_DEFAULTS_DIR}/transaction_types.hpp  ${INCLUDE_DEFAULTS_DIR}
  rm -rf ${SRC_DEFAULTS_DIR}

  echo -e "Moving 'identities' headers.\n"
  mv ${SRC_IDENTITIES_DIR}/address.hpp    ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/privatekey.hpp ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/publickey.hpp  ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/wif.hpp        ${INCLUDE_IDENTITIES_DIR}

  echo -e "Moving 'interfaces' headers.\n"
  mv ${SRC_INTERFACES_DIR}/identities.hpp ${INCLUDE_INTERFACES_DIR}
  rm -rf ${SRC_INTERFACES_DIR}

  echo -e "Moving 'networks' headers.\n"
  mv ${SRC_NETWORKS_DIR}/devnet.hpp   ${INCLUDE_NETWORKS_DIR}
  mv ${SRC_NETWORKS_DIR}/mainnet.hpp  ${INCLUDE_NETWORKS_DIR}
  mv ${SRC_NETWORKS_DIR}/testnet.hpp  ${INCLUDE_NETWORKS_DIR}
  rm -rf ${SRC_NETWORKS_DIR}

  echo -e "Moving 'transactions' headers.\n"
  mv ${SRC_TRANSACTIONS_DIR}/builder.h      ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/deserializer.h ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/serializer.h   ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/transaction.h  ${INCLUDE_TRANSACTIONS_DIR}

  echo -e "Restoring the 'lib' directory.\n"
  mkdir ${SRC_LIB_DIR}
  mv ${EXTRAS_LIB_DIR}/date         ${SRC_LIB_DIR}
  mv ${SRC_DIR}/bcl                 ${SRC_LIB_DIR}
  mv ${SRC_DIR}/rfc6979             ${SRC_LIB_DIR}

  echo -e "Moving Docs back to the project root directory.\n"
  mv ${EXTRAS_DIR}/docs  ${PROJECT_ROOT}

  echo -e "Removing old directories 🗑\n"
  rm -rf ${EXTRAS_BACKUP_DIR}

  echo -e "****************************************\n"

  echo -e "\nAll Done!\n👏👏👏👏👏\n"
  echo -e "\nArduino IDE compatibility has been reverted 👍\n\n"
  exit 0

fi
