#include "pagingAlgorithms.h"
#include <stdio.h>


void FIFO(PAGETABLE* table, PAGE pageNum, int* firstIn)
{
    //PAGETABLE tempTable = *table;
    printf("\nstarting FIFO\n");
    for (int i = 0; i < table->size; i++)
    {
        if (!(table->frames[i].validBit) && !(tableCheck(*table, pageNum)))
        {
            pageFault (&table->frames[i], pageNum);
            table->frames[i].validBit = TRUE;
        }
    }
    pageFault (&table->frames[*firstIn], pageNum);
    *firstIn = *firstIn + 1;
    if (*firstIn == table->size)
    {
        *firstIn = 0;
    }
}