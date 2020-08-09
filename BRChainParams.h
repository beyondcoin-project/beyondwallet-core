//
//  BRChainParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRChainParams_h
#define BRChainParams_h

#include "BRMerkleBlock.h"
#include "BRSet.h"
#include <assert.h>

typedef struct {
    uint32_t height;
    UInt256 hash;
    uint32_t timestamp;
    uint32_t target;
} BRCheckPoint;

typedef struct {
    const char * const *dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRSet *blockSet); // blockSet must have last 2016 blocks
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;

static const char *BRMainNetDNSSeeds[] = {
    "", NULL}; // testing

static const char *BRTestNetDNSSeeds[] = {
    "", NULL // testing
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
    {      0, uint256("0a9e3b5fce3aee6e04f06dfd6ad380a6c0f9d8420f53a4ca97845756ee5d56e7"), 1568521797, 0x1e0ffff0 }
    //{   2016, uint256("4634e6d5576aaeac9962aa71d4a14cbea593cbe2ee8dec3b35013c433a90e2e1"), 1570633800, 0x1e0fffff },
    //{   4023, uint256("069e7c1ee71176920f1dcf03d8d6b0d39c811873d8e0a912ffbf96db235307a1"), 1570646425, 0x1e03ffff },
    //{   6048, uint256("6690d77629136b546eace011747986e3f8e5262ba0f880713b7a6f086e0b278b"), 1570716172, 0x1e00ffff },
    //{   8064, uint256("a74124dc8802f31a37d86777b6d972ab7b825d28f351ef3366d85aa48218b846"), 1570792715, 0x1d40ed0d },
    //{  10080, uint256("8995e6b36b94eb3bcc6258d65fc13b95f03115fee10a3c0e1593e58130f38783"), 1570829483, 0x1d103b43 },
    //{  12096, uint256("161dd4ef5904c58c42b8ca1854bcc1ad7d26e346293b31d7f0bee706ee87394a"), 1570846408, 0x1d040ed0 },
    //{  14112, uint256("0efac2da1f2aba9329dca6884898630c11a87010125b418983be7fef13601c58"), 1570861725, 0x1d0103b4 },
    //{  16128, uint256("59d2bbf3ea2f0094dc1bd2924f82df18f4b04832c7b0c54182eb814ee0cae7c9"), 1570875878, 0x1c40ed00 },
    //{  18144, uint256("97d3e636460acb36a5f65ef84c92b4fa1f0902026a98027253bfd9e80f06742c"), 1570890961, 0x1c103b40 },
    //{  20160, uint256("4ac036e3b7b06eb9c1598e95ca9894054c987d86635b0c00ea6386aebdbeff38"), 1570934455, 0x1c040ed0 },
    //{  28224, uint256("f8a1baa91a81fbede774878982b540d56cee4bbbfa8e5d6ce7e03d030172dd09"), 1572954650, 0x1c01fb29 },
    //{  36288, uint256("3c4891e8bda65bbd45e6f7ab63d257afaffd04fa341f7f6afd2d765b14486356"), 1574464167, 0x1c01eb6b },
    //{  44352, uint256("a93d5e64828d81f398942528fa8117758586248d63c2601120373f3c60df4929"), 1575501882, 0x1b5eb500 },
    //{  52416, uint256("48525f181fef67737ae4902b0602e412ff98c42521f9f2f0e96e2bc8d027abf2"), 1577639536, 0x1c00f859 },
    //{  60480, uint256("bd3e841ad2cbbd522e1e92d617dcae2e5c226457ef1330e82db1b06c04230e14"), 1580063537, 0x1c02c300 },
    //{  68544, uint256("9a68906949af97eceb4a2633f7699f3db6538a0d87c46bf1787297dacf723041"), 1582956753, 0x1c033aeb },
    //{  76608, uint256("912f4fcf66197b901a1b0b2e8b78f1de10087a1515e7e1403a77e1bf3094cfcd"), 1584187558, 0x1c01d483 }
};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    {       0, uint256("e4c23a189582c0a7719569717bfeb59b478a20367c5b36dd6fb18b7df4ecab51"), 1568522508, 0x1e0ffff0 }
};

static int BRMainNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    // const BRMerkleBlock *previous, *b = NULL;
    // uint32_t i;

    // assert(block != NULL);
    // assert(blockSet != NULL);

    // // check if we hit a difficulty transition, and find previous transition block
    // if ((block->height % BLOCK_DIFFICULTY_INTERVAL) == 0) {
    //     for (i = 0, b = block; b && i < BLOCK_DIFFICULTY_INTERVAL; i++) {
    //         b = BRSetGet(blockSet, &b->prevBlock);
    //     }
    // }

    // previous = BRSetGet(blockSet, &block->prevBlock);
    // return BRMerkleBlockVerifyDifficulty(block, previous, (b) ? b->timestamp : 0);
    return 1;
}

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRMainNetParams = {
    BRMainNetDNSSeeds,
    10333,       // standardPort
    0x81d7e2b7,  // magicNumber
    0,           // services
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints) / sizeof(*BRMainNetCheckpoints)};

static const BRChainParams BRTestNetParams = {
    BRTestNetDNSSeeds,
    14333,      // standardPort
    0x81d7e2b7, // magicNumber
    0,          // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints) / sizeof(*BRTestNetCheckpoints)};

#endif // BRChainParams_h
