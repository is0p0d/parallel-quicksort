#include "./common.h"
#include "./array_tools.h"

uint64_t* prefix_sums(uint64_t* array, uint64_t size);
uint64_t* ps_arrprep(uint64_t* array, uint64_t size, uint64_t newSize);
void ps_shiftleft(uint64_t* array, uint64_t size);
void ps_addone(uint64_t* array, uint64_t size);