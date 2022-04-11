/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
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
        hashValue = (hashValue + (long long)(str[i]) * p_pow) % HASHTABLE_SIZE;
        p_pow = (p_pow * p) % HASHTABLE_SIZE;
    }
    return hashValue;
}

//Initialize hashtable
void init_hash_table(hashtable_element* table){
    if(table == NULL){
        printf("HashTable allocation not found,Creating One.\n");
    }
    for(int i = 0; i < HASHTABLE_SIZE; i++){
        table[i].tokenPointer = NULL;
        table[i].added = false;
    //   printf("checking loop %d\n", i);
    }
    
    printf("Table Initialized\n");
}

//Insert
void insert_token(hashtable_element* table,token* Token){
    printf("Inside insert token function\n");
    int lexeme_hash=hash(Token->lexeme);
    int probe=1;
    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash].added){
        if(strcmp(table[lexeme_hash].tokenPointer->lexeme,Token->lexeme) == 0){
            break;
            printf("PreExisting Token found \n");
        }

        lexeme_hash = (lexeme_hash + (probe*probe)) % HASHTABLE_SIZE;
        probe++;
    }

    printf("Empty Space Found\n");
    table[lexeme_hash].tokenPointer = Token ;
    table[lexeme_hash].added=true;
    printf("Token Added\n");
}

//Search the hash table
token* find_token(hashtable_element* table, char* lexeme){
    printf("Inside find_token\n");

    int lexeme_hash = hash(lexeme);
    int probe = 1;

    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash].added){
        if(strcmp(table[lexeme_hash].tokenPointer->lexeme, lexeme) == 0){
            printf("Found\n");
            return (table[lexeme_hash].tokenPointer);
        }
        else{
            lexeme_hash = ( lexeme_hash + (probe * probe) ) % HASHTABLE_SIZE;
            probe++;
        }
    }

    return NULL;
} 

