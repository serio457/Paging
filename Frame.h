//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:Frame.h
//// Defines the structure for a FRAME

#include "Page.h"

#ifndef FRAME_H
#define FRAME_H

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct
{
    PAGE page;
    BOOL validBit;
} FRAME;

///Get Page from Frame
///Returns the address of a page
PAGE *getPage (FRAME *frame);
///Get Valid Bit
///Returns the address of the Valid Bit
BOOL *getValid (FRAME *frame);
#endif