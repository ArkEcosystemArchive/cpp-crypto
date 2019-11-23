/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include "gtest/gtest.h"

#include "identities/keys.hpp"

#include "types/fixtures/common.hpp"
#include "types/fixtures/transfer.hpp"
#include "types/fixtures/second_signature.hpp"
#include "types/fixtures/delegate_registration.hpp"
#include "types/fixtures/vote.hpp"
#include "types/fixtures/ipfs.hpp"
#include "types/fixtures/multi_payment.hpp"
#include "types/fixtures/delegate_resignation.hpp"
#include "types/fixtures/htlc_lock.hpp"
#include "types/fixtures/htlc_claim.hpp"
#include "types/fixtures/htlc_refund.hpp"

#include "transactions/transaction_data.hpp"
#include "transactions/transaction.hpp"

#include "utils/hex.hpp"
#include "utils/platform.h"

#include "test_helpers.h"

////////////////////////////////////////////////////////////////////////////////

using namespace Ark::Crypto;
using namespace Ark::Crypto::transactions;

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, constructor_default) {
    Transaction transaction;
    ASSERT_FALSE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, get_id) {
    Transaction transaction;

    transaction.data.network                     = COMMON_MAINNET;
    transaction.data.typeGroup                   = COMMON_TYPEGROUP;
    transaction.data.type                        = TYPE_0_TYPE;
    transaction.data.nonce                       = COMMON_NONCE;

    memmove(&transaction.data.senderPublicKey,
            COMMON_PUBLICKEY,
            PUBLICKEY_COMPRESSED_LEN);

    transaction.data.fee                         = TYPE_0_FEE;

    transaction.data.asset.transfer.amount       = TYPE_0_AMOUNT;
    transaction.data.asset.transfer.expiration   = TYPE_0_EXPIRATION;

    memmove(&transaction.data.asset.transfer.recipientId,
            TYPE_0_RECIPIENT,
            sizeof(TYPE_0_RECIPIENT));

    transaction.data.signature.insert(
            transaction.data.signature.begin(),
            TYPE_0_SIGNATURE,
            TYPE_0_SIGNATURE + sizeof(TYPE_0_SIGNATURE));

    ASSERT_TRUE(array_cmp(TYPE_0_TX_ID,
                          transaction.getId().data(),
                          sizeof(TYPE_0_TX_ID)));

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, sign) {
    Transaction transaction;

    transaction.data.network                     = COMMON_MAINNET;
    transaction.data.typeGroup                   = COMMON_TYPEGROUP;
    transaction.data.type                        = TYPE_0_TYPE;
    transaction.data.nonce                       = COMMON_NONCE;

    memmove(&transaction.data.senderPublicKey,
            COMMON_PUBLICKEY,
            PUBLICKEY_COMPRESSED_LEN);

    transaction.data.fee                         = TYPE_0_FEE;

    transaction.data.asset.transfer.amount       = TYPE_0_AMOUNT;
    transaction.data.asset.transfer.expiration   = TYPE_0_EXPIRATION;

    memmove(&transaction.data.asset.transfer.recipientId,
            TYPE_0_RECIPIENT,
            sizeof(TYPE_0_RECIPIENT));

    transaction.sign("this is a top secret passphrase");

    ASSERT_TRUE(array_cmp(TYPE_0_TX_ID,
                          transaction.getId().data(),
                          sizeof(TYPE_0_TX_ID)));

    ASSERT_TRUE(array_cmp(TYPE_0_SIGNATURE,
                          transaction.data.signature.data(),
                          sizeof(TYPE_0_SIGNATURE)));

    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, sign_second) {
    Transaction transaction;

    transaction.data.network                     = COMMON_MAINNET;
    transaction.data.typeGroup                   = COMMON_TYPEGROUP;
    transaction.data.type                        = TYPE_0_TYPE;
    transaction.data.nonce                       = COMMON_NONCE;

    memmove(&transaction.data.senderPublicKey,
            COMMON_PUBLICKEY,
            PUBLICKEY_COMPRESSED_LEN);

    transaction.data.fee                         = TYPE_0_FEE;
    transaction.data.asset.transfer.amount       = TYPE_0_AMOUNT;
    transaction.data.asset.transfer.expiration   = TYPE_0_EXPIRATION;

    memmove(&transaction.data.asset.transfer.recipientId,
            TYPE_0_RECIPIENT,
            sizeof(TYPE_0_RECIPIENT));

    transaction.sign("this is a top secret passphrase");

    const auto secondPassphrase = "this is a top secret passphrase too";
    transaction.secondSign(secondPassphrase);

    const auto keys = identities::Keys::fromPassphrase(secondPassphrase);

    ASSERT_TRUE(transaction.verify());

    ASSERT_TRUE(transaction.secondVerify(keys.publicKey.data()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, deserialize) {
    Transaction transaction;
    ASSERT_TRUE(transaction.deserialize(TYPE_0_BYTES));
    ASSERT_TRUE(transaction.verify());
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, serialize) {
    Transaction transaction;

    ASSERT_TRUE(transaction.deserialize(TYPE_0_BYTES));

    ASSERT_TRUE(array_cmp(TYPE_0_BYTES.data(),
                          transaction.serialize().data(),
                          TYPE_0_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, to_bytes) {
    Transaction transaction;

    ASSERT_TRUE(transaction.deserialize(TYPE_0_BYTES));
    
    ASSERT_TRUE(array_cmp(TYPE_0_BYTES.data(),
                          transaction.toBytes().data(),
                          TYPE_0_BYTES.size()));
}

////////////////////////////////////////////////////////////////////////////////

TEST(transactions_transaction, to_map_to_json) {  // NOLINT
    Transaction transferTx;
    transferTx.deserialize(TYPE_0_BYTES);
    const auto transferJson = transferTx.toJson();
    const std::string transferResponse = R"({"version":2,"network":23,"type":0,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"10000000","amount":"1","expiration":0,"recipientId":"AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff","signature":"3045022100d55051f5aec7d894afb987d582e63e0157b7a6e0cb8eff1d70ac81cbbb1382e90220294b89acb106e811b48a072a555915bea4aa0fc63c4210ad90115d1220b31b7d","id":"aafbacad9b75fa664c9cecae6de552833d4c2ab6f857573cf492eafcebfd1551"})";
    ASSERT_STREQ(transferResponse.c_str(), transferJson.c_str());

    Transaction secondSignatureTx;
    secondSignatureTx.deserialize(TYPE_1_BYTES);
    const auto secondSignatureJson = secondSignatureTx.toJson();
    const std::string secondSignatureResponse = R"({"version":2,"network":23,"type":1,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"500000000","asset":{"signature":{"publicKey":"02877e4f35c76abaeb152b128670db0a7ae10b3999afcd28a42938b653fbf87ae9"}},"signature":"304402201786b482215f6f63e3a9414324283decffc64b829209640024a4e78d7ed557f50220197e53c8e8b7f8a645eb82712587926ad930695a8ca43a2308ca0a9dbeabb65b","id":"6934f7a73846b2daeb94e70b3b8a23118410cb552ada5993bf1b47b10e168916"})";
    ASSERT_STREQ(secondSignatureResponse.c_str(), secondSignatureJson.c_str());

    Transaction delegateRegistrationTx;
    delegateRegistrationTx.deserialize(TYPE_2_BYTES);
    const auto delegateRegistrationJson = delegateRegistrationTx.toJson();
    const std::string delegateRegistrationResponse = R"({"version":2,"network":23,"type":2,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"2500000000","asset":{"delegate":{"username":"arkdelegate"}},"signature":"30440220281812ca558b3b032aaf724aeaba5e20733e87f20fefe1c78536cc523de7e475022038a2454ca2665f6c3d910b04ecdd5995a7d82904f9f4bf878402a31262d2db61","id":"668f5db0d99189ee7dd85c991360ca19372302a13e3046511a60d115dbf1864e"})";
    ASSERT_STREQ(delegateRegistrationResponse.c_str(), delegateRegistrationJson.c_str());

    Transaction voteTx;
    voteTx.deserialize(TYPE_3_BYTES);
    const auto voteJson = voteTx.toJson();
    const std::string voteResponse = R"({"version":2,"network":23,"type":3,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"100000000","asset":{"votes":["+034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192"]},"signature":"3045022100dfa4edd1fb7bc587eb277dd996ab0dde73dc4942a293e5634bd48be9c7d25880022025c91f30c88f49bc3ed77614749c0c439f0759457a4bf22ed5c97f338659ccee","id":"ca544581927728ae03a63f088e76053f357dc8fb0422512bb8a7c6a0f7ae16cf"})";
    ASSERT_STREQ(voteResponse.c_str(), voteJson.c_str());

    // Transaction multiSignatureTx;  // TODO

    Transaction ipfsTx;
    ipfsTx.deserialize(TYPE_5_BYTES);
    const auto ipfsJson = ipfsTx.toJson();
    const std::string ipfsResponse = R"({"version":2,"network":23,"type":5,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"500000000","asset":{"ipfs":"QmYSK2JyM3RyDyB52caZCTKFR3HKniEcMnNJYdk8DQ6KKB"},"signature":"30440220636aa75a15bcc59c9cf2db11ae7f9ed73f112b6ca14cc2aca1b6ed3d2daadaad02207434f5c6d17c98350942afafbaa57b6518ea4e78e8443f414398190183235787","id":"f68875f1fa80091ef42dec05c5c6a0ea77f4b83934f7eed0d1c72b910ddf6d03"})";
    ASSERT_STREQ(ipfsResponse.c_str(), ipfsJson.c_str());

// This MultiPayment is currently way too big for IoT.
// The MultiPayment type is supported on IoT;
// however, the limit is considerably less than the Network supports
// and is ultimately dependent on your working environment.
#ifndef USE_IOT
    Transaction multiPaymentTx;
    multiPaymentTx.deserialize(TYPE_6_BYTES);
    const auto multiPaymentJson = multiPaymentTx.toJson();

    const std::string multiPaymentResponse = R"({"version":2,"network":30,"type":6,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"10000000","asset":{"payments":[{"amount":"1","recipientId":"DHKxXag9PjfjHBbPg3HQS5WCaQZdgDf6yi"},{"amount":"1","recipientId":"DBzGiUk8UVjB2dKCfGRixknB7Ki3Zhqthp"},{"amount":"1","recipientId":"DFa7vn1LvWAyTuVDrQUr5NKaM73cfjx2Cp"},{"amount":"1","recipientId":"DSGsxX84gif4ipAxZjjCE2k2YpHmsNTJeY"},{"amount":"1","recipientId":"DQhzMRvVoCYCiZH2iSyuqCTcayz7z4XTKx"},{"amount":"1","recipientId":"DMSD6fFT1Xcxh4ErYExr5MtGnEuDcYu22m"},{"amount":"1","recipientId":"D7HCZG8hJuJqu9rANRdyNr6N1vpH2vbyx8"},{"amount":"1","recipientId":"DQy6ny2bkvWiDLboQMZ1cxnmoNC5JM228w"},{"amount":"1","recipientId":"D7EUgmA78qUaSfsNedfgKs2ALq28FhL3zo"},{"amount":"1","recipientId":"DEHyKHdtzHqTghfpwaBcvTzLpgPP5AAUgE"},{"amount":"1","recipientId":"DBgA92a616rwVi9GsgYUwBq9Y7dgvZiC41"},{"amount":"1","recipientId":"DPXaJv1GcVpZPvxw5T4fXebqTVhFpfqyrC"},{"amount":"1","recipientId":"D6JpPhN7BehrhNy7AbSQ2u9mkSZb1k7Ens"},{"amount":"1","recipientId":"D9sdJ42YtJpXeL7Fa1cTLiciW7FpGYqms4"},{"amount":"1","recipientId":"DJq86RdmTMKC257szcXRXKpbuoYPaL8KgL"},{"amount":"1","recipientId":"DMsQKioFXniGH3vHDNfkQLRRqsQsAS46Cy"},{"amount":"1","recipientId":"DHwPoAP8cMP9ZeKrhh5c99WzaoJqFKW2qi"},{"amount":"1","recipientId":"DAwN6Pp4ErGf69EypErrbtuWFfEMtuSzmE"},{"amount":"1","recipientId":"DQ6sE3jE9rTFC13e2ndooRdy5YCYinLbPm"},{"amount":"1","recipientId":"DFuo2NGezzHGwHjzG6c21JuJ9WpntLGFER"},{"amount":"1","recipientId":"D6qzeJEGG7rEBem5bNCCZqHtPCBtzsUZpP"},{"amount":"1","recipientId":"DNVhLKTPh4LnqhcnkogNS8iSxmsnFG17tC"},{"amount":"1","recipientId":"D8EPxx42Dr4bd8xXRbMHi8LHefFLaT2VaM"},{"amount":"1","recipientId":"DBK4VPsUQHUYkGc47FqF69PEyPjjqvnGzu"},{"amount":"1","recipientId":"D7XtDDKh2VrRtz5rtbBicfgSEoEQzEZiNx"},{"amount":"1","recipientId":"D9gQjhu2tDUstXfrbK85zHi23VtAk72qsS"},{"amount":"1","recipientId":"DKhfkyY4RZyxR7CFjQAeNtGKXAaVEBa9HK"},{"amount":"1","recipientId":"DMCBerfV13HBuJEwJTZRVTWzrYDxgb3QSy"},{"amount":"1","recipientId":"DLCoxbHdf9LMhEavEnj8mGv4AwVk8eEiKd"},{"amount":"1","recipientId":"D5taz6B4xDk1LD3jV4fYrUhaKC8DnTtziW"},{"amount":"1","recipientId":"DDb3EXY3refv2f5ymMME3hp2DXFqMPzGah"},{"amount":"1","recipientId":"D5HydybffvfuwdbBKQ1dnhiXzNnWq6CgQz"},{"amount":"1","recipientId":"D9DMKvx8fDyWyAP1EUGs5McBwwv3y5E1Yn"},{"amount":"1","recipientId":"DHXqndno9dBvGabhc7NdZWuoj6nRUdSaP7"},{"amount":"1","recipientId":"DJAmJiuLQGnzXWmH7KvosVLks7hhfxQ8np"},{"amount":"1","recipientId":"D752ZwkQZKm5gYYMUZV2tKFFZZaD35MtRa"},{"amount":"1","recipientId":"D6Xe5kVsK7axaPZ1tP2fVWaLFubyCajkVq"},{"amount":"1","recipientId":"D9yDJNK4xHP9Gx27s187Z5XHcNF5YFA94h"},{"amount":"1","recipientId":"DJuZC2smL8j86bUNrZiNceAubad3zs3drS"},{"amount":"1","recipientId":"DRUVFo5MjNrMHHQCwpVPH6AwLL2AULpgbH"},{"amount":"1","recipientId":"DNM5wLmqVUz6UgY14mt6BsMndy8JGcFwct"},{"amount":"1","recipientId":"DHMd77xyB8f6DnSCgxaRWfuM86cwyH76EH"},{"amount":"1","recipientId":"DFmg9q2KqGyretLazvRjWdynJAZbPkZPG2"},{"amount":"1","recipientId":"DMnY8QWLAmsb4wNEjRVvtQsNWF4SbXntxM"},{"amount":"1","recipientId":"DBMn94FxVB36nXgzbmtmfu6jVEGwwHNyNA"},{"amount":"1","recipientId":"DUD3r46LtArk4msu6jFrwn1hjxbZoXzX9t"},{"amount":"1","recipientId":"DFUNVTBd5zFexBaHkymr4UJqsHeXhPLKUF"},{"amount":"1","recipientId":"DFtCxvMSsF9qfw2mH1aNHxusXGJ2QzCahP"},{"amount":"1","recipientId":"D8LiYnmH4DLDyxCLTV7RrqxtCA21pfGkb9"},{"amount":"1","recipientId":"DASUgX1U7yvp8WDQ57QoTEUim6bqTYzxGw"},{"amount":"1","recipientId":"D5iNaf5ZckhdZivPfy6vFvBLeBDJtvDoGo"},{"amount":"1","recipientId":"DPrdeuFDcfMujvYK6n18RBAWgh7hYeiDeZ"},{"amount":"1","recipientId":"D9oaC7bd2YaJYHDdGkUdyAnfpkBrFFKZHy"},{"amount":"1","recipientId":"DUTUfseKR6qJRjqCuxeH3oRxMr6EFLUxRW"},{"amount":"1","recipientId":"DTYv1v3YdUNy81kzD1VhRx6e8jkDYnvCoh"},{"amount":"1","recipientId":"DE1BK8iL17PiBwo9TUCfkkm1vnUkobBwj8"},{"amount":"1","recipientId":"D7Ba6DnbpPJgqVnQNdN7baRsZs1DKvptMM"},{"amount":"1","recipientId":"DUBcre2e5KMykYr6xK56T5BrwkKMZkUF8r"},{"amount":"1","recipientId":"DPeqoTgBbRhyuEJtMnhqhSAeK32ymMNvjd"},{"amount":"1","recipientId":"DGmToX3GrCEUC8EJdZrXWTYFNWqQz1VVhX"},{"amount":"1","recipientId":"DArHKTMXf3F5zXS1i3GSwni9aA8TX1yQvh"},{"amount":"1","recipientId":"DTgcCvAYR2XdzUHv4WuEB6aShYEbh2MYp6"},{"amount":"1","recipientId":"DFLY9huetM6GMrt9EGp6sXDEiC7r3oSYHg"},{"amount":"1","recipientId":"DEszKKqdRipXiF7BDKS2Q4iJwwfzLdwADK"},{"amount":"1","recipientId":"DF45FRKUYcyUGeZyyTF3sCYJ8VFNXymzhJ"},{"amount":"1","recipientId":"DJb6jvhSvw2RmxCBEQSAzG6tjUs5rK3a5m"},{"amount":"1","recipientId":"DCqqT4x4on1dsbgUKRWkuZsdZaoohYK6NV"},{"amount":"1","recipientId":"D9SAVjqkxwWQmb82iqAedJPccFjDUnMSi9"},{"amount":"1","recipientId":"DBvXesEgzrAsm9YrzRb2jithR2hg7SZpuq"},{"amount":"1","recipientId":"DF5ZYcQsmgDvH6cVQR87xvXapyTUFB1a5R"},{"amount":"1","recipientId":"DQEfNNsJ6PQTA9abwWdiunPuebLZAhxbpZ"},{"amount":"1","recipientId":"DP6k5YTtaeNJUHZ72H6QtugFaHVB5vEBQe"},{"amount":"1","recipientId":"DJBTrPo6sDMGr2kcswTwDWtQyYV5adqnAp"},{"amount":"1","recipientId":"DMHtTBMyG5qGYgcZNRkb36XaCT3TUSKmYE"},{"amount":"1","recipientId":"DTbCpyVgTeJw4idpqbY5jwrEi7SxSid9GU"},{"amount":"1","recipientId":"D75g1ztcaHi46eUFRnakRryqG7GV9xsgGC"},{"amount":"1","recipientId":"DSkMiPrEx3YF6ijDjxhwCnbAbriC8sWKEW"},{"amount":"1","recipientId":"D7BHGU3UedoxpZko4nBLcz5oRtSmUmRfy6"},{"amount":"1","recipientId":"DQZUzueTvUJb5tnhBCziPYaMnzaoui4F57"},{"amount":"1","recipientId":"DGCCpnJ86YvxJAkHRPhC5jTBNGsy5PEDRh"},{"amount":"1","recipientId":"DHSW3vi66L63xnzRt9PadwSVrb9bCKhgvJ"},{"amount":"1","recipientId":"D6eAmMh6FFynorCSjHS1Qx75rXiN89soa7"},{"amount":"1","recipientId":"DGPoaSg15fb6As8bPKBAQrK3nCDpgfYow8"},{"amount":"1","recipientId":"DKPmC4G1ZEwxb5hZro2sJwRWJ1pQixcK6N"},{"amount":"1","recipientId":"DFpBcXzcJdFaN9rfVD8Nc5yWFvJ3DnePwa"},{"amount":"1","recipientId":"DKxQ9FDTBDQaLLV24sWc625w2Kycw2RoqR"},{"amount":"1","recipientId":"DNZr7NxGm97r8hV6Jg4rv3S5MgJrEVUWNQ"},{"amount":"1","recipientId":"DBBbtnKKDAW84bDjywEmQFLgwf36DxJHZJ"},{"amount":"1","recipientId":"DA7GfDKG5zYFeiZ1C4FPJBeTajpYNvXxcC"},{"amount":"1","recipientId":"DPAsWQyuxYkiMRzhngKBPTpWb6WWqxdd1T"},{"amount":"1","recipientId":"DTv6qvhUK1jks58gAA5YFzShHf3YX9sJVo"},{"amount":"1","recipientId":"DDwTm5FbgvWugYekvjE1dzantAVKxtGbNo"},{"amount":"1","recipientId":"DTno4QZdEyAokZHxQZcYrErqMLVE19PgCb"},{"amount":"1","recipientId":"D5xRcwzEGSN83nyuGN74Sw8f353vDmm2tt"},{"amount":"1","recipientId":"DC1hKDKyFbtMhiTc79mmPS99SJnQLsvvH3"},{"amount":"1","recipientId":"DM1pVjbHA3Q4dezcwGBjmT54cLYqpx1NtZ"},{"amount":"1","recipientId":"DFEMw6jihEKRJ9CT3k8Rj73PLKDGDyQLU1"},{"amount":"1","recipientId":"D5nTPSQFkt9W6mNzdy5ks5PiHkhDqswxDY"},{"amount":"1","recipientId":"DMca1DGMxj8w59dWYmji1YC1xLP7AmL6rA"},{"amount":"1","recipientId":"DM6emC4WnxyP2RzrNW5VMS2n3sNfz6Xpci"}]},"signature":"3045022100a6c327cb6798cb3dc8b282b64358dc4c24a72bff61e347009c1e0ad2a1cc6d8c022028cf62c3d0ea8c3ca6113f63b4e827bd8db8201a478f5ff40c309bbb9987a9b4","id":"c9d689827cd6c6b741ebcad601ce5218bd7df96d2bf592aa5105116b89e09f80"})";
    ASSERT_STREQ(multiPaymentResponse.c_str(), multiPaymentJson.c_str());
#endif  // #ifndef USE_IOT

    Transaction delegateResignationTx;
    delegateResignationTx.deserialize(TYPE_7_BYTES);
    const auto delegateResignationJson = delegateResignationTx.toJson();
    const std::string delegateResignationResponse = R"({"version":2,"network":23,"type":7,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"2500000000","signature":"3045022100aa113ddefb502d868219339d16b8d448c8e69c8e320664e12903cc84420c159d02201b6206c7cb9442f6ef07dd0824aeb0cc393d8f9f9909988da6687c44ef897070","id":"a8cf10c6a7d2e5c82bff0860f83f917f426bdd1ee25bd8d5dad2358973ce4ecb"})";
    ASSERT_STREQ(delegateResignationResponse.c_str(), delegateResignationJson.c_str());

    Transaction htlcLockTx;
    htlcLockTx.deserialize(TYPE_8_BYTES);
    const auto htlcLockJson = htlcLockTx.toJson();
    const std::string htlcLockResponse = R"({"version":2,"network":23,"type":8,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"10000000","amount":"1","recipientId":"AJWRd23HNEhPLkK1ymMnwnDBX2a7QBZqff","asset":{"lock":{"secretHash":"09b9a28393efd02fcd76a21b0f0f55ba2aad8f3640ff8cae86de033a9cfbd78c","expiration":{"type":1,"value":81242895}}},"signature":"3044022034491f6ee88278248c3b0ddd62b7ee0cb68e0ff93a51008899240b32d111b90a022043b10dd604f2d6256c75e50b5423612824a971c1876528af983ebb8145403e86","id":"50f301306d8da58d62332ce3a361d9fd4a01b0a89ca914517b685e2d3714e24e"})";
    ASSERT_STREQ(htlcLockResponse.c_str(), htlcLockJson.c_str());

    Transaction htlcClaimTx;
    htlcClaimTx.deserialize(TYPE_9_BYTES);
    const auto htlcClaimJson = htlcClaimTx.toJson();
    const std::string htlcClaimResponse = R"({"version":2,"network":23,"type":9,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"0","asset":{"claim":{"lockTransactionId":"50f301306d8da58d62332ce3a361d9fd4a01b0a89ca914517b685e2d3714e24e","unlockSecret":"f5ea877a311ced90cf4524cb489e972f"}},"signature":"3045022100d47a071dadebfae4e9115f35ae29429d0ada7bcb1668dc9babde9613108ecc8302201d97dd366a8816f81581dc5be46f3a859b66e48532c80fb7fa19da63dfc3c01f","id":"88b21734d289fa48801b2fed39e23b89f021df4670e8d43e703b776e5a5333a8"})";
    ASSERT_STREQ(htlcClaimResponse.c_str(), htlcClaimJson.c_str());

    Transaction htlcRefundTx;
    htlcRefundTx.deserialize(TYPE_10_BYTES);
    const auto htlcRefundJson = htlcRefundTx.toJson();
    const std::string htlcRefundResponse = R"({"version":2,"network":23,"type":10,"nonce":"1","senderPublicKey":"034151a3ec46b5670a682b0a63394f863587d1bc97483b1b6c70eb58e7f0aed192","fee":"0","asset":{"refund":{"lockTransactionId":"50f301306d8da58d62332ce3a361d9fd4a01b0a89ca914517b685e2d3714e24e"}},"signature":"30450221009b2b4d9070095d566b2570ba723c5c1935877e669eaf88f188f0fcac51fa5a4a022022e46ad51939c78b719b6ab37536d5331ea3e414a25d24776b056346fe6feb3c","id":"ff58b3f891b8395b407d21ee7c2c10aa3fe1303e815677f1fa88b399ff185ff2"})";
    ASSERT_STREQ(htlcRefundResponse.c_str(), htlcRefundJson.c_str());
}

////////////////////////////////////////////////////////////////////////////////
