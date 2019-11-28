//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:FIFO.h
//// Headerfile for FIFO
//// Takes in a page table and returns the number of page faults to the completion of the process using First In First Out

#include "pageTable.h"

#ifndef FIFO_H
#define FIFO_H

///Main FIFO function
///Takes in the pagetable, the array of memory locations, the number of memory locations, and the pagesize to return the number of pagefaults required to complete the program
int FIFO(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);

#endif
