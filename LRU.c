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