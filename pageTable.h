#include "Frame.h"

#ifndef PAGETABLE_H
#define PAGETABLE_H

#define MAX_NUM_FRAMES 500

#define TRUE 1
#define FALSE 0

typedef int BOOL;


typedef struct {
    FRAME frames[MAX_NUM_FRAMES];
    int size;
} PAGETABLE;


void pageFault (FRAME *frame, PAGE page);

BOOL tableCheck (PAGETABLE table, PAGE page);
#endif