//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:pageTable.c
//// Defines a pageTable as an array of frames and an integer for size

#include "pageTable.h"

void pageFault(FRAME *frame, PAGE page)
{
    frame->page = page;
}

BOOL tableCheck(PAGETABLE table, PAGE page)
{
    for (int i = 0; i < table.size; i++)
    {
        if (table.frames[i].page == page)
        {
            return TRUE;
        }
    }
    return FALSE;
}