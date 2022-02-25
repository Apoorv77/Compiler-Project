#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void removeComments(char* inputStream, char* outputStream){
    char* input = inputStream;
    char* output = outputStream;

    while(*input != '$'){
        if(*input == '%'){
            while(*input != '\n'){
                input++;
            }
        }
        else{
            *output = *input;
            input++;
            output++;
        }
        
    }


}

int main(){
    FILE* fp;
    char c;
    int n = 50;
    int lenRead = 0;

    char* inputStream = malloc(sizeof(char) * n);

    char* inputPointer = inputStream;


    fp = fopen("testcase.txt", "r");

    if(fp == NULL){
        printf("Eroor in reading file\n");
        return(-1);
    }

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

    *inputPointer = '$';


    char* opstream = ((char*) (malloc(sizeof(char)*n)));
    removeComments(inputStream, opstream);

    for(int i = 0; i < n; i++){
        printf("%c", opstream[i]);
    }
}