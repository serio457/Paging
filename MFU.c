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
    int pageFrequency[getTableSize(*table)]; // array that keeps track of how recently a page has been used
    BOOL faulted = FALSE;

    // initialize all page frequencies to 0
    for (int i = 0; i < getTableSize(*table); i++)
    {
        pageFrequency[i] = 0;
    }

    for (int j = 0; j < numMemLocations; j++)
    {
        pageNum = memoryLocations[j] / pagesize; 
        if (!tableCheck(*table, pageNum)) // if page number is not in the table... 
        {
            for (int i = 0; i < getTableSize(*table); i++)
            {
                // case for when frames are empty
                if (!(*getValid(getFrame(table, i))) && !(tableCheck(*table, pageNum)))
                {
                    pageFault(getFrame(table, i), pageNum);
                    resetFrequency(pageFrequency, MFU);
                    *getValid(getFrame(table, i)) = TRUE;
                    faulted = TRUE;
                }
            }
            MFU = findMFU(pageFrequency, getTableSize(*table)); // find page that was most frequently used
            if (!faulted)
            {
                pageFault(getFrame(table, MFU), pageNum); 
            }
            resetFrequency(pageFrequency, MFU); // reset that frame's frequency to 0

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