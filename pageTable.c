//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:pageTable.c
//// Defines a pageTable as an array of frames and an integer for size

#include "pageTable.h"

void pageFault(FRAME *frame, PAGE page)
{
    *getPage(frame) = page;
}

BOOL tableCheck(PAGETABLE table, PAGE page)
{
    for (int i = 0; i < getTableSize(table); i++)
    {
        if (*getPage(getFrame(&table, i)) == page)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void setTableSize (PAGETABLE *table, int size)
{
    table->size = size;
}

int getTableSize (PAGETABLE table)
{
    return table.size;
}

FRAME *getFrame (PAGETABLE *table, int index)
{
    return &table->frames[index];
}