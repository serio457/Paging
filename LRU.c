//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:LRU.c
//// Takes in a page table and returns the number of page faults to the completion of the process using Least Recently Used

#include "LRU.h"

int LRU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int pageFaults = 0;
    int LRU = 0;
    PAGE pageNum;
    int pageTimeInTable[getTableSize(*table)]; // array that keeps track of the "time" that a page has been in a frame

    // initialize all times to 0
    for (int i = 0; i < getTableSize(*table); i++)
    {
        pageTimeInTable[i] = 0;
    }

    for (int j = 0; j < numMemLocations; j++)
    {
        pageNum = memoryLocations[j] / pagesize;
        if (!tableCheck(*table, pageNum)) // if a page is not in the table...
        {
            for (int i = 0; i < getTableSize(*table); i++)
            {
                // case for when frames are empty
                if (!(*getValid(getFrame(table, i))) && !(tableCheck(*table, pageNum)))
                {
                    pageFault(getFrame(table, i), pageNum);
                    *getValid(getFrame(table, i)) = TRUE;
                }
            }
            LRU = findLRU(pageTimeInTable, getTableSize(*table)); // find the page that was least recently used
            pageFault(getFrame(table, LRU), pageNum);

            pageFaults++;
        }
        iterateAllButUsed(pageTimeInTable, getTableSize(*table), LRU); // increment the "time" for those page that were not used
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

void iterateAllButUsed(int pageTimeInTable[], int count, int frameUsed)
{
    for (int i = 0; i < count; i++)
    {
        if (i != frameUsed)
        {
            pageTimeInTable[i]++;
        }
        else
        {
            pageTimeInTable[i] = 0;
        }
    }
}