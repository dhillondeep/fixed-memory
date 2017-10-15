#include <iostream>
#include "../../src/Allocator.h"

using namespace std;

int main(){
    // create allocator with no pool
    Allocator allocator{8};

    cout << "Allocator with no pool" << endl;

    // dynamically allocated
    auto *array = (char*)allocator.Allocate();
    array[0] = array[1] = array[2] = array[3] = array[4] = array[5] = array[6] = 'h';
    array[7] = '\0';

    cout << "Num Allocations: " << allocator.GetNumAllocations() << endl;       // should be 1
    cout << "Num Pool Blocks: " << allocator.GetPoolSize() << endl;;            // should be 0
    cout << "Avail Pool Blocks: " << allocator.GetNumPoolBlocksAvail() << endl; // should be 0
    cout << "Avail Total Blocks: " << allocator.GetTotalBlocks() << endl;       // should be 1
    cout << "Is Pool member: " << allocator.IsPoolBlock(array) << endl;         // should be 0
    std::cout << array << endl;

    // memory not used from pool must always be de-allocated manually but memory from pool will be
    // de-allocated automatically if it is not from stack. It is good practice to De-allocate what
    // you allocate so that block can be recycled
    allocator.Deallocate(array);

    cout << "Num Allocations: " << allocator.GetNumDeallocations() << endl;     // should be 1

    cout << endl;
}
