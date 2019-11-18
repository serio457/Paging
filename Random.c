/*Fran, Perry, Nick 
  Fall 2019
  CS3074 Project 4
  FILE: Random.h
  Randomizes what page to replace
  Takes in a index size and returns an index number to replace
*/

#include "Random.h"

int getRandom (int indexSize) {
  srand(time(0));
  return (rand() % indexSize);
}
