#include "../include/para_quicksort.h"

void para_quicksort(uint64_t* array, uint64_t start, uint64_t end)
{
    printf("para_quicksort - start: %u, end: %u\n", start, end);
    if (start < end && end != 0)
    {
        printf("para_quicksort - array before algorithm: \n");
        print_inplace(array, start, end);
        uint64_t pivot = rand_gen(start, end-1);
        printf("para_quicksort - pivot: %u\n", pivot);
        swap(array, start, pivot);
        uint64_t k = partition(array, start, end);
        #pragma omp parallel sections
        {
            printf("\n\npara_quicksort - section one\n");
            #pragma omp section
                para_quicksort(array, start, k);

            printf("\n\npara_quicksort - section two\n");
            #pragma omp section
                para_quicksort(array, k, end-1);
        }
        printf("para_quicksort - array after algorithm: \n");
        print_inplace(array, start, end);
    }
    printf("para_quicksort - end\n");
}