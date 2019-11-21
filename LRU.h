#include "pageTable.h"

#ifndef LRU_H
#define LRU_H


int LRU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
int findLRU(int pageTimeInTable[], int count);
void iterateAllButUsed(int pageFrequencies[], int count, int frameUsed);

#endif