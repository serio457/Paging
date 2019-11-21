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
            return TRUE;
        }
    }
    return FALSE;
}