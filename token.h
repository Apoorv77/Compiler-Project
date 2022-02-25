#ifndef twinBuffer
#include<stdio.h>
#define MAX_LEXEME_LEN 50
typedef struct token{
    int line_no;
    union{
        char lexeme[MAX_LEXEME_LEN];
        int num;
        double realNum;
    }value;    
    int tok; // defines the type of toke

} token;
#endif