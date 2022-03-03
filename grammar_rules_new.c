#include <stdio.h>
#include <stdlib.h>
#include "grammar_def.h"
#define sizeOfGrammer 53
#define MAX_SIZE_OF_SYMBOL 50
// using ^ symbol for epsilon in the grammar
//this will take input as the FILE pointer
lhs* take_input_from_grammar_file(FILE* ptr)
{
    printf("entered into the input function\n");
    lhs* grammar = ( lhs*)malloc(sizeof(lhs)*sizeOfGrammer);
    int rule_no = 0;
    char ch = 'a';
    while(ch!=EOF)
    {
        ch = fgetc(ptr);
        for(int i =0;i<10;i++)
        grammar[rule_no].rule[i] = NULL;
        grammar[rule_no].isEpsilon = 0;
        // printf("%c",ch);
        if(ch==EOF)
        break;
        // printf("%c",ch);
        // this if condition takes care of the lhs part
        if(ch=='<')
        {
            // printf("%c",ch);
            char string[50];
            ch = fgetc(ptr);
            int i = 0;
            while(ch!='>')
            {
                string[i++] = ch;
                ch = fgetc(ptr);
            }
            string[i++] = '\0';
            // printf("%c",string[0]);
            for(int j =0;string[j]!='\0';j++)
            {
                
                grammar[rule_no].nonterminal[j] = string[j];
                // printf("%c",grammar[rule_no].nonterminal[j]);
            }
            ch = fgetc(ptr);
        }
        int order = 0;
        int or_no = 0;
        while(ch!='\n'||ch!=EOF)
        {
            // printf("%c",ch);
            
           
            rhs* temp;
            if(ch=='<')
            {
                char string[MAX_SIZE_OF_SYMBOL];
                // char* symbol = (char*)malloc(sizeof(char)*MAX_SIZE_OF_SYMBOL);
                for(int i =0;i<MAX_SIZE_OF_SYMBOL;i++)
                {
                    ch = fgetc(ptr);
                    // printf("%c",ch);
                    if(ch=='>')
                    {
                        string[i] = '\0';
                        if(order==0)
                        {  
                            grammar[rule_no].rule[or_no] = (rhs*)malloc(sizeof(rhs));
                            temp = grammar[rule_no].rule[or_no];
                        }
                        int j=0;
                        for(j =0;string[j]!='\0';j++)
                        temp->token[j] = string[j]/*,printf("%c",string[j])*/;
                        temp->token[j]='\0';
                        temp->isNonTerm = 0; 
                        temp->or_no = or_no;                    
                        temp->next = (rhs*)malloc(sizeof(rhs));
                        temp = temp->next;
                        temp->next = NULL;
                        order++;
                        ch = fgetc(ptr);// to move the pointer forward so that in the next iteration, it can work properly and like go into the correct if conds
                        break;
                    }
                    else
                    string[i] = ch;
                }
            }
            else if(ch=='T')//assuming all tokens will start with a TK_
            {
                char string[MAX_SIZE_OF_SYMBOL];
                // char* symbol = (char*)malloc(sizeof(char)*MAX_SIZE_OF_SYMBOL);
                for(int i=0;i<MAX_SIZE_OF_SYMBOL;i++)
                {
                    if((ch<'A'||ch>'Z')&&ch!='_')
                    {
                        // if(ch=='\n')
                        // printf("HELLO");
                        // printf("%c",ch);
                        string[i] = '\0';
                         
                        if(order==0)
                        { 
                            grammar[rule_no].rule[or_no] = (rhs*)malloc(sizeof(rhs));
                            temp = grammar[rule_no].rule[or_no];
                        }
                        int j=0;
                        for(j =0;string[j]!='\0';j++)
                        temp->token[j] = string[j]/*,printf("%c",string[j])*/;
                        temp->token[j]='\0';
                        temp->isNonTerm = 1;  
                        temp->or_no = or_no;                      
                        temp->next = (rhs*)malloc(sizeof(rhs));
                        temp = temp->next;
                        temp->next = NULL;
                        order++;
                        // put "symbol" string in the correct place in grammar 
                        // it is surely a Terminal. So do it accordingly.
                        // it will matter if ch == '|' or '<'
                        // in the first case, a new "rules" node has to be made and the next thing put into that
                        // in the second case, simple continuation of the same linked list
                        //
                        // ch = fgetc(ptr);
                        break;
                    }
                    else
                    {
                        string[i] = ch;
                        // ch = fgetc(ptr);
                    }
                    ch = fgetc(ptr);
                }

            }
            else if(ch=='=')
            {
                while(ch!='<'&&ch!='T'&&ch!='e')// e is epsilon
                {
                    // printf("%c",ch);
                    ch = fgetc(ptr);
                }
            }
            else if(ch=='|')
            {
                temp = NULL;
                or_no++;
                order=0;
                ch = fgetc(ptr);
            }
            else if(ch==' ')
            {
                while(ch==' ')
                {
                    ch = fgetc(ptr);
                }
            }
            else if(ch=='^')
            {
                grammar[rule_no].isEpsilon = 1;
                ch = fgetc(ptr);
            }
            if(ch=='\n'||ch==EOF)
                break;
           
            // i have to handle the condition when ">|" comes together like that. I can handle it in the first case itself imo. 
        }
        rule_no++;
        printf("%d",rule_no);
    }
    return grammar;
}

void printgrammar(lhs* gram)
{
    for(int i = 0;i<sizeOfGrammer;i++)
    {
        printf("line_no : %d, lhs : %s\n",i, gram[i].nonterminal);
        int j = 0;
        while(gram[i].rule[j]!=NULL)
        {
            printf("or_no : %d\n", j);
            rhs* temp = gram[i].rule[j];
            while(temp->next!=NULL)
            {
                printf("%s -> ", temp->token);
                temp = temp->next;
            }
            printf("\nnext line\n");
            j++;
        }
        printf("\n");
    }
}

// void main()
// {
//     FILE* input = fopen("grammar_test_file_temp.txt", "r");
//     if(input==NULL){
//         fprintf(stderr, "Error Opening Grammar File\n");
//         return;
//     }
//     grammar = take_input_from_grammar_file(input);
//     printf("Input taken in successfully");
//     // if(grammar[0].rule[0]->nex==NULL)
//     // printf("HUE HUE HUE");
//     // printf("%s, %d", grammar[0].rule[1]->token,grammar[0].rule[1]->or_no);
//     printgrammar(grammar);
// }
