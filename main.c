#include<stdio.h>
#include <stdlib.h>
#include "hashtable.h"
int main(){
    hashtable* ht=NULL;
    // for(int i=0;i<HASHTABLE_SIZE;i++){
    //       ht[i].tokenPointer = NULL;
    //     ht[i].added = false;
    // }
    ht=init_hash_table(ht);
     token* mytoken = (token*) malloc(sizeof(token));
    mytoken->lexeme="Apoorv";
    mytoken->line_no='1';
    mytoken->tok=7;
   insert_token(ht,mytoken);
    token* retrieved = find_token(ht,mytoken->lexeme);
     printf("%s\n",retrieved->lexeme);
    printf("%d\n",retrieved->line_no);
     printf("%d\n",retrieved->tok);
    
}