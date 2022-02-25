#define LEXEME_LEN_LIMIT 50
#define HASHTABLE_SIZE 100

#include"token.h"

typedef struct {
    char lexeme[LEXEME_LEN_LIMIT];
    token* tokenPointer;
    bool added;
} hashtable_element;

typedef hashtable_element hashtable[HASHTABLE_SIZE];



