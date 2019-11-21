//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:Random.c
//// Randomizes what page to replace and returns the number of faults that occurred

#include "Random.h"

int Random(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int pageFaults = 0;
    PAGE pageNum;
    BOOL faulted = FALSE;

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
                    faulted = TRUE;
                }
            }
            if (!faulted)
            {
				int rand = getRandom(table->size);
                pageFault(&table->frames[rand], pageNum);
            }

            pageFaults++;
        }
        faulted = FALSE;
    }
    return pageFaults;
}

int getRandom(int indexSize)
{
	return (rand() % indexSize);
}
