//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:Random.c
//// Randomizes what page to replace and returns the number of faults that occurred

#include "Random.h"

int Random(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int pageFaults = 0;
    int rand;
    PAGE pageNum;
    BOOL faulted = FALSE;

    for (int j = 0; j < numMemLocations; j++)
    {
        pageNum = memoryLocations[j] / pagesize;
        if (!tableCheck(*table, pageNum)) // if page number is not in the table...
        {
            for (int i = 0; i < getTableSize(*table); i++)
            {
                // case for when frames are empty
                if (!(table->frames[i].validBit) && !(tableCheck(*table, pageNum)))
                {
                    pageFault(getFrame(table, i), pageNum);
                    *getValid(getFrame(table, i)) = TRUE;
                    faulted = TRUE;
                }
            }
            if (!faulted)
            {
				rand = getRandom(getTableSize(*table)); // pick a random frame at which to page fault
                pageFault(getFrame(table, rand), pageNum);
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