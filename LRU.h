//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:LRU.h
//// Header file for LRU
//// Takes in a page table and returns the number of page faults to the completion of the process using Least Recently Used

#include "pageTable.h"

#ifndef LRU_H
#define LRU_H

///Main LRU function
///Takes in the pagetable, the array of memory locations, the number of memory locations, and the pagesize to return the number of pagefaults required to complete the program
int LRU(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
///Find Least Recently Used
///Searches the array that contains the number of iterations since each page was last used and returns the highest index number (corrisponds to the frams index containing that page)
int findLRU(int pageTimeInTable[], int count);
///Iterate All [frames] But [the last] Used [page]
///Increases the integer that represents the number of memory accessess that have passed since the corrisponding page was accessed, but ignores the page that was most recently called
void iterateAllButUsed(int pageTimeInTable[], int count, int frameUsed);

#endif