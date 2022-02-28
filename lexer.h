//function prototype declarations of functions in lexer.c
#include<stdio.h>
#include "token.h"
void retract(twinBuffer* tb,int *lexeme_idx,char* lexeme);
void generate_lookupTable();
token* getNextToken(FILE *fp, twinBuffer *tb, int *line_no, FILE* op);
void lexical_analysis(FILE *fp);
char *get_token_type(char* lexeme, int tok);
