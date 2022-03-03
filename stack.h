/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include<stdio.h>

typedef struct Line_no_and_token{
    char arr[60];
    char line_no[4];
}line_no_and_token;

typedef struct stack{
    line_no_and_token** arr;
    int i;
    int capacity;

} stack;

stack* init_stack();
void push(stack* st,line_no_and_token* str);
line_no_and_token* pop(stack* st);
line_no_and_token* top(stack* st);