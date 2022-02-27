#include <stdio.h>
#include <stdbool.h>
#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 1000000

typedef struct lookuptable_element{
    char *token_value;
    bool added;
} lookuptable_element;

lookuptable_element lookuptable[HASHTABLE_SIZE];

int hash(char *str);
void init_lookuptable(lookuptable_element* table);
void insert_token(lookuptable_element* table,char* lexeme, char* tokenVal);
char* find_token(lookuptable_element* table, char* lexeme);

