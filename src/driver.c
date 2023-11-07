#include "../include/common.h"
#include "../include/array_tools.h"
#include "../include/para_quicksort.h"
#include "../include/partition.h"

int main(uint64_t argc, char* argv[])
{
    omp_set_num_threads(1);
    uint64_t testArr[5] = {5,6,4,7,3}; // should produce 10101

    printf("main - calling para_quicksort...\n");
    para_quicksort(testArr, 0, 5);

    printf("main - sorted array:\n");
    print_arr(testArr, 5);
    
    return 0;
}