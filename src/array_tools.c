#include "../include/array_tools.h"

uint64_t rand_gen(uint64_t min, uint64_t max)
{
    if (max == 0) return 0;
    else if (max == min)
    {
        printf("rand_gen - max == min\n"); 
        return max;
    }
    printf("rand_gen - max: %u, min: %u\n", max, min);
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    srand((time_t)ts.tv_nsec); //seeding with nanoseconds instead of seconds
    return ((rand() % (max-min)) + min);
}

void print_arr(uint64_t* array, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
        printf ("%d ", array[i]);
    printf ("\n");
}

void print_inplace(uint64_t* array, uint64_t start, uint64_t end)
{
    for (uint64_t i = start; i < end; i++)
        printf ("%d ", array[i]);
    printf ("\n");
}

void array_randpop(uint64_t* array, uint64_t size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand_gen(0, UINT64_MAX-1);
    }
}