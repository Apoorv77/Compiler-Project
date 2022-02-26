#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hash(char *str){
    // sum(str[i] * pow(p,i) mod m)
    int p = 101,length=strlen(str);
    // printf("%d\n",length);
    long long hashValue = 0,p_pow=1;
    for (int i=0;i<length;i++){
        hashValue = (hashValue + (long long)(str[i] - 'a' + 1) * p_pow) % HASHTABLE_SIZE;
        p_pow = (p_pow * p) % HASHTABLE_SIZE;
    }
    return hashValue;
}

//Initialize hashtable
hashtable* init_hash_table(hashtable* table){
    if(table == NULL){
        printf("HashTable allocation not found,Creating One.\n");
        table = malloc(sizeof(hashtable));
        printf("Table Alloc in init was successfull\n");
    }
    for(int i = 0; i < HASHTABLE_SIZE; i++){
       if(table[i]==NULL){printf("%d\n",i);}
       else{
        table[i]->tokenPointer= NULL;
        table[i]->added = false;
       }
    //   printf("checking loop %d\n", i);
    }
    
    printf("Table Initialized\n");
    return table;
}

//Insert
void insert_token(hashtable* table,token* Token){
    printf("Inside insert token function\n");
    int lexeme_hash=hash(Token->lexeme);
    int probe=1;
    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash]->added){
        if(strcmp(table[lexeme_hash]->tokenPointer->lexeme,Token->lexeme) == 0){
            break;
            printf("PreExisting Token found \n");
        }

        lexeme_hash = (lexeme_hash + (probe*probe)) % HASHTABLE_SIZE;
        probe++;
    }

    printf("Empty Space Found\n");
    table[lexeme_hash]->tokenPointer = Token ;
    table[lexeme_hash]->added=true;
    printf("Token Added\n");
}

//Search the hash table
token* find_token(hashtable* table, char* lexeme){
    printf("Inside find_token\n");

    int lexeme_hash = hash(lexeme);
    int probe = 1;

    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash]->added){
        if(strcmp(table[lexeme_hash]->tokenPointer->lexeme, lexeme) == 0){
            printf("Found\n");
            return (table[lexeme_hash]->tokenPointer);
        }
        else{
            lexeme_hash = ( lexeme_hash + (probe * probe) ) % HASHTABLE_SIZE;
            probe++;
        }
    }

    return NULL;
} 

