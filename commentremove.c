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
    char* opstream = ((char*) (malloc(sizeof(char)*100)));
    removeComments("ABCDE\nsldjkfgn%pqrst dkfjgndkjf\n $", opstream);

    for(int i = 0; i < 100; i++){
        printf("%c", opstream[i]);
    }
}