#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "twinBuffer.h"
#include "hashtable.h"
#include "lexer.h"
#include "lexerDef.h"
token* getNextToken(FILE* fp,twinBuffer* tb,int* line_no);
void lexical_analysis(FILE* fp);

int main(){
    FILE* fp = fopen("test.txt", "r");
    lexical_analysis(fp);
}

void lexical_analysis(FILE* fp){
    twinBuffer *tb = (twinBuffer*) malloc (sizeof(twinBuffer));
    tb->use = 1;
    int line_no = 1;
    readIntoBuffer(fp,tb);
    char c;
    tb->idx = 0;

    while(feof(fp) == 0 || tb->idx < tb->numRead){
        token* t = getNextToken(fp, tb, &line_no);
        if(t != NULL){
            printf("Token=> Lexeme: %s\t\t\tLineNo: %d\t\t\tTok: %d\n", t->lexeme, t->line_no, t->tok);
        }
        
    }
}


token* getNextToken(FILE* fp, twinBuffer* tb, int* line_no){
    int state = 0, found = 0, lexeme_idx = 0, goBack = 0, errorOccured = 0, commentFound = 0;
    char c;
    char lexeme[MAX_LEX_LEN];


    //going to the token

    while(feof(fp) == 0 || tb->idx < tb->numRead){
        c = get_char_from_buffer(fp, tb);
        if(c == '\n'){
            *line_no = *line_no + 1;
            continue;
        }
        else if(c == ' ' || c == '\t'){
            continue;
        }
        else{
            tb->idx = tb->idx-1;
            break;
        }
    }

    //reading the lexeme

    while(found == 0 && (feof(fp) == 0 || tb->idx < tb-> numRead) && lexeme_idx < MAX_LEX_LEN && errorOccured == 0){
        c = get_char_from_buffer(fp, tb);
        

        if(c == -1){
            errorOccured = 1;
            break;
        }

        if(c == '\n'){
            *line_no = *line_no + 1;
            break;
        }

        lexeme[lexeme_idx] = c;

        lexeme_idx++;

        switch (state)
    {
    case 0:
        if(c >= 'a' && c <= 'z' && !('b'<= c && c <='d')){
            state = 1;
        }
        else if(c >= 'b' && c <='d')
        {
            state = 3;
        }
        else if(c >= '0' && c <= '9')
        {
            state = 8;
        }
        else{
            switch (c)
            {
            case '_':
                state = 18;
                break;
            case '.':
                state=22;
                found = 1;
                break;
            case '(':
                state=23;
                found = 1;
                break;
            case '#':
                state=24;
                break;
            case '%':
                state=27;
                // found=1;
                break;
            case '<':
                state=28;
                break;
            case '[':
                state=34;
                found=1;
                break;
            case ']':
                state=35;
                found=1;
                break;
            case ',':
                state=36;
                found=1;
                break;
            case ';':
                state=37;
                found=1;
                break;
            case ':':
                state=38;
                found=1;
                break;
            case ')':
                state=39;
                found=1;
                break;
            case '+':
                state = 40;
                found=1;
                break;
            case '-':
                state = 41;
                found=1;
                break;
            case '*':
                state = 42;
                found=1;
                break;
            case '/':
                state = 43;
                found=1;
                break;
            case '~':
                state = 44;
                found=1;
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
       if(c >='a' && c <='z'){
           state=1;
       }
       else{
            state = 2;
            goBack=1;
            found=1;
            break;
       }
       break;
    case 3:
        if(c >= 'a' && c <= 'z'){
            state=1;
        }
        else if('2' <=c && c<='7'){
            state=4;
        }
        else{
            state = 7;
          goBack=1;
            found=1;
            break;
        }
        break;
    case 4:
        if(c >= 'b' && c <= 'd'){
            state = 4;
        }
        else if(c >= '2' && c <= '7'){
            state = 6;
        }
        else{
            state = 5;
          goBack=1;
           found=1;
        }
        break;

    case 6:
        if(c >= '2' && c <= '7'){
            state = 6;
        }
        else{
            state = 5;
           goBack=1;
            found=1;
            break;
        }
        break;

    case 8:
        if(c >= '0' && c <= '9'){
            state = 8;
        }
        else if(c == '.'){
            state = 10;
        }
        else{
            state = 9;
           goBack=1;
            found=1;
        }
       break;
    case 10:
        if(c >= '0' && c <= '9'){
            state = 11;
        }   
        else{
            errorOccured=1;
            break;
        }
        break;

    case 11:
        if(c >= '0' && c <= '9'){
            state = 12;
        }   
        else{
            errorOccured=1;
            break;
        }
        break;

    case 12:
        if(c == 'E'){
            state = 14;
        }
        else{
            state = 13;
           goBack=1;
            found=1;
            break;
        }
        break;

    case 14:
        if(c == '+' || c == '-'){
            state = 15;
        }
        else if(c >= '0' && c <= '9'){
            state = 16;
        }
        else{
            errorOccured=1;
            break;
        }
        break;

    case 15:
        if(c >= '0' && c <= '9'){
            state = 16;
        }
        else{
             errorOccured=1;
             break;
        }
    break;

    case 16:
        if(c >= '0' && c <= '9'){
            state = 13;
            found=1;
            break;
        }
        else{
             errorOccured=1;
             break;
        }
    break;


    case 18:
        if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
            state = 19;
            break;
        }
        else{
            errorOccured=1;
            break;
        }
    break;

    case 19:
        if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){

            state = 19;
            break;
        }
        else if(c >= '0' && c <= '9'){
            state = 21;
            break;
        }
        else{
            state = 20;
           goBack=1;
            found=1;
            break;
        }
        break;

    case 21:
        if(c >= '0' && c <= '9'){
            state = 21;
        }
        else{
            state = 20;
           goBack=1;
            found=1;
            break;
        }
        break;

    case 24:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            errorOccured=1;
        }
    break;

    case 25:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            state = 26;
            goBack=1;
            found=1;
            break;
        }

       break;

    case 27:
        if(c != '\n'){
            state = 27;
        }
    break;
   
    case 28:   
        if(c == '='){
            state = 29;
            found=1;
            break;
        }
        else if(c == '-'){
            state = 30;
        }
        else{
            state = 33;
            goBack=1;
            found=1;
            break;
        }
    break;


    case 30:
        if(c == '-'){
            state = 31;
        }
        else{
             errorOccured=1;
        }
        break;


    case 31:
        if(c == '-'){
            state = 32;
            found=1;
            break;
        }
        else{
            errorOccured=1;
        }
    break;


    case 45:
        if(c == '&'){
            state = 46;
        }
        else{
             errorOccured=1;
        }
    break;

    case 46:
        if(c == '&'){
            state = 47;
            found=1;
            break;
        }
        else{
             errorOccured=1;
        }
    break;

    case 48:
        if(c == '@'){
            state = 49;
        }
        else{
             errorOccured=1;
        }
    break;

    case 49:
        if(c == '@'){
            state = 50;
            found=1;
            break;
        }
        else{
             errorOccured=1;
        }
    break;

    case 51:
        if(c == '='){
            state = 53;
            found=1;
        }
        else{
            state = 52;
           goBack=1;
            found=1;
            break;
        }
    break;

    case 54:
        if(c == '='){
            state = 55;
            found=1;
            break;
        }
        else{
             errorOccured=1;
        }
    break;

    case 56:
        if(c == '='){
            state = 57;
            found=1;
            break;
        }
        else{
             errorOccured=1;
        }
    break;

    default:
        printf("No Match -> '%c'\n", c);
        break;
    }

    }

    // if(commentFound == 1){
    //     printf("Comment Found: ");
    //     while((feof(fp)==0) || tb->idx<tb->numRead){
    //     c = get_char_from_buffer(fp,tb);
    //     printf("%c", c);
    //     if(c=='\n'){
            
    //         *line_no = *line_no +1;
    //         break;
    //     }
        
    //     }

    //     printf("\n");

    //     return NULL;
    // }

    if(errorOccured == 1){
        printf("Line No: %d\tError: Unknown Symbol<%c>\n", *line_no, c);
    }

    if(goBack == 1){
        retract(tb, &lexeme_idx, &lexeme);
    }

    if(found == 1){
        token * t = (token*)malloc(sizeof(token));
        t->lexeme=lexeme;
        t->lexeme[lexeme_idx]='\0';
        t->line_no=*line_no;
        t->tok=state;
        return t;
    }

    return NULL;
}

void retract(twinBuffer* tb,int *lexeme_idx,char* lexeme){
    tb->idx = tb->idx-1;
    *lexeme_idx = *lexeme_idx-1; 
    lexeme[*lexeme_idx]='\0';  
    
}