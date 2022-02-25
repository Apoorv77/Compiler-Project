#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char *str){

    return 1;
}

void init_hash_table(hashtable table){
    if(table == NULL){
        printf("HashTable allocation not found.\n");
        exit(1);
    }

    for(int i = 0; i < HASHTABLE_SIZE; i++){
        table[i].tokenPointer = NULL;
        table[i].added = false;
        table[i].lexeme = "";
    }
}
