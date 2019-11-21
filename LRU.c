#include "LRU.h"
#include <stdio.h>

int LRU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int pageFaults = 0;
    int LRU = 0;
    PAGE pageNum;
    int pageTimeInTable[table->size];

    for (int i = 0; i < table->size; i++)
    {
        pageTimeInTable[i] = 0;
    }

    for (int j = 0; j < numMemLocations; j++)
    {
        pageNum = memoryLocations[j] / pagesize;
        if (!tableCheck(*table, pageNum))
        {
            for (int i = 0; i < table->size; i++)
            {
                if (!(table->frames[i].validBit) && !(tableCheck(*table, pageNum)))
                {
                    pageFault(&table->frames[i], pageNum);
                    table->frames[i].validBit = TRUE;
                    printf("on MemLoc %d\n", pageNum);
                }
            }
            LRU = findLRU(pageTimeInTable, table->size);
            pageFault(&table->frames[LRU], pageNum);

            pageFaults++;
        }
        iterateAllButUsed(pageTimeInTable, table->size, LRU);
    }
    return pageFaults;
}

int findLRU(int pageTimeInTable[], int count)
{
    int LRUUses = 0;
    int LRUFrame = 0;
    for (int i = 0; i < count; i++)
    {
        if (LRUUses < pageTimeInTable[i])
        {
            LRUUses = pageTimeInTable[i];
            LRUFrame = i;
        }
    }
    return LRUFrame;
}

void iterateAllButUsed(int pageFrequencies[], int count, int frameUsed)
{
    for (int i = 0; i < count; i++)
    {
        if (i != frameUsed)
        {
            pageFrequencies[i]++;
        }
        else
        {
            pageFrequencies[i] = 0;
        }
    }
}