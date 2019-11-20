#include "pageTable.h"
#include <stdio.h>

void pageFault (FRAME *frame, PAGE page)
{
    frame->page = page;
}

BOOL tableCheck (PAGETABLE table, PAGE page)
{
    for (int i=0; i<table.size; i++)
    {
        if (table.frames[i].page == page)
        {
            //printf ("returning true on frame %d with page %d\n", i, page);
            return TRUE;
        }
            //printf ("false on frame %d (page %d) with page %d\n", i, table.frames[i].page, page);
    }
    //printf ("returning false with page %d\n", page);
    return FALSE;
}