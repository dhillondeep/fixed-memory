#include <iostream>
#include "../../src/Memory.h"

using namespace std;

int main(){
    /*
     * Memory is initialized in the beginning so no need to call init manually.
     * Memory is also deleted at the end so no need to destroy memory manually.
     * This does not mean you should not use memory_free. This free is necessary
     */

    auto *array = (int*)memory_alloc(sizeof(int) * 3);
    array[0] = array[1] = array[2] = 75;

    cout << "address: " << array << endl;
    cout << array[0] << ", " << array[1] << ", " << array[2] << endl;

    memory_free(array);

    /*
     * Since the old array is freed the new array of the same size
     * will use the space of old array and no new space will be allocated
     */
    auto *array2 = (int*)memory_alloc(sizeof(int) * 3);
    array2[0] = array2[1] = array2[2] = 750;

    cout << "address: " << array2 << endl;
    cout << array2[0] << ", " << array2[1] << ", " << array2[2] << endl;

    memory_free(array2);

    /*
     * Since array 3 will take less space than array 1 and 2, new memory will be allocated
     * to accomodate for smaller blocks
     */
    auto *array3 = (int*)memory_alloc(sizeof(int)*2);
    array3[0] = array3[1] = 7;

    cout << "address: " << array3 << endl;
    cout << array3[0] << ", " << array3[1]  << endl;

    /*
     * Since array 3 is not free that space will not be used and another block of
     * same size will be allocated
     */
    auto *array4 = (int*)memory_alloc(sizeof(int)*2);
    array4[0] = array4[1] = 2;

    cout << "address: " << array4 << endl;
    cout << array4[0] << ", " << array4[1] << endl;

    /*
     * Since new size is being allocated, a totally new block is allocated
     */
    array4 = (int*)memory_realloc(array4, sizeof(int)*3);
    array4[0] = array4[1] = array4[2] = 2;

    cout << "address: " << array4 << endl;
    cout << array4[0] << ", " << array4[1] << ", " << array4[2] << endl;

    memory_free(array3);
    memory_free(array4);
}

