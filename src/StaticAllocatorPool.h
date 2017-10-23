#ifndef FIXED_MEMORY_ALLOCATORPOOL_H
#define FIXED_MEMORY_ALLOCATORPOOL_H

#include "Allocator.h"

/*!
 * Template class to create static memory pools
 *
 * @tparam blockSize size of memory block
 * @tparam numBlocks number of memory blocks
 */
template <int blockSize, int numBlocks>
class StaticAllocatorPool : public Allocator{
private:
    const size_t m_poolSize = blockSize * numBlocks;
    char m_memory[blockSize * numBlocks];
public:
    StaticAllocatorPool() : Allocator(blockSize, m_memory, blockSize * numBlocks, Allocator::STATIC){}
};

#endif //FIXED_MEMORY_ALLOCATORPOOL_H
