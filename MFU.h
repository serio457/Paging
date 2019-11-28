//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:MFU.h
//// Header file for MFU.c
//// Takes in a page table and returns the number of page faults to the completion of the process using Most Frequently Used

#include "pageTable.h"

#ifndef MFU_H
#define MFU_H

///Main Most Frequently Used function
///Takes in the pagetable, the array of memory locations, the number of memory locations, and the pagesize to return the number of pagefaults required to complete the program
int MFU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
///Find Most Frequently Used
///Brings in the integer array that signifies the number of uses that a particular frame has had and returns the index number of the most frequently used frame
int findMFU(int pageFrequency[], int count);
///Reset Frequency
///Resets the most frequently used's array slot (of the number of accesses) to 0 once it is faulted
void resetFrequency(int pageFrequency[], int MFU);

#endif