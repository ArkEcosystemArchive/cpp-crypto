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

#include "common/configuration.hpp"
#include "common/fee_policy.hpp"
#include "common/network.hpp"

#include "defaults/fee_policies.hpp"
#include "defaults/static_fees.hpp"
#include "defaults/transaction_types.hpp"

#include "identities/address.h"
#include "identities/privatekey.h"
#include "identities/publickey.h"
#include "identities/wif.h"

#include "networks/devnet.hpp"
#include "networks/mainnet.hpp"
#include "networks/testnet.hpp"

#include "transactions/builder.h"
#include "transactions/deserializer.h"
#include "transactions/serializer.h"
#include "transactions/transaction.h"

#include "utils/message.h"
#include "utils/slot.h"

using namespace Ark::Crypto;
using namespace Ark::Crypto::Identities;
using namespace Ark::Crypto::Transactions;
using namespace Ark::Crypto::Utils;

#endif
