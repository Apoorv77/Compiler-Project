#ifndef twinBuffer
#include<stdio.h>
#define MAX_LEXEME_LEN 50
typedef struct token{
    int line_no;
    char* lexeme;
    int tok; // defines the type of toke

} token;
#endif