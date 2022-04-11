/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
//function prototype declarations of functions in lexer.c
#include<stdio.h>
#include "token.h"
#include "twinBuffer.h"
void retract(twinBuffer* tb,int *lexeme_idx,char* lexeme);
void generate_lookupTable();

token* getNextToken(FILE *fp, twinBuffer *tb, int *line_no, FILE* op, FILE* onlitokens);
void lexical_analysis(FILE *fp);
char *get_token_type(char* lexeme, int tok);
