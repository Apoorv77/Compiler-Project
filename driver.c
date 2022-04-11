/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include<stdio.h>
#include "commentremove.h"
#include "lexer.h"
#include "parser.h"
#include <time.h>
int main(int argc,char* argv[]){
    if(argc <3){
        printf("Please enter both the input textcase and output file names\n");
        return 0;
    }
    int option=-1;
    printf("\n****Welcome to the stage-1 compiler!***\nThe 5 options available are:\n0.Exit\n1.Removal of Comments and printing comment free code\n2.Lexical Analysis\n3.Syntax Analysis\n4.Time taken by the stage-1 code (lexical+syntax)\n\n\n");

    while(option != 0){
        printf("Please enter your option:\n");
        scanf("%d",&option);
        FILE* fp = fopen(argv[1],"r");//Testcase
    FILE* op = fopen(argv[2],"w");//ParseTreeOutput.txt
    if(fp == NULL){
        printf("Error in opening the testcase %s\n",argv[1]);
        return 0;
    }
    if(op == NULL){
        printf("Error in opening the output file to write the parse tree to:%s\n",argv[2]);
        return 0;
    }
        switch (option)
        {
        case 0:
        return 0;
        case 1:
        //Removal of comments
        removeComments(fp);
        break;
         case 2:
        //Lexical Analysis
        lexical_analysis(fp);
        break;
         case 3:{
        //Parsing
            FILE *input = fopen("grammar_test_file.txt", "r");
            if (input == NULL)
            {
                fprintf(stderr, "Error Opening Grammar File\n");
                return -1;
            }
            grammar = take_input_from_grammar_file(input);
            printf("\nGRammar taken in successfully\n");
            FILE *fnf = fopen("FirstAndFollow.txt", "r");
            firstAndfollow* fnfset = populateFirstandFollow(fnf);
            printf("FNF done.\n");
            complete_init(fnfset, grammar);
            printf("INIT DONE\n");
            printf("Parse Table created, parser function ( implemented in parser.c ) returns segmentation fault\n");
        }
        break;
         case 4:{
         //Time
         clock_t start_time, end_time;
         double total_CPU_time, total_CPU_time_in_seconds;
         start_time = clock();
         // invoke your lexer and parser here
         end_time = clock();
         total_CPU_time = (double) (end_time - start_time);
         total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
         printf("Time taken for lexer and parser is %lf\n",total_CPU_time_in_seconds);
         }
        break;
        default:
        printf("Please select a valid option from 0-4\n");
            break;
        }
        fclose(fp);
    fclose(op);
    }
}