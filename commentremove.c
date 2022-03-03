/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "commentremove.h"

void removeComments(FILE* fp){
    char c;
    int n = 50;
    int lenRead = 0;
    char* inputStream = malloc(sizeof(char) * n);
    char* inputPointer = inputStream;
    do{
        c = fgetc(fp);
        *inputPointer = c;
        inputPointer++;
        lenRead++;

        if(feof(fp)){
            break;
        }

        if(lenRead == n - 5){
            n = n * 2;
            inputStream = (char *) realloc(inputStream, n);
            inputPointer = inputStream;

            for(int i = 0; i < lenRead; i++){
                inputPointer++;
            }
        }


    }
    while(1);
    char* opstream = ((char*) (malloc(sizeof(char)*n)));
    lenRead--;
    helper(inputStream, opstream,lenRead);

    for(int i = 0; i < n; i++){
        printf("%c", opstream[i]);
    }
}

void helper(char* inputStream,char* outputStream,int lenRead){
     char* input = inputStream;
    char* output = outputStream;
    int tot_read=0;
    while(tot_read<lenRead){
        if(*input == '%'){
            while(*input != '\n'){
                input++;
                tot_read++;
            }
        }
        else{
            *output = *input;
            input++;
            tot_read++;
            output++;
        }
        
    }
}