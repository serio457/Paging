/*Fran, Perry, Nick 
  Fall 2019
  CS3074 Project 4
  FILE: Random.h
  Randomizes what page to replace
  Takes in a index size and returns an index number to replace
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pageTable.h"

#ifndef RANDOM_H
#define RANDOM_H

int Random(PAGETABLE *table, PAGE memoryLocations[], int numMemLocations, int pagesize);
int getRandom(int indexSize);

#endif
