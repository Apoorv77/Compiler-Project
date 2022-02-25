#include<stdio.h>

int main(){
    int option=-1;
    printf("\nWelcome to the stage-1 compiler!\nThe 5 options available are:\n0.Exit\n1.Removal of Comments and printing comment free code\n2.Lexical Analysis\n3.Syntax Analysis\n4.Time taken by the stage-1 code (lexical+syntax)\n\n");

    while(option != 0){
        printf("Please enter your option:\n");
        scanf("%d",&option);
        switch (option)
        {
        case 0:
        return 0;
        case 1:
        //Removal of comments
        break;
         case 2:
        //Lexical Analysis
        break;
         case 3:
        //Parsing
        break;
         case 4:
         //Time
        break;
        default:
        printf("Please select a valid option from 0-4\n");
            break;
        }
    }
}