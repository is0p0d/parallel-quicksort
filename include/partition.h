#include "./common.h"
#include "./prefix_sums.h"
#include "./array_tools.h"

uint64_t partition(uint64_t* array, uint64_t start, uint64_t end);
uint64_t* mark(uint64_t* array, uint64_t start, uint64_t end);
uint64_t* filter(uint64_t* array, uint64_t* flags, uint64_t start, uint64_t end, uint64_t* partSize);
void flip(uint64_t* flags, uint64_t size);
void combine(uint64_t* arrA, uint64_t* arrB, uint64_t* arrC, uint64_t sizeA, uint64_t sizeB, uint64_t sizeC);
void swap(uint64_t* array, uint64_t indA, uint64_t indB);