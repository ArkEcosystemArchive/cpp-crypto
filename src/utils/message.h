/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "helpers/helpers.h"
#include "helpers/encoding/hex.h"
#include "helpers/crypto.h"

#include "identities/publickey.h"
#include "identities/privatekey.h"

#include "bcl/CurvePoint.hpp"
#include "bcl/Sha256Hash.hpp"
#include "bcl/Sha256.hpp"
#include "bcl/Uint256.hpp"

#include "rfc6979/rfc6979.h"

#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace Ark::Crypto::Identities;

namespace Ark {
namespace Crypto {
namespace Utils {

/**
 * This is the message class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class Message
{
    public:
        std::string message;
        PublicKey publicKey;
        std::vector<uint8_t> signature;

        Message(std::string msg, PublicKey pubKey, std::vector<uint8_t> sig);
        Message() : signature( std::vector<uint8_t>(142) ) {};

        bool sign(std::string newMessage, const char *const passphrase);
        bool verify();

        std::vector<std::pair<const char *const, std::string>> toArray();
        std::string toJson();
        std::string toString();
};
/**/
};
};
};

#endif
