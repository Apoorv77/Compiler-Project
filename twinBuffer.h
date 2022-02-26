#ifndef twinBuffer
#include<stdio.h>
#define BUFFER_SIZE 50
typedef struct twinBuffer{
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    int idx;
    int numRead;
    char use; // To alternate between the two buffers
} twinBuffer;

void readIntoBuffer(FILE* fp,twinBuffer* tb);
char get_char_from_buffer(FILE* fp,twinBuffer* tb);
#endif