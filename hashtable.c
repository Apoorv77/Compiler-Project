#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hash(char *str){
    // sum(str[i] * pow(p,i) mod m)
    int p = 101,length=strlen(str);
    long long hashValue = 0,p_pow=1;
    for (int i=0;i<length;i++){
        hashValue = (hashValue + (long long)(str[i] - 'a' + 1) * p_pow) % HASHTABLE_SIZE;
        p_pow = (p_pow * p) % HASHTABLE_SIZE;
    }
    return hashValue;
}

//Initialize hashtable
void init_hash_table(hashtable table){
    if(table == NULL){
        printf("HashTable allocation not found.\n");
        exit(1);
    }

    for(int i = 0; i < HASHTABLE_SIZE; i++){
        table[i].tokenPointer = NULL;
        table[i].added = false;
    }
}

//Insert
void insert_token(hashtable table,token* Token){
    int lexeme_hash=hash(Token->lexeme),probe=1;
    while(table[lexeme_hash].added){
        if(!strcmp(table[lexeme_hash].tokenPointer->lexeme,Token->lexeme))
        break;
        lexeme_hash =(lexeme_hash + (probe*probe)) % HASHTABLE_SIZE;
        probe++;
    }
    table[lexeme_hash].tokenPointer = Token ;
    table[lexeme_hash].added=true;

}

//Search the hash table
token* find_token(hashtable table, char* lexeme){
    int lexeme_hash = hash(lexeme);
    int probe = 1;

    while(table[lexeme_hash].added){
        //sus not sure
        if(strcmp(table[lexeme_hash].tokenPointer->lexeme, lexeme)){
            return (table[lexeme_hash].tokenPointer);
        }
        else{
            lexeme_hash = ( lexeme_hash + (probe * probe) ) % HASHTABLE_SIZE;
            probe++;
        }
    }

    return -1;
} 

