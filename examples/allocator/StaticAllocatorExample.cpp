#include <iostream>
#include "../../src/StaticAllocatorPool.h"

using namespace std;

int main(){
    StaticAllocatorPool<16, 2> pool;

    auto *array =  (char*)pool.Allocate();

    array[0] = 'H';
    array[1] = 'e';
    array[2] = 'l';
    array[3] = 'l';
    array[4] = 'o';
    array[5] = '\0';

    cout << (void *) &array[0] << endl;
    cout << array << endl;

    auto *array2 =  (char*)pool.Allocate();

    array2[0] = 'B';
    array2[1] = 'y';
    array2[2] = 'e';
    array2[3] = 'e';
    array2[4] = 'e';
    array2[5] = '\0';

    /*
     * Based on the address of array1 and array2, they are spaced by 16 which
     * makes sense because it is a pool and block size is fixed
     */

    cout << (void *) &array2[0] << endl;
    cout << array2 << endl;
}