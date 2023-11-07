#include "../include/prefix_sums.h"

uint64_t* prefix_sums(uint64_t* array, uint64_t size)
{
    printf("prefix_sums - size: %u\n", size);
    if (size == 0) 
    {
        printf("prefix_sums- size 0\n");
        return array;
    }

    uint64_t expon = ceil(log2(size)); //closest power of two
    uint64_t tempSize = (uint64_t)pow(2, expon);
    printf("prefix_sums - pow: %u, tempSize: %u\n", expon, tempSize);
    if (expon == 0) 
    {
        printf("prefix_sums- expon 0\n");
        return array;
    }
    
    printf("prefix_sums - call ps_arrprep...\n");
    uint64_t* tempArr = ps_arrprep(array, size, tempSize);

    //upsweep
    printf("prefix_sums - upsweep \n");
    for (uint64_t d = 0; d < (expon-1); d++)
    {
        //print_arr(tempArr, tempSize);
        uint64_t power2pl = (uint64_t)(pow(2, d+1));
        uint64_t power2 = (uint64_t)(pow(2, d));
        #pragma omp parallel for
            for (uint64_t i = 0; i < tempSize; i += power2pl)
                tempArr[i+power2pl-1]=tempArr[i+power2-1]+tempArr[i+power2pl-1];
    }

    //downsweep
    printf("prefix_sums - downsweep \n");
    tempArr[tempSize-1] = 0;
    for (uint64_t d = (expon-1); d >= 0;)
    {
        //print_arr(tempArr, tempSize);
        uint64_t power2pl = (uint64_t)(pow(2, d+1));
        uint64_t power2 = (uint64_t)(pow(2, d));
        #pragma omp parallel for
            for (uint64_t i = 0; i < tempSize; i+=power2pl)
            {
                uint64_t t = tempArr[i+power2-1];
                tempArr[i+power2-1] = tempArr[i+power2pl-1];
                tempArr[i+power2pl-1] = t+tempArr[i+power2pl-1];
            }
        if (d == 0) break; //unsigned int 
        d--;
    }
    
    printf("prefix_sums - array at algorithm finish:\n");
    print_arr(tempArr, tempSize);

    //sometimes arrays still start at 0 after a shift left, we add one to the whole array to account for that
    if (tempArr[0] == 0)
    {
        ps_addone(tempArr, tempSize); //size in an effort to preserve the last element beyond size which holds the length of B
    }
    else
    {
        //shift left to make inclusive
        ps_shiftleft(tempArr, tempSize);
    }
    printf("prefix_sums - passing this:\n");
    print_arr(tempArr, size);
    return tempArr;
}

uint64_t* ps_arrprep(uint64_t* array, uint64_t size, uint64_t newSize)
{
    uint64_t* newArr = (uint64_t*)calloc(newSize, sizeof(uint64_t));
    #pragma omp parallel for
    for (uint64_t i = 0; i < size; i++)
    {
        newArr[i] = array[i];
    }
    printf("ps_arrprep - passed array: ");
    print_arr(array, size);
    printf("ps_arrprep - new array: ");
    print_arr(newArr, newSize);
    return newArr;
}

void ps_shiftleft(uint64_t* array, uint64_t size)
{
    printf("ps_shiftleft: shifting left...\n");
    #pragma omp parallel for
    for (uint64_t i = 0; i < size-1; i++)
    {
        array[i] = array[i+1];
    }
}

void ps_addone(uint64_t* array, uint64_t size)
{
    printf("ps_addone: adding one to every element...\n");
    #pragma omp parallel for
    for (uint64_t i = 0; i < size; i++)
    {
        array[i]++;
    }
}