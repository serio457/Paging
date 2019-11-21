#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Page.h"
#include "Frame.h"
#include "pageTable.h"
#include "FIFO.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_MEM_LOCATIONS 500
#define MAX_NUM_FRAMES 500
#define FIFO_CODE 1
#define LRU_CODE 2
#define MRU_CODE 3
#define RANDOM_CODE 4

int isArgNum(char stringIn[]);
//
void storeMemoryLocations(int memoryLocations[], int numMemoryLocations, int currentMemoryLocation);

