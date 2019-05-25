/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef ARKCRYPTO_H
#define ARKCRYPTO_H

#define HAS_CRYPTO

#if (defined ARDUINO || defined ESP8266 || defined ESP32)
#define USE_IOT
#endif

#include "configuration/fee.h"
#include "configuration/network.h"
#include "enums/fees.h"
#include "enums/types.h"

#include "identities/address.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"
#include "identities/wif.h"

#include "networks/abstractnetwork.h"
#include "networks/devnet.h"
#include "networks/mainnet.h"
#include "networks/testnet.h"

#include "transactions/builder.h"
#include "transactions/deserializer.h"
#include "transactions/serializer.h"
#include "transactions/transaction.h"

#include "utils/message.h"
#include "utils/slot.h"

using namespace Ark::Crypto::Configuration;
using namespace Ark::Crypto::Enums;
using namespace Ark::Crypto::Identities;
using namespace Ark::Crypto::Networks;
using namespace Ark::Crypto::Transactions;

#endif
