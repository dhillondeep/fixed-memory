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
    cout << "Num Pool Blocks: " << allocator.GetTotalPoolBlocks() << endl;;     // should be 0
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


    // create allocator with pool
    Allocator allocator1{8, 16};

    cout << "Allocator with pool created" << endl;

    // pool allocated
    auto *array1 = (char*)allocator1.Allocate();
    array1[0] = array1[1] = array1[2] = array1[3] = array1[4] = array1[5] = array1[6] = 'a';
    array1[7] = '\0';

    cout << "Num Allocations: " << allocator1.GetNumAllocations() << endl;          // should be 1
    cout << "Num Pool Blocks: " << allocator1.GetTotalPoolBlocks() << endl;;        // should be 2
    cout << "Avail Pool Blocks: " << allocator1.GetNumPoolBlocksAvail() << endl;    // should be 1
    cout << "Avail Total Blocks: " << allocator1.GetTotalBlocks() << endl;          // should be 2
    cout << "Is Pool member: " << allocator1.IsPoolBlock(array1) << endl;           // should be 1
    std::cout << array1 << endl;

    // block available for reuse
    allocator1.Deallocate(array1);

    cout << "Num Allocations: " << allocator1.GetNumDeallocations() << endl;     // should be 1
    cout << endl;


    // create allocator with static pool provided
    char adr[18];
    Allocator allocator2{9, adr, 16, Allocator::STATIC};

    cout << "Allocator with static pool provided" << endl;

    // pool allocated
    auto *array2 = (char*)allocator2.Allocate();
    auto *anotherArray2 = (char*)allocator2.Allocate();
    array2[0] = array2[1] = array2[2] = array2[3] = array2[4] = array2[5] = array2[6] = array2[7] = 'z';
    array2[8] = '\0';

    anotherArray2[0] = anotherArray2[1] = anotherArray2[2] = anotherArray2[3] = anotherArray2[4] = anotherArray2[5] =
    anotherArray2[6] = anotherArray2[7] = 'l';
    anotherArray2[8] = '\0';

    cout << "Num Allocations: " << allocator2.GetNumAllocations() << endl;              // should be 2
    cout << "Num Pool Blocks: " << allocator2.GetTotalPoolBlocks() << endl;             // should be 2
    cout << "Avail Pool Blocks: " << allocator2.GetNumPoolBlocksAvail() << endl;        // should be 0
    cout << "Avail Total Blocks: " << allocator2.GetTotalBlocks() << endl;              // should be 2
    cout << "Is Pool member array2: " << allocator2.IsPoolBlock(array2) << endl;        // should be 1
    cout << "Is Pool member anotherArray2: " << allocator2.IsPoolBlock(array2) << endl; // should be 1
    std::cout << array2 << endl;
    std::cout << anotherArray2 << endl;

    // blocks available for reuse
    allocator2.Deallocate(array2);
    allocator2.Deallocate(anotherArray2);

    cout << "Num Allocations: " << allocator2.GetNumDeallocations() << endl;     // should be 2
    cout << endl;


    // create allocator with static pool provided
    auto *adr1 = new char[9];
    Allocator allocator3{9, adr1, 9, Allocator::DYNAMIC};

    cout << "Allocator with dynamic pool provided" << endl;

    auto *array3 = (char*)allocator3.Allocate();             // pool allocated
    auto *anotherArray3 = (char*)allocator3.Allocate();      // pool extended and dynamically created
    array3[0] = array3[1] = array3[2] = array3[3] = array3[4] = array3[5] = array3[6] = array3[7] = 'i';
    array3[8] = '\0';

    anotherArray3[0] = anotherArray3[1] = anotherArray3[2] = anotherArray3[3] = anotherArray3[4] = anotherArray3[5] =
    anotherArray3[6] = anotherArray3[7] = 'o';
    anotherArray3[8] = '\0';

    cout << "Num Allocations: " << allocator3.GetNumAllocations() << endl;                      // should be 2
    cout << "Num Pool Blocks: " << allocator3.GetTotalPoolBlocks() << endl;                     // should be 1
    cout << "Avail Pool Blocks: " << allocator3.GetNumPoolBlocksAvail() << endl;                // should be 0
    cout << "Avail Total Blocks: " << allocator3.GetTotalBlocks() << endl;                      // should be 2
    cout << "Is Pool member array2: " << allocator3.IsPoolBlock(array3) << endl;                // should be 1
    cout << "Is Pool member anotherArray2: " << allocator3.IsPoolBlock(anotherArray3) << endl;  // should be 0
    std::cout << array3 << endl;
    std::cout << anotherArray3 << endl;

    // blocks available for reuse
    allocator3.Deallocate(array3);
    allocator3.Deallocate(anotherArray3);

    cout << "Num Allocations: " << allocator3.GetNumDeallocations() << endl;     // should be 2
}
