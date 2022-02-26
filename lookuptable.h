#include <stdio.h>
#include <stdbool.h>
#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 1000000

typedef struct lookuptable_element{
    char token_value[50];
    bool added;
} lookuptable_element;

lookup_table lookuptable[HASHTABLE_SIZE];

int hash(char *str);
void  init_hash_table(lookuptable_element* table);
void insert_token(lookuptable_element* table,char *lexeme);
token* find_token(lookuptable_element* table, char* lexeme);

