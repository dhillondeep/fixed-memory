#include "Allocator.h"
#include <cstring>
#include <cmath>

Allocator::Allocator(size_t blockSize, size_t poolSize, Type allocationType, void *pPool) :
        m_poolType{allocationType},
        m_blockSize{blockSize < sizeof(Block *) ? sizeof(Block *) : blockSize},
        m_pHead{nullptr},
        m_pPool{nullptr},
        m_poolSize{poolSize},
        m_poolTotalBlockCnt{0},
        m_poolCurrBlockCnt{0},
        m_totalBlockCount{0},
        m_allocations{0},
        m_deallocations{0} {
    // if pool size is provided, we will use pool instead of dynamic heap allocations
    if (m_poolSize) {
        m_poolSize = max(m_blockSize, poolSize);

        // find the closest round number that describes the number of blocks
        m_poolTotalBlockCnt = (uint16_t) round(m_poolSize / (float) m_blockSize);
        m_poolCurrBlockCnt = m_poolTotalBlockCnt;
        m_totalBlockCount = m_poolTotalBlockCnt;

        // based on number of blocks adjust the size of pool
        m_poolSize = m_blockSize * m_totalBlockCount;

        // If caller provided an external memory pool
        if (pPool) {
            m_pPool = (Block *) pPool;
        } else {
            // create a pool
            m_pPool = (Block *) new char[m_poolSize];
        }

        memset(m_pPool, 0, m_poolSize);

        // Fill m_pPool with m_poolSize blocks
        Block *pBlock = m_pPool;
        for (uint16_t i = 1; i < m_poolTotalBlockCnt; i++) {
            pBlock = pBlock->pNext = (Block *) ((char *) pBlock + m_blockSize);
        }

        // Initially, all in Deallocate'd state
        m_pHead = m_pPool;
    }
}

Allocator::Allocator(size_t blockSize, size_t poolSize) :
        Allocator(blockSize, poolSize, DYNAMIC, nullptr) {}

Allocator::Allocator(size_t blockSize, void *pPool, size_t poolSize, Type type) :
        Allocator(blockSize, poolSize, type, pPool) {}

Allocator::~Allocator() {
    // delete non pool blocks
    if (m_totalBlockCount > m_poolTotalBlockCnt) {
        Block *pBlock = nullptr;
        while (m_pHead) {
            pBlock = m_pHead;
            if (pBlock) {
                m_pHead = m_pHead->pNext;
                if (!IsPoolBlock(pBlock)) {
                    delete[] (char *) pBlock;
                    --m_totalBlockCount;
                }
            }
        }
    }

    // only delete the pool if it is not static
    if (m_poolType != Type::STATIC) {
        // destroy the pool
        if (m_pPool) delete[] (char *) m_pPool;
    }
}

void *Allocator::Allocate() {
    // Pop one free block, if any.
    Block *pBlock = m_pHead;

    if (pBlock){
        m_pHead = m_pHead->pNext;
        --m_poolCurrBlockCnt;
    }
    else {
        // Otherwise, get a 'new' one from heap.
        pBlock = (Block *) new char[m_blockSize];
        ++m_totalBlockCount;
    }

    ++m_allocations;

    return pBlock;
}

void Allocator::Deallocate(void *pBlock) {
    if (IsPoolBlock(pBlock)) ++m_poolCurrBlockCnt;

    auto pBlock1 = (Block *) pBlock;
    pBlock1->pNext = m_pHead;
    m_pHead = pBlock1;
    ++m_deallocations;
}

