#include<stdio.h>
#include <stdlib.h>
#include "hashtable.h"
int main(){
    // for(int i=0;i<HASHTABLE_SIZE;i++){
    //       ht[i].tokenPointer = NULL;
    //     ht[i].added = false;
    // }
    init_hash_table(hashtable);

    printf("Returned for initialization to main\n");

    printf("Creating a sample token\n");
    token* mytoken = (token*) malloc(sizeof(token));
    mytoken->lexeme="Apoorv";
    mytoken->line_no= 1;
    mytoken->tok=7;

    printf("Token=> lexeme: %s \t lineno: %d \t tokenEnum: %d \n", mytoken->lexeme, mytoken->line_no, mytoken->tok);

   insert_token(hashtable,mytoken);
   printf("Returned to main post insertion\n");
   
    token* retrieved = find_token(hashtable,mytoken->lexeme);
     printf("%s\n",retrieved->lexeme);
    printf("%d\n",retrieved->line_no);
     printf("%d\n",retrieved->tok);
    
}