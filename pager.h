#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Page.h"
#include "Frame.h"
#include "pageTable.h"
#include "FIFO.h"
#include "LRU.h"
#include "MFU.h"
#include "Random.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_MEM_LOCATIONS 500
#define MAX_NUM_FRAMES 500
#define FIFO_CODE 1
#define LRU_CODE 2
#define MFU_CODE 3
#define RANDOM_CODE 4

// Tests input for digits, returns -1 if there's an error
int isArgNum(char stringIn[]);
// Saves a memory location into the memory access array
void storeMemoryLocations(int memoryLocations[], int numMemoryLocations, int currentMemoryLocation);

