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
    float parTime = 0.0;
    float serTime = 0.0;
    uint64_t maxProc = (uint64_t)omp_get_max_threads();
    uint64_t numFlagged = 0; //for creating the B array - may end up vestigial
    //arrays and such
    float* serAvgsArr = NULL;
    float* parAvgsArr = NULL;
    uint64_t* sortArr1 = NULL; //sorted and unsorted values, depending on execution point
    uint64_t* sortArr2 = NULL; //copy
    float* stArr = NULL;

    //start actual code
    printf("system available processors: %d\n", maxProc);
    if (numProc > maxProc)
    {
      printf("*ERROR: %d processors exceeds the system max of %d\n", numProc, maxProc);
      return -1;  
    }
  

    printf("Processors: %d, Data Set Size: %d, Rounds: %d\n", numProc, setSize, numRnds);
    
    for (int procIndex = 1; procIndex <= numProc; procIndex++)
    {
        serAvgsArr = (float *)calloc(numRnds, sizeof(float));
        parAvgsArr = (float *)calloc(numRnds, sizeof(float));
        for (int step = 0; step < numRnds; step++) //sorting an new array step number of times for data integrity, higher sample size.
        {
            //initialize array
            sortArr1 = (uint64_t *)malloc(setSize*sizeof(uint64_t)); //serial sort
            sortArr2 = (uint64_t *)malloc(setSize*sizeof(uint64_t)); //parallel sort
            uint64_t tempRand = 0;
            for(int arrInd = 0; arrInd < setSize; arrInd++)
            {
                tempRand = rand_gen(0, 256);
                sortArr1[arrInd] = tempRand;
                sortArr2[arrInd] = tempRand;
            }
            omp_set_num_threads(1); //effectively making a serial version.
            printf("main - calling para_quicksort...\n");
            timer = clock();
            para_quicksort(sortArr1, 0, setSize);
            timer = clock() - timer;
            serAvgsArr[step] = ((float)timer)/CLOCKS_PER_SEC;

            omp_set_num_threads(procIndex); //setting the number of "processors" our program will attempt to use
            timer = clock();
            para_quicksort(sortArr1, 0, setSize);
            timer = clock() - timer;
            parAvgsArr[step] = ((float)timer)/CLOCKS_PER_SEC;
            free(sortArr2);
            free(sortArr1);
        }
        //averaging those times into one value
        parTime = array_avg(parAvgsArr, numRnds);
        serTime = array_avg(serAvgsArr, numRnds);

        printf("%i processors: p%f, s%f\n", procIndex, parTime, serTime);

        free(parAvgsArr);
        free(serAvgsArr);
    }
    
    
    
    
    
    // omp_set_num_threads(1);
    // uint64_t testArr[5] = {5,6,4,7,3}; // should produce 10101

    // printf("main - calling para_quicksort...\n");
    // para_quicksort(testArr, 0, 5);

    // printf("main - sorted array:\n");
    // print_arr(testArr, 5);
    
    return 0;
}