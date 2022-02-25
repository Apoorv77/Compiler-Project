#ifndef twinBuffer
#include<stdio.h>
#define BUFFER_SIZE 50
struct twinBuffer{
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    char use; // To alternate between the two buffers
};
#endif