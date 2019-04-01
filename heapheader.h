#ifndef HEAPHEADER_H_INCLUDED
#define HEAPHEADER_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

 // HEAPHEADER_H_INCLUDED

struct heap{
    int blockSize;//Size of memory block current node represents
    struct heap* next;//points to the next memory block
};
struct heap* freeList=NULL;//contains unused heap blocks
struct heap* allocList=NULL;//contains allocated heap blocks
int initialSize;

#endif
