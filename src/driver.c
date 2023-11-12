/**********************************************************
* Jim M                                           11.2.23 *
* para_quicksort.c                                        *
* A parallel implementation of the quicksort algorithm    *
* with included timing functions to compare the effect of *
* parallelism across multiple sizes of datasets and itera-*
* tions.                                                  *
* Usage:                                                  *
* quicksort x y z                                         *
* Where x is the number of randomly generated numbers the *
* program will sort, y is the number of rounds times it'll*
* rerandomize and sort the numbers for timing purposes,   *
* and z is the number of processors that the program will *
* be allowed to use.                                      *
**********************************************************/

#include "../include/common.h"
#include "../include/array_tools.h"
#include "../include/para_quicksort.h"
#include "../include/partition.h"

int main(uint64_t argc, char* argv[])
{
    if (argc != 4)
    {
        printf("ERROR: Unexpect argument count, this program accepts three arguments past the program name.\n");
        printf("USAGE: quicksort x y z\nWhere:\tx is the number of randomly generated numbers the program will sort\n");
        printf("\ty is the number of rounds the program will re-randomize and re-sort the array of size x, for timing purposes\n");
        printf("\tz is the number of processors used to parallelize the sorting of x elements y times\n");
        return 1;
    }
    printf("quicksort.c - jpm 2023\n");
    
    // Values set from the command line
    uint64_t setSize = atoi(argv[1]); //Size of the randomized array
    uint64_t numRnds = atoi(argv[2]); //number of times array will be re-randomized and sorted
    uint64_t  numProc = atoi(argv[3]); //number of processors program will be allowed to utilize.
    // A dat file to store our output for visualization
    char* outputName = "output1.dat";
    FILE* output = NULL;
    // clock and values for timing
    clock_t timer;
    double parTime = 0.0;
    double serTime = 0.0;
    uint64_t maxProc = (uint64_t)omp_get_max_threads();
    uint64_t numFlagged = 0; //for creating the B array - may end up vestigial
    //arrays and such
    uint64_t* sortArr = NULL; //sorted and unsorted values, depending on execution point
    float* stArr = NULL;

    //start actual code
    printf("system available processors: %d\n", maxProc);
    if (numProc > maxProc)
    {
      printf("*ERROR: %d processors exceeds the system max of %d\n", numProc, maxProc);
      return -1;  
    }
  

    printf("Processors: %d, Data Set Size: %d, Rounds: %d\n", numProc, setSize, numRnds);

    avgsArr = (float*)calloc(numRnds, sizeof(float));
    
    for (int procIndex = 0; procIndex < numProc; procIndex++)
    {
        omp_set_num_threads(numProc); //setting the number of "processors" our program will attempt to use
    }
    
    
    
    
    
    // omp_set_num_threads(1);
    // uint64_t testArr[5] = {5,6,4,7,3}; // should produce 10101

    // printf("main - calling para_quicksort...\n");
    // para_quicksort(testArr, 0, 5);

    // printf("main - sorted array:\n");
    // print_arr(testArr, 5);
    
    return 0;
}