
#include<stdlib.h>
#include<stdio.h>
#include "twinBuffer.h"
#include "hashtable.h"
#include "lexer.h"
token* getNextToken(FILE* fp,twinBuffer* tb);
void lexical_analysis(FILE* fp);

int main(){
    FILE* fp = fopen("test.txt", "r");
    lexical_analysis(fp);
}
void lexical_analysis(FILE* fp){
    twinBuffer *tb = (twinBuffer*) malloc (sizeof(twinBuffer));
    int size_buffer=BUFFER_SIZE,lexeme_begin,forward;
    tb->use='1'; //Alternate between using buffer one and two
    
    readIntoBuffer(fp,tb);
    char c;
     while(!feof(fp) || tb->idx != tb->numRead){
         printf("Found token\n");
         token* t = getNextToken(fp,tb);
        // printf("%s\n",t->lexeme);
   }
}

token* getNextToken(FILE* fp,twinBuffer* tb){
    int state=0,found=0,idx=0;
    char c;
    char lexeme[50];
    while(1 && found==0){
    c = get_char_from_buffer(fp,tb); 
    lexeme[idx++]=c;
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
        else if(c == '_'){
            state = 18;
        }
        else if(c == '#'){
            state = 24;
        }
        else{
            switch (c)
            {
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
                found=1;
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
            //Error !
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
            retract(tb,&idx,lexeme);
            found=1;
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
           retract(tb,&idx,lexeme);
            found=1;
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
           retract(tb,&idx,lexeme);
           found=1;
        }
        break;

    case 6:
        if(c >= '2' && c <= '7'){
            state = 6;
        }
        else{
            state = 5;
            retract(tb,&idx,lexeme);
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
            retract(tb,&idx,lexeme);
            found=1;
        }
       break;
    case 10:
        if(c >= '0' && c <= '9'){
            state = 11;
        }   
        else{
            //error
        }
        break;

    case 11:
        if(c >= '0' && c <= '9'){
            state = 12;
        }   
        else{
            //error
        }
        break;

    case 12:
        if(c == 'E'){
            state = 14;
        }
        else{
            state = 13;
            retract(tb,&idx,lexeme);
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
            //ERROR
        }
        break;

    case 15:
        if(c >= '0' && c <= '9'){
            state = 16;
        }
        else{
            //error;
        }
    break;

    case 16:
        if(c >= '0' && c <= '9'){
            state = 13;
            found=1;
        }
        else{
            //error
        }
    break;


    case 18:
        if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
            state = 19;
        }
        else{
            //error
        }
    break;

    case 19:
        if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
            state = 19;
        }
        else if(c >= '0' && c <= '9'){
            state = 21;
        }
        else{
            state = 20;
            retract(tb,&idx,lexeme);
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
            retract(tb,&idx,lexeme);
            found=1;
        }
        break;

    case 24:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            //error
        }
    break;

    case 25:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            state = 26;
           retract(tb,&idx,lexeme);
            found=1;
        }

       break;
   
    case 28:   
        if(c == '='){
            state = 29;
            found=1;
        }
        else if(c == '-'){
            state = 30;
        }
        else{
            state = 33;
            retract(tb,&idx,lexeme);
            found=1;
        }
    break;


    case 30:
        if(c == '-'){
            state = 31;
        }
        else{
            //error
        }
        break;


    case 31:
        if(c == '-'){
            state = 32;
            found=1;
        }
        else{
            //error
        }
    break;


    case 45:
        if(c == '&'){
            state = 46;
        }
        else{
            //Error
        }
    break;

    case 46:
        if(c == '&'){
            state = 47;
            found=1;
            break;
        }
        else{
            //error
        }
    break;

    case 48:
        if(c == '@'){
            state = 49;
        }
        else{
            //error
        }
    break;

    case 49:
        if(c == '@'){
            state = 50;
            found=1;
        }
        else{
            //error
        }
    break;

    case 51:
        if(c == '='){
            state = 53;
            found=1;
        }
        else{
            state = 52;
            retract(tb,&idx,lexeme);
            found=1;
        }
    break;

    case 54:
        if(c == '='){
            state = 55;
            found=1;
            break;
        }
        else{
            //error
        }
    break;

    case 56:
        if(c == '='){
            state = 57;
            found=1;
        }
        else{
            //error
        }
    default:
    //Error ,should never land up here
        break;
    }
}
token * t = (token*)malloc(sizeof(token));
t->lexeme=lexeme;
printf("The lexeme is %s\n",t->lexeme);
t->line_no=0;
t->tok=1;
return t;
}


void retract(twinBuffer* tb,int* lexeme_idx,char * lexeme){
    if(tb->idx>0){
        tb->idx--;
    }
    else{
        //points to the beginning of the next buffer, so //retract to the back of the previous buffer
        tb->idx = BUFFER_SIZE-1; //The previous buffer has to full since only then would load up the next buffer
        if(tb->use=='1')tb->use='2';
        else tb->use='1';
        tb->numRead=BUFFER_SIZE; //This buffer will have all valid chars till the end
    }
    lexeme[*lexeme_idx]='\0';
    *lexeme_idx = *lexeme_idx-1;
}