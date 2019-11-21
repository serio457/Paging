//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:MFU.c
//// Takes in a page table and returns the number of page faults to the completion of the process using Most Frequently Used

#include "MFU.h"

int MFU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int pageFaults = 0;
    int MFU = 0;
    PAGE pageNum;
    int pageFrequency[table->size];
    BOOL faulted = FALSE;

    for (int i = 0; i < table->size; i++)
    {
        pageFrequency[i] = 0;
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
                    resetFrequency(pageFrequency, MFU);
                    table->frames[i].validBit = TRUE;
                    faulted = TRUE;
                }
            }
            MFU = findMFU(pageFrequency, table->size);
            if (!faulted)
            {
                pageFault(&table->frames[MFU], pageNum);
            }
            resetFrequency(pageFrequency, MFU);

            pageFaults++;
        }
        pageFrequency[MFU]++;
        faulted = FALSE;
    }
    return pageFaults;
}

int findMFU(int pageFrequency[], int count)
{
    int MFUUses = 0;
    int MFUFrame = 0;
    for (int i = 0; i < count; i++)
    {
        if (MFUUses < pageFrequency[i])
        {
            MFUUses = pageFrequency[i];
            MFUFrame = i;
        }
    }
    return MFUFrame;
}

void resetFrequency(int pageFrequency[], int MFU)
{
    pageFrequency[MFU] = 0;
}