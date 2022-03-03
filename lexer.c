/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "lexerDef.h"
#include "lookuptable.h"


// int main()
// {
//     FILE *fp = fopen("t1.txt", "r");
//     
//     lexical_analysis(fp);
// }
void lexical_analysis(FILE *fp)
{  init_lookuptable(lookuptable);
    twinBuffer *tb = (twinBuffer *)malloc(sizeof(twinBuffer));
    tb->use = '1'; // Alternate between using buffer one and two
    int line_no = 1;
    readIntoBuffer(fp, tb);
    char c;
    FILE *op =fopen("Output_LexicalAnalysis.txt", "w");
    FILE *onlitokens =fopen("onliTokens.txt", "w");
    // printf("Reached here");
    int idx = 0;
    while (feof(fp) == 0 || tb->idx < tb->numRead)
    {
        token* t = getNextToken(fp, tb, &line_no, op, onlitokens);
        if (t != NULL && t->lexeme != NULL)
        {
            // printf("%s %d %d", t->lexeme, t->line_no, t->tok);
            // printf("Before get_token_type: %s\t", t->lexeme);
            char tempLexeme[MAX_LEX_LEN];
            strcpy(tempLexeme, t->lexeme);
            int tempTok = t->tok;
            // printf("Lexeme: %s, Tok: %d\n", tempLexeme, tempTok);
            char *tokenType = get_token_type(tempLexeme, tempTok);
            printf("Line  no. %d\t\tLexeme %s\t\tToken %s\n", t->line_no, tempLexeme, tokenType);
            if(t->tok != 27){
            fprintf(op,"Line  no. %d\t\tLexeme %s\t\tToken %s\n", t->line_no, tempLexeme, tokenType);
            fprintf(onlitokens, "%d %s\n", line_no, tokenType);
            }
        }
    }
    fclose(op);
    fclose(onlitokens);
}

token* getNextToken(FILE *fp, twinBuffer *tb, int *line_no, FILE* op, FILE* onlitokens)
{
    int state = 0, found = 0, lexeme_idx = 0, goBack = 0, errorOccured = 0, temp = tb->idx;
    char c;
    char lexeme[MAX_LEX_LEN];
    // Going over the whitespace
    while (feof(fp) == 0 || tb->idx < tb->numRead)
    {
        c = get_char_from_buffer(fp, tb);
        if (c == '\n')
            *line_no = *line_no + 1;
        if (c == ' ' || c == '\n' || c == '\t')
            continue;
        else
        {
            tb->idx = tb->idx - 1; // Retracting
            break;
        }
    }

    while (found == 0 && (tb->idx < tb->numRead || feof(fp) == 0) && errorOccured == 0)
    {
        c = get_char_from_buffer(fp, tb);
        if (c == -1)
        {   //lexeme[lexeme_idx]='\0';
            //printf("***Why %s\n",lexeme);
            c='?';
           // errorOccured = 1;
            break;
        }
        if (c == '\n')
        {
            if(state == 0){
                *line_no = *line_no + 1;
            }
            else{

            }
        }

        if (lexeme_idx < MAX_LEX_LEN - 2)
        {
            lexeme[lexeme_idx] = c;
            lexeme_idx++;
        }
        

        switch (state)
        {
        case 0:
            if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))  && !(('b' <= c && c <= 'd') || ('B' <= c && c <= 'D')))
            {
                state = 1;
            }
            else if (c >= 'b' && c <= 'd')
            {
                state = 3;
            }
            else if (c >= '0' && c <= '9')
            {
                state = 8;
            }
            else if (c == '_')
            {
                state = 18;
            }
            else if (c == '#')
            {
                state = 24;
            }
            else
            {
                switch (c)
                {
                case '.':
                    state = 22;
                    found = 1;
                    break;
                case '(':
                    state = 23;
                    found = 1;
                    break;
                case '#':
                    state = 24;
                    break;
                case '%':
                    // Have to ignore the comments and move to the next line
                    for (int i = 0; i <= lexeme_idx; i++)
                    {
                        lexeme[lexeme_idx] = '\0';
                        lexeme_idx = 0;
                    }
                    lexeme[lexeme_idx]='%';
                    lexeme_idx++;
                    while (feof(fp) == 0 || (tb->idx < tb->numRead))
                    {
                        c = get_char_from_buffer(fp, tb);
                        if (c == '\n')
                        {
                            *line_no = *line_no + 1;
                            break;
                        }
                    }
                    state = 27;
                    found = 1;
                    break;
                case '<':
                    state = 28;
                    break;
                case '[':
                    state = 34;
                    found = 1;
                    break;
                case ']':
                    state = 35;
                    found = 1;
                    break;
                case ',':
                    state = 36;
                    found = 1;
                    break;
                case ';':
                    state = 37;
                    found = 1;
                    break;
                case ':':
                    state = 38;
                    found = 1;
                    break;
                case ')':
                    state = 39;
                    found = 1;
                    break;
                case '+':
                    state = 40;
                    found = 1;
                    break;
                case '-':
                    state = 41;
                    found = 1;
                    break;
                case '*':
                    state = 42;
                    found = 1;
                    break;
                case '/':
                    state = 43;
                    found = 1;
                    break;
                case '~':
                    state = 44;
                    found = 1;
                    break;
                case '&':
                    state = 45;
                    break;
                case '@':
                    state = 48;
                    break;
                case '>':
                    state = 51;
                    break;
                case '=':
                    state = 54;
                    break;
                case '!':
                    state = 56;
                    break;
                default:
                    if(c == '\n'){
                        return NULL;
                    }
                    errorOccured = 1;
                    break;
                }
            }
            break;
        case 1:
            if (c >= 'a' && c <= 'z')
            {
                state = 1;
            }
            else
            {   
                state = 2;
                goBack = 1;
                found = 1;
            }
            break;
        case 3:
            if (c >= 'a' && c <= 'z')
            {
                state = 1;
            }
            else if ('2' <= c && c <= '7')
            {
                state = 4;
            }
            else
            {
                state = 7;
                goBack = 1;
                found = 1;
            }
            break;
        case 4:
            if (c >= 'b' && c <= 'd')
            {
                state = 4;
            }
            else if (c >= '2' && c <= '7')
            {
                state = 6;
            }
            else
            {
                state = 5;
                goBack = 1;
                found = 1;
            }
            break;

        case 6:
            if (c >= '2' && c <= '7')
            {
                state = 6;
            }
            else
            {
                state = 5;
                goBack = 1;
                found = 1;
                break;
            }
            break;

        case 8:
            if (c >= '0' && c <= '9')
            {
                state = 8;
            }
            else if (c == '.')
            {
                state = 10;
            }
            else
            {
                state = 9;
                goBack = 1;
                found = 1;
            }
            break;
        case 10:
            if (c >= '0' && c <= '9')
            {
                state = 11;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 11:
            if (c >= '0' && c <= '9')
            {
                state = 12;
            }
            else
            {
                errorOccured = 1;
                goBack = 1;
            }
            break;

        case 12:
            if (c == 'E')
            {
                state = 14;
            }
            else
            {
                state = 13;
                goBack = 1;
                found = 1;
                break;
            }
            break;

        case 14:
            if (c == '+' || c == '-')
            {
                state = 15;
            }
            else if (c >= '0' && c <= '9')
            {
                state = 16;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 15:
            if (c >= '0' && c <= '9')
            {
                state = 16;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 16:
            if (c >= '0' && c <= '9')
            {
                state = 13;
                found = 1;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 18:
            if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            {
                state = 19;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 19:
            if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            {
                state = 19;
            }
            else if (c >= '0' && c <= '9')
            {
                state = 21;
            }
            else
            {
                state = 20;
                goBack = 1;
                found = 1;
                break;
            }
            break;

        case 21:
            if (c >= '0' && c <= '9')
            {
                state = 21;
            }
            else
            {
                state = 20;
                goBack = 1;
                found = 1;
            }
            break;

        case 24:
            if (c >= 'a' && c <= 'z')
            {
                state = 25;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 25:
            if (c >= 'a' && c <= 'z')
            {
                state = 25;
            }
            else
            {
                state = 26;
                goBack = 1;
                found = 1;
            }

            break;

        case 28:
            if (c == '=')
            {
                state = 29;
                found = 1;
            }
            else if (c == '-')
            {
                state = 30;
            }
            else
            {
                state = 33;
                goBack = 1;
                found = 1;
            }
            break;

        case 30:
            if (c == '-')
            {
                state = 31;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 31:
            if (c == '-')
            {
                state = 32;
                found = 1;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 45:
            if (c == '&')
            {
                state = 46;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 46:
            if (c == '&')
            {
                state = 47;
                found = 1;
                break;
            }
            else
            {
                errorOccured = 1;
                goBack = 1;
            }
            break;

        case 48:
            if (c == '@')
            {
                state = 49;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 49:
            if (c == '@')
            {
                state = 50;
                found = 1;
            }
            else
            {
                errorOccured = 1;
            }
            break;

        case 51:
            if (c == '=')
            {
                state = 53;
                found = 1;
            }
            else
            {
                state = 52;
                goBack = 1;
                found = 1;
            }
            break;

        case 54:
            if (c == '=')
            {
                state = 55;
                found = 1;
                break;
            }
            else
            {
                errorOccured = 1;
                goBack = 1;
                break;
            }
            break;

        case 56:
            if (c == '=')
            {
                state = 57;
                found = 1;
            }
            else
            {
                errorOccured = 1;
            }
        break;

        default:
            // Error ,should never land up here
            break;
        }
    }

    if (goBack == 1)
    {
        retract(tb, &lexeme_idx, &lexeme);
    }

    // if (errorOccured)
    // {
    //     if (lexeme_idx == 0)
    //         return;
    //     printf("Error occured\n");
    //     // Keep moving until the end of this lexeme
    //     while ((feof(fp) == 0) || tb->idx < tb->numRead)
    //     {
    //         c = get_char_from_buffer(fp, tb);
    //         if (c == -1)
    //             return; // Reached the eof
    //         if (c == '\n')
    //             *line_no = *line_no + 1;
    //         if (c == '\t' || c == 'n' || c == ' ')
    //             break;
    //     }
    //     return;
    // }
    if(lexeme_idx == 0){
        return NULL;
    }
    if(state == 5 && lexeme_idx >20){
        //Variable identifiers with length > 20
        // found=0;
      //  printf("CLUTCH\n");
        errorOccured=2;
    }
    if(state == 2 && lexeme_idx > 30){
        //Function identifier with length > 30
        // found = 0;
        errorOccured = 3;
    }
    if(errorOccured == 1){
        // if(c == '\n'){
            // return NULL;
        // }
        lexeme[lexeme_idx]='\0';
        printf("Line No: %d\tError: Unknown Symbol<%s>\n", *line_no, lexeme);
        fprintf(op,"Line No: %d\tError: Unknown Symbol<%s>\n", *line_no, lexeme);
        fprintf(onlitokens, "%d %s\n", *line_no, lexeme);
        return NULL;
    }
    else if(errorOccured==2){
        printf("Error :Variable Identifier is longer than the prescribed length of 20 characters.\n");
        fprintf(op,"Error :Variable Identifier is longer than the prescribed length of 20 characters.\n");
        return NULL;
    }
    else if(errorOccured ==3){
        printf("Error :Function Identifier is longer than the prescribed length of 30 characters.\n");
        fprintf(op,"Error :Function Identifier is longer than the prescribed length of 30 characters.\n");
        return NULL;
    }
        token *t = (token *)malloc(sizeof(token));
        t->lexeme = lexeme;
        t->lexeme[lexeme_idx] = '\0';
        // printf("The lexeme is %s  Line No:%d\n",t->lexeme,*line_no);
        t->line_no = *line_no;
        if(state == 27){
            t->line_no = t->line_no -1;
        }
        t->tok = state;
        return t; 
}

void retract(twinBuffer *tb, int *lexeme_idx, char *lexeme)
{
    tb->idx = tb->idx - 1;
    *lexeme_idx = *lexeme_idx - 1;
    lexeme[*lexeme_idx] = '\0';
}


char *get_token_type(char* lexeme, int tok)
{
    char *token_type = find_token(lookuptable, lexeme);
    if(token_type != NULL){
        return token_type;
    }
switch (tok)
    {
    case 2:
        return "TK_FIELDID";
        break;
    case 5:
        return "TK_ID";
        break;
    case 9:
        return "TK_NUM";
        break;
    case 13:
        return "TK_RNUM";
        break;
    case 20:
        return "TK_FUNID";
        break;
    case 26:
        return "TK_RUID";
        break;
    }
    return token_type;
}
