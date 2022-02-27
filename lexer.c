#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "twinBuffer.h"
//#include "hashtable.h"
#include "lexer.h"
#include "lexerDef.h"
#include "lookuptable.h"
#include "token.h"
void getNextToken(FILE *fp, twinBuffer *tb, int *line_no, token *t);
void lexical_analysis(FILE *fp);
char *get_token_type(char* lexeme, int tok);
int main()
{
    FILE *fp = fopen("t1.txt", "r");
    init_lookuptable(lookuptable);
    lexical_analysis(fp);
}
void lexical_analysis(FILE *fp)
{
    twinBuffer *tb = (twinBuffer *)malloc(sizeof(twinBuffer));
    tb->use = '1'; // Alternate between using buffer one and two
    int line_no = 1;
    readIntoBuffer(fp, tb);
    char c;
    // printf("Reached here");
    int idx = 0;
    while (feof(fp) == 0 || tb->idx < tb->numRead)
    {
        token *t = (token *)malloc(sizeof(token));
        getNextToken(fp, tb, &line_no, t);
        if (t != NULL && t->lexeme != NULL)
        {
            // printf("%s %d %d", t->lexeme, t->line_no, t->tok);
            // printf("Before get_token_type: %s\t", t->lexeme);
            char tempLexeme[MAX_LEX_LEN];
            strcpy(tempLexeme, t->lexeme);
            int tempTok = t->tok;
            // printf("Lexeme: %s, Tok: %d\n", tempLexeme, tempTok);
            char *tokenType = get_token_type(tempLexeme, tempTok);
            printf("Token=> Lexeme: %s\t\t LineNo: %d\t\t Tok: %s\n", tempLexeme, t->line_no, tokenType);
        }
    }
}

void getNextToken(FILE *fp, twinBuffer *tb, int *line_no, token *t)
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

    while (found == 0 && (tb->idx < tb->numRead || feof(fp) == 0) && lexeme_idx < MAX_LEX_LEN && errorOccured == 0)
    {
        c = get_char_from_buffer(fp, tb);
        if (c == -1)
        {
            errorOccured = 1;
            break;
        }
        if (c == '\n')
        {
            *line_no = *line_no + 1;
            break;
        }
        if (lexeme_idx < MAX_LEX_LEN)
        {
            lexeme[lexeme_idx] = c;
        }
        lexeme_idx++;

        switch (state)
        {
        case 0:
            if (c >= 'a' && c <= 'z' && !('b' <= c && c <= 'd'))
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
                    while (feof(fp) == 0 || (tb->idx < tb->numRead))
                    {
                        c = get_char_from_buffer(fp, tb);
                        if (c == '\n')
                        {
                            *line_no = *line_no + 1;
                            break;
                        }
                    }
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
                // state = 2;
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
    if(state == 5 && lexeme_idx >20){
        //Variable identifiers with length > 20
        found=0;
        errorOccured=2;
    }
    if(state == 2 && lexeme_idx > 30){
        //Function identifier with length > 30
        found = 0;
        errorOccured = 3;
    }
    if(errorOccured == 1){
        printf("Line No: %d\tError: Unknown Symbol<%c>\n", *line_no, c);
        return;
    }
    else if(errorOccured==2){
        printf("Error :Variable Identifier is longer than the prescribed length of 20 characters.\n");
        return;
    }
    else if(errorOccured ==3){
        printf("Error :Function Identifier is longer than the prescribed length of 30 characters.\n");
        return;
    }

        t->lexeme = lexeme;
        t->lexeme[lexeme_idx] = '\0';
        // printf("The lexeme is %s  Line No:%d\n",t->lexeme,*line_no);
        t->line_no = *line_no;
        t->tok = state;
        return;
        
    

        
        
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

    return token_type;
}
