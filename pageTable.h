//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:pageTable.h
//// Header file for pageTable.c
//// Defines a pageTable as an array of frames and an integer for size

#include "Frame.h"

#ifndef PAGETABLE_H
#define PAGETABLE_H

#define MAX_NUM_FRAMES 500

#define TRUE 1
#define FALSE 0

typedef int BOOL;

typedef struct
{
    FRAME frames[MAX_NUM_FRAMES];
    int size;
} PAGETABLE;

///Page Fault
///Performs a page fault (in a real system, this would actually move data. In our program, it just assigns an integer to a frame)
void pageFault(FRAME *frame, PAGE page);
///Table Check
///Searches a table for a page and returns TRUE (1) or FALSE (0) if the page was found
BOOL tableCheck(PAGETABLE table, PAGE page);
///Set Table Size
///Takes in a table and the size to assign
void setTableSize (PAGETABLE *table, int size);
///Table Size
///Returns the size of a Page Table
int getTableSize (PAGETABLE table);
///Get Table Frame
///Takes in a Page Table and Frame number and returns the address of that frame
FRAME *getFrame (PAGETABLE *table, int index);
#endif