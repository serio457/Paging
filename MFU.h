#include "pageTable.h"

#ifndef MFU_H
#define MFU_H


int MFU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
int findMFU(int pageTimeInTable[], int count);
void resetFrequency(int pageFrequency[], int MFU);

#endif