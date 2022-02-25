#ifndef GUARD
#include<stdio.h>
#include<stdlib.h>
#include "twinBuffer.h"

int readIntoBuffer(FILE* fp,struct twinBuffer* tb){
    if(feof(fp))return 0;
    char c;
    for(int i=0;i<BUFFER_SIZE;i++){
        c=fgetc(fp);

        if(tb->use == '1')tb->buffer1[i]=c;
        else tb->buffer2[i]=c;

        if(feof(fp))return i;
    }
    return BUFFER_SIZE;    
}

// int main(){

// FILE * fp; 

// fp = fopen("1.txt", "r");

// struct twinBuffer *tb = (struct twinBuffer*) malloc (sizeof(struct twinBuffer));
// int size_buffer=BUFFER_SIZE,lexeme_begin,forward;
// tb->use='1'; //Alternate between using buffer one and two
// while(!feof(fp)){
//     int numRead=readInToBuffer(fp,tb);
//     for(int i=0;i<numRead;i++){
//         tb->use =='1'?(printf("%c",tb->buffer1[i])):(printf("%c",tb->buffer2[i]));
//     }
//     if(tb->use=='1')tb->use='2';
//     else tb->use='1';
// }
// }


#endif