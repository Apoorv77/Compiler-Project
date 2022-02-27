#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 1000000

typedef struct lookuptable_element{
    char lexeme[50];
    char token_value[50];
    bool added;
} lookuptable_element;

lookuptable_element lookuptable[HASHTABLE_SIZE];

int hash(char *str);
void  init_hash_table(lookuptable_element* table);
void insert_token(lookuptable_element* table,char* lexeme, char* tokenVal);
char* find_token(lookuptable_element* table, char* lexeme);
void add_tokens();

