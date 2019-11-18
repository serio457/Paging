#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_MEM_LOCATIONS 500

int isArgNum(char stringIn[]);
//
void storeMemoryLocations(int memoryLocations[], int numMemoryLocations, int currentMemoryLocation);
