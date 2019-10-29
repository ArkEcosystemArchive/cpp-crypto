
#include "gtest/gtest.h"

#include <map>
#include <string>


#include "transactions/builder.h"
#include "transactions/transaction.h"

using namespace Ark::Crypto::Transactions;

TEST(transactions, transaction_to_array_type_0) {  // NOLINT
  std::map<std::string, std::string> tArray;
  // Type 0 //

  { // force dtor on transfer to clean up stack space
  auto transfer = Builder::buildTransfer("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib",
                                         1,
                                         "",
                                         "Secret passphrase");

  tArray = transfer.toArray();
  }

  // Amount
  ASSERT_STREQ("1", tArray["amount"].c_str());

  // Fee
  ASSERT_STREQ("10000000", tArray["fee"].c_str());

  // Id
  ASSERT_FALSE(tArray["id"].empty());

  // Recipient
  ASSERT_STREQ("D61mfSggzbvQgTUe6JhYKH2doHaqJ3Dyib", tArray["recipient"].c_str());

  // SenderPublicKey
  ASSERT_STREQ("02f21aca9b6d224ea86a1689f57910534af21c3cc9f80602fed252c13e275f0699",
               tArray["senderPublicKey"].c_str());

  // Signature
  ASSERT_FALSE(tArray["signature"].empty());

  // Timestamp
  ASSERT_FALSE(tArray["timestamp"].empty());

  // Type
  ASSERT_STREQ("0", tArray["type"].c_str());

  // Version
  ASSERT_STREQ("1", tArray["version"].c_str());

}
