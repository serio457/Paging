//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:FIFO.c
//// Takes in a page table and returns the number of page faults to the completion of the process using First In First Out

#include "FIFO.h"
#include <stdio.h>

int FIFO(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize)
{
    int firstIn = 0, pageFaults = 0;
    PAGE pageNum;
    for (int j = 0; j < numMemLocations; j++)
    {
        pageNum = memoryLocations[j]/pagesize;
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
            pageFault(&table->frames[firstIn], pageNum);
            pageFaults++;
            firstIn++;
            if (firstIn == table->size)
            {
                firstIn = 0;
            }
        }
    }
    return pageFaults;
}