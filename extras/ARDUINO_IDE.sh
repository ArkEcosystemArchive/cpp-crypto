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
EXTRAS_DIR=`dirname "$0"`
INCLUDE_DIR=${EXTRAS_DIR}/../src/include
INCLUDE_CRYPTO_DIR=${INCLUDE_DIR}/cpp-crypto
SRC_DIR=${EXTRAS_DIR}/../src

EXTRAS_BACKUP_DIR=${EXTRAS_DIR}/BACKUP

SRC_LIB_DIR=${SRC_DIR}/lib
EXTRAS_LIB_DIR=${EXTRAS_BACKUP_DIR}/lib

EXTRAS_IDENTITIES_DIR=${EXTRAS_BACKUP_DIR}/identities

INCLUDE_CONFIGURATION_DIR=${INCLUDE_CRYPTO_DIR}/configuration
SRC_CONFIGURATION_DIR=${SRC_DIR}/configuration

INCLUDE_ENUMS_DIR=${INCLUDE_CRYPTO_DIR}/enums
SRC_ENUMS_DIR=${SRC_DIR}/enums

INCLUDE_HELPERS_DIR=${INCLUDE_CRYPTO_DIR}/helpers
SRC_HELPERS_DIR=${SRC_DIR}/helpers

INCLUDE_ENCODING_DIR=${INCLUDE_HELPERS_DIR}/encoding
SRC_ENCODING_DIR=${SRC_HELPERS_DIR}/encoding

INCLUDE_IDENTITIES_DIR=${INCLUDE_CRYPTO_DIR}/identities
SRC_IDENTITIES_DIR=${SRC_DIR}/identities

INCLUDE_NETWORKS_DIR=${INCLUDE_CRYPTO_DIR}/networks
SRC_NETWORKS_DIR=${SRC_DIR}/networks

INCLUDE_TRANSACTIONS_DIR=${INCLUDE_CRYPTO_DIR}/transactions
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
  mv ${INCLUDE_CRYPTO_DIR}/arkCrypto.h ${SRC_DIR}

  echo -e "Moving 'configuration' headers.\n"
  mv ${INCLUDE_CONFIGURATION_DIR}/fee.h     ${SRC_CONFIGURATION_DIR}
  mv ${INCLUDE_CONFIGURATION_DIR}/network.h ${SRC_CONFIGURATION_DIR}

  echo "Creating 'enums' folder 🗂"
  mkdir ${SRC_ENUMS_DIR}

  echo -e "Moving 'enums' headers.\n"
  mv ${INCLUDE_ENUMS_DIR}/fees.h  ${SRC_ENUMS_DIR}
  mv ${INCLUDE_ENUMS_DIR}/types.h ${SRC_ENUMS_DIR}

  echo -e "Moving 'helpers' headers.\n"
  mv ${INCLUDE_HELPERS_DIR}/encoding/der.h  ${SRC_HELPERS_DIR}/encoding
  mv ${INCLUDE_HELPERS_DIR}/encoding/hex.h  ${SRC_HELPERS_DIR}/encoding

  ## 'bip39' library is not supported in Arduino
  echo -e "Backing up and removing 'mnemonic.h'.\n"
  mkdir ${EXTRAS_BACKUP_DIR}
  mkdir ${EXTRAS_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/mnemonic.h ${EXTRAS_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/mnemonic.cpp ${EXTRAS_IDENTITIES_DIR}
  echo "// this is a dummy file" >> ${SRC_IDENTITIES_DIR}/mnemonic.h
  echo "// this is a dummy file" >> ${SRC_IDENTITIES_DIR}/mnemonic.cpp

  echo -e "Moving 'identites' headers.\n"
  mv ${INCLUDE_IDENTITIES_DIR}/address.h    ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/privatekey.h ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/publickey.h  ${SRC_IDENTITIES_DIR}
  mv ${INCLUDE_IDENTITIES_DIR}/wif.h        ${SRC_IDENTITIES_DIR}

  echo -e "Moving 'networks' headers.\n"
  mv ${INCLUDE_NETWORKS_DIR}/abstractnetwork.h  ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/devnet.h           ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/mainnet.h          ${SRC_NETWORKS_DIR}
  mv ${INCLUDE_NETWORKS_DIR}/testnet.h          ${SRC_NETWORKS_DIR}

  echo -e "Moving 'transactions' headers.\n"
  mv ${INCLUDE_TRANSACTIONS_DIR}/builder.h      ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/deserializer.h  ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/serializer.h   ${SRC_TRANSACTIONS_DIR}
  mv ${INCLUDE_TRANSACTIONS_DIR}/transaction.h ${SRC_TRANSACTIONS_DIR}

  echo -e "Backing up and removing the 'lib' directory.\n"
  mv ${SRC_LIB_DIR}/* ${EXTRAS_BACKUP_DIR}
  echo

  echo -e "Removing old directories 🗑\n"
  rm -rf ${INCLUDE_DIR}
  rm -rf ${SRC_DIR}/lib

  echo -e "****************************************\n"

  echo -e "\nAll Done!\n👏👏👏👏👏\n"
  echo -e "\nYou can now use Cpp-Crypto with the Arduino IDE 👍\n\n"
  exit 0

else
  # This will run if headers are already in the 'src' directory tree.
  echo -e "****************************************\n"

  echo -e "Creating the 'include' directory tree 🗂\n"
  mkdir ${INCLUDE_DIR}
  mkdir ${INCLUDE_CRYPTO_DIR}
  mkdir ${INCLUDE_CONFIGURATION_DIR}
  mkdir ${INCLUDE_ENUMS_DIR}
  mkdir ${INCLUDE_HELPERS_DIR}
  mkdir ${INCLUDE_ENCODING_DIR}
  mkdir ${INCLUDE_IDENTITIES_DIR}
  mkdir ${INCLUDE_NETWORKS_DIR}
  mkdir ${INCLUDE_TRANSACTIONS_DIR}

  echo -e "Moving 'arkCrypto.h' back to the 'include/cpp-crypto/' directory.\n"
  mv ${SRC_DIR}/arkCrypto.h ${INCLUDE_CRYPTO_DIR}

  echo -e "Moving 'configuration' headers.\n"
  mv ${SRC_CONFIGURATION_DIR}/fee.h     ${INCLUDE_CONFIGURATION_DIR}
  mv ${SRC_CONFIGURATION_DIR}/network.h ${INCLUDE_CONFIGURATION_DIR}

  echo -e "Moving 'enums' headers.\n"
  mv ${SRC_ENUMS_DIR}/fees.h  ${INCLUDE_ENUMS_DIR}
  mv ${SRC_ENUMS_DIR}/types.h ${INCLUDE_ENUMS_DIR}

  echo -e "Moving 'helpers/encoding' headers.\n"
  mv ${SRC_ENCODING_DIR}/der.h ${INCLUDE_ENCODING_DIR}
  mv ${SRC_ENCODING_DIR}/hex.h ${INCLUDE_ENCODING_DIR}

  echo -e "Moving 'identities' headers.\n"
  mv ${SRC_IDENTITIES_DIR}/address.h    ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/mnemonic.h   ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/privatekey.h ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/publickey.h  ${INCLUDE_IDENTITIES_DIR}
  mv ${SRC_IDENTITIES_DIR}/wif.h        ${INCLUDE_IDENTITIES_DIR}

  echo -e "Moving 'networks' headers.\n"
  mv ${SRC_NETWORKS_DIR}/abstractnetwork.h  ${INCLUDE_NETWORKS_DIR}
  mv ${SRC_NETWORKS_DIR}/devnet.h           ${INCLUDE_NETWORKS_DIR}
  mv ${SRC_NETWORKS_DIR}/mainnet.h          ${INCLUDE_NETWORKS_DIR}
  mv ${SRC_NETWORKS_DIR}/testnet.h          ${INCLUDE_NETWORKS_DIR}

  echo -e "Moving 'transactions' headers.\n"
  mv ${SRC_TRANSACTIONS_DIR}/builder.h      ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/deserializer.h ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/serializer.h   ${INCLUDE_TRANSACTIONS_DIR}
  mv ${SRC_TRANSACTIONS_DIR}/transaction.h  ${INCLUDE_TRANSACTIONS_DIR}

  ## 'bip39' library is not supported in Arduino
  echo -e "Restoring 'mnemonic.h'.\n"
  rm -rf ${SRC_IDENTITIES_DIR}/mnemonic.h
  rm -rf ${SRC_IDENTITIES_DIR}/mnemonic.cpp
  mv ${EXTRAS_IDENTITIES_DIR}/mnemonic.h    ${INCLUDE_IDENTITIES_DIR}
  mv ${EXTRAS_IDENTITIES_DIR}/mnemonic.cpp  ${SRC_IDENTITIES_DIR}
  rm -rf ${EXTRAS_IDENTITIES_DIR}/mnemonic.cpp

  echo -e "Restoring the 'lib' directory.\n"
  mkdir ${SRC_DIR}/lib
  mv ${EXTRAS_BACKUP_DIR}/* ${SRC_DIR}/lib
  echo

  echo -e "Removing old directories 🗑\n"
  rm -rf ${SRC_ENUMS_DIR}
  rm -rf ${EXTRAS_BACKUP_DIR}

  echo -e "****************************************\n"

  echo -e "\nAll Done!\n👏👏👏👏👏\n"
  echo -e "\nArduino IDE compatibility has been reverted 👍\n\n"
  exit 0

fi
