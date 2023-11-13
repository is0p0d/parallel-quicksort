#include "../include/partition.h"

uint64_t partition(uint64_t* array, uint64_t start, uint64_t end)
{
    printf("partition - start: %u, end: %u\n", start, end);
    uint64_t sizeB = 0, sizeC = 0;
    uint64_t* flags = mark(array, start, end);
    printf("partition - starting B...\n");
    uint64_t* partB = filter(array, flags, start, end, &sizeB);
    printf("partition - sizeB: %u\n", sizeB);
    flip(flags, end-start);
    printf("partition - starting C...\n");
    uint64_t* partC = filter(array, flags, start, end, &sizeC);
    printf("partition - sizeC: %u\n", sizeC);
    combine(array, partB, partC, (end-start), sizeB, sizeC);
    swap(array, start, sizeB-1);
    
    printf("partition - array after partition:\n");
    print_arr(array, (end-start));


    free(partC);
    free(partB);
    free(flags);

    return sizeB;
}
uint64_t* mark(uint64_t* array, uint64_t start, uint64_t end)
{
    printf("mark - start: %u. end: %u\n", start, end);
    printf("mark - passed array: ");
    print_inplace(array, start, end);

    uint64_t* flagArr = (uint64_t*)calloc((end-start), sizeof(uint64_t));
    #pragma omp parallel for 
    for (uint64_t i = 0; i < (end-start); i++)
    {
        printf(">i: %u, Arr index: %u\n", i, i+start);
        if (array[start] >= array[i+start])
        {
            //printf("%u - i: %u, array[i]: %u, cond: 1, flagIndex: %u\n", omp_get_thread_num(), i, array[i], (i%end));
            flagArr[i] = 1;
        }
        else
        {
            //printf("%u - i: %u, array[i]: %u, cond: 0, flagIndex: %u\n", omp_get_thread_num(), i, array[i], (i%end));
            flagArr[i] = 0;
        }
    }
    printf("mark - returning this: ");
    print_arr(flagArr, (end-start));

    return flagArr;
}

uint64_t* filter(uint64_t* array, uint64_t* flags, uint64_t start, uint64_t end, uint64_t* partSize)
{
    printf("filter - start: %u. end: %u\n", start, end);
    uint64_t size = (end-start);
    printf("filter - passed array: ");
    print_inplace(array, start, end);
    printf("filter - passed flags: ");
    print_arr(flags, size);
    
    uint64_t* flagsP = prefix_sums(flags, size);
    //*partSize = flagsP[size]-1;
    //changing this in github, instead of using a conditional to help deal with size 1 issues
    //just gonna count in the for loop :)
    uint64_t partCount = 0;
    printf("filter - partSize: %u\n", *partSize);
    uint64_t* partArr = (uint64_t*)calloc(*partSize, sizeof(uint64_t));
    if (flagsP != NULL && flagsP != NULL)
    {
        #pragma omp parallel for
        for (uint64_t i = 0; i < size; i++)
        {
            if (flags[i] == 1)
            {
                printf("filter - loop: %u, flags[%u]: %u, flagsP[%u]-1: %u, array[%u]: %u\n",i,i,flags[i],i,flagsP[i]-1,i,array[i]);
                partArr[flagsP[i]-1] = array[i];
                partCount++;
            }
        }
        *partSize = partCount;
        printf("filter - returning this: \n");
        print_arr(partArr, *partSize);
        free(flagsP);
    }

    return partArr;
}

void flip(uint64_t* flags, uint64_t size)
{
    printf("flip - size: %u\n", size);
    printf("fip - passed flags: ");
    print_arr(flags, size);

    #pragma omp parallel for
    for (uint64_t i = 0; i < size; i++)
    {
        flags[i] = (flags[i] == 0) ? 1 : 0;
    }

    printf("fip - flipped flags: ");
    print_arr(flags, size);

}

void combine(uint64_t* arrA, uint64_t* arrB, uint64_t* arrC, uint64_t sizeA, uint64_t sizeB, uint64_t sizeC)
{
    printf("combine - sizeA: %u, sizeB: %u, sizeC: %u\n", sizeA, sizeB, sizeC);
    printf("combine - passed array A:");
    print_arr(arrA, sizeA);
    printf("combine - passed array B:");
    print_arr(arrB, sizeB);
    printf("combine - passed array C:");
    print_arr(arrC, sizeC);

    if (sizeB != 0)
    {
        #pragma omp parallel for
        for(int i = 0; i < sizeB; i++)
            arrA[i] = arrB[i];
    }
    if (sizeC != 0)
    {
        #pragma omp parallel for
        for(int i = 0; i < sizeC; i++)
            arrA[sizeB+i] = arrC[i];
    }
    printf("combine - completed array: \n");
    print_arr(arrA, sizeA);
}

void swap(uint64_t* array, uint64_t indA, uint64_t indB)
{
    indA = (indA == UINT64_MAX ) ? 0 : indA;
    indB = (indB == UINT64_MAX) ? 0 : indB;
    printf("swap - indA: %d, indB %d\n", indA, indB);
    printf("swap - swapping vals: %d, %d\n", array[indA], array[indB]);
    uint64_t temp = array[indA];
    array[indA] = array[indB];
    array[indB] = temp;
    printf("swap - swapped vals: %d, %d\n", array[indA], array[indB]);
}