#include "MFU.h"
#include <stdio.h>

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
                    printf("1. page fault at frame %d with location %d.\n", i, memoryLocations[j]);
                    resetFrequency(pageFrequency, MFU);
                    table->frames[i].validBit = TRUE;
                    printf("on pageNum %d\n", pageNum);
                    faulted = TRUE;
                }
            }
            MFU = findMFU(pageFrequency, table->size);
            if (!faulted)
            {
                pageFault(&table->frames[MFU], pageNum);
                printf("2. page fault at frame %d with location %d.\n", MFU, memoryLocations[j]);
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