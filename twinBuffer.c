#ifndef GUARD
#include<stdio.h>
#include<stdlib.h>
#include "twinBuffer.h"

void readIntoBuffer(FILE* fp,twinBuffer* tb){
    tb->idx=0;
    tb->numRead=0;
    if(feof(fp))return;
    char c;
    for(int i=0;i<BUFFER_SIZE;i++){
        c=fgetc(fp);

        if(tb->use == '1')tb->buffer1[i]=c;
        else tb->buffer2[i]=c;

        if(feof(fp)){tb->numRead=i+1;return;}
    }
    tb->numRead=BUFFER_SIZE;    
}
char get_char_from_buffer(FILE* fp,twinBuffer* tb){
    if(tb->idx == tb->numRead){
        if(tb->use=='1'){
            tb->use='2';
        }
        else tb->use='1';
        readIntoBuffer(fp,tb);
    }
    char c;
    if(tb->use=='1')c=tb->buffer1[tb->idx];
    else c=tb->buffer2[tb->idx];
    tb->idx = tb->idx + 1;
    return c;
}

// int main(){

// FILE * fp; 
// int line=1;
// fp = fopen("t1.txt", "r");
//  twinBuffer *tb = (twinBuffer*) malloc (sizeof(twinBuffer));
// int size_buffer=BUFFER_SIZE,lexeme_begin,forward;
// tb->use='1'; //Alternate between using buffer one and two
// while(!feof(fp)){
//     readIntoBuffer(fp,tb);
//     int numRead= tb->numRead;
//     for(int i=0;i<numRead;i++){
//         if(tb->use =='1'){
//             if(tb->buffer1[i]=='\n')line++;
//             printf("%c",tb->buffer1[i]);
//         }
//         else { 
//             if(tb->buffer1[i]=='\n')line++;
//             printf("%c",tb->buffer2[i]); 
//         }
//     }
//     if(tb->use=='1')tb->use='2';
//     else tb->use='1';
// }
// printf("The total number of lines read is : %d\n",line);
// }


#endif