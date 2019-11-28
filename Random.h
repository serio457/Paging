//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:Random.h
//// Headerfile for Random.c
//// Randomizes what page to replace and returns the number of faults that occurred

#include <stdlib.h>
#include <time.h>
#include "pageTable.h"

#ifndef RANDOM_H
#define RANDOM_H

///Main Random Function
///Takes in the pagetable, the array of memory locations, the number of memory locations, and the pagesize to return the number of pagefaults required to complete the program
int Random(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
///Get Random [Number] Function
///Takes in an index count and returns a random number from 0 to that number
int getRandom(int indexSize);

#endif