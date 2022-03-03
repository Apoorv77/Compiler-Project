/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include<stdio.h>
#include <stdlib.h>
#include "stack.h"

//Initialize
stack* init_stack(){
    printf("1");
    stack* st = (stack*) malloc(sizeof(stack));
    printf("2");
    st->capacity = 250;
    printf("3");
    st->arr = (line_no_and_token**) malloc(sizeof(line_no_and_token*) * st->capacity);
    printf("4");
    st->i=0;
    printf("5");
    return st;
}
void push(stack* st,line_no_and_token* str){
    printf("enter\n");
    if(st->i == st->capacity){
        st->capacity *= 2;
        line_no_and_token** temp = (line_no_and_token**)realloc(st,sizeof(line_no_and_token*) * st->capacity);
        if(!temp){printf("Error in increasing stack size!");}
        else st->arr=temp; 
    }
    st->arr[st->i] = str;
    st->i = st->i + 1;
    printf("push complete\n");
}
line_no_and_token* top(stack* st){
    if(st->i==0){
        //printf("Stack is empty!");
        return NULL;
    }
    return st->arr[st->i -1];
}

line_no_and_token* pop(stack* st){
    if(st->i == 0){
        //printf("Already empty!");
        return NULL;
    }
    st->i=st->i-1;
    return st->arr[st->i];
}

