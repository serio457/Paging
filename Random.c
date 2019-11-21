/*Fran, Perry, Nick 
  Fall 2019
  CS3074 Project 4
  FILE: Random.h
  Randomizes what page to replace
  Takes in a index size and returns an index number to replace
*/

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
                    printf("1. page fault at frame %d with location %d.\n", i, memoryLocations[j]);
                    table->frames[i].validBit = TRUE;
                    printf("on pageNum %d\n", pageNum);
                    faulted = TRUE;
                }
            }
            if (!faulted)
            {
				int rand = getRandom(table->size);
                pageFault(&table->frames[rand], pageNum);
                printf("2. page fault at frame %d with location %d, page %d.\n", rand, memoryLocations[j], pageNum);
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
