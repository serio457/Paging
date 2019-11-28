//// Fran, Perry, Nick
//// Fall 2019
//// CS3074 Project 4
//// FILE:Frame.c
//// A frame is made in the .h file

#include "Frame.h"

PAGE *getPage (FRAME *frame)
{
    return &frame->page;
}

BOOL *getValid (FRAME *frame)
{
    return &frame->validBit;
}