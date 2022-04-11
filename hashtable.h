/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdio.h>
#include <stdbool.h>
#include"token.h"
#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 1000000

typedef struct hashtable_element{
    token* tokenPointer;
    bool added;
} hashtable_element;

hashtable_element hashtable[HASHTABLE_SIZE];

int hash(char *str);
void  init_hash_table(hashtable_element* table);
void insert_token(hashtable_element* table,token* Token);
token* find_token(hashtable_element* table, char* lexeme);



