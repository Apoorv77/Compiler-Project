#include <stdio.h>
#include <stdbool.h>
#include"token.h"
#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 50
#define HASH_MOD 100000007
typedef struct  hashtable_element{
    token* tokenPointer;
    bool added;
} hashtable_element;

typedef hashtable_element hashtable[HASHTABLE_SIZE];

int hash(char *str);
hashtable* init_hash_table(hashtable* table);
void insert_token(hashtable* table,token* Token);
token* find_token(hashtable* table, char* lexeme);



