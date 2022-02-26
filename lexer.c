
#include "twinBuffer.h"
#include "hashtable.h"
#include<stdlib.h>
#include<stdio.h>

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
     while(!feof(fp)){
         token* t = getNextToken(fp,tb);
         printf("%s\n",t->lexeme);
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
                break;
            case '<':
                state=28;
                break;
            case '[':
                state=34;
                break;
            case ']':
                state=35;
                break;
            case ',':
                state=36;
                break;
            case ';':
                state=37;
                break;
            case ':':
                state=38;
                break;
            case ')':
                state=39;
                break;
            case '+':
                state = 40;
                break;
            case '-':
                state = 41;
                break;
            case '*':
                state = 42;
                break;
            case '/':
                state = 43;
                break;
            case '~':
                state = 44;
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
            //Retract
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
           // //retract();
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
           // //retract();
            break;
            //Retract by one
            //token funfield found
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
           // //retract();
            break;
        }
    break;


    case 6:
        if(c >= '2' && c <= '7'){
            state = 6;
        }
        else{
            state = 5;
            //retract();
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
            //retract();
            break;
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
            ////retract();
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
    break;

    case 15:
        if(c >= '0' && c <= '9'){
            state = 16;
        }
        else{
            //eroor;
        }
    break;

    case 16:
        if(c >= '0' && c <= '9'){
            state = 17;
        }
    break;

    case 17:
        if(!(c >= '0' && c <= '9')){
            state = 13;
            //retract();
            break;
        }
    break;

    case 18:
        if(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
            state = 19;
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
            ////retract();
            break;
        }
    break;

    case 21:
        if(c >= '0' && c <= '9'){
            state = 21;
        }
        else{
            state = 20;
            //retract();
            break;
        }
    break;

    case 24:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            //eroor
        }
    break;

    case 25:
        if(c >= 'a' && c <= 'z'){
            state = 25;
        }
        else{
            state = 26;
           // //retract();
            break;
        }

    break;
   
    case 28:   
        if(c == '='){
            state = 29;
            break;
        }
        else if(c == '-'){
            state = 30;
        }
        else{
            state = 33;
           // //retract();
            break;
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
            break;
        }
        else{
            break;
        }
    break;


    case 45:
        if(c == '&'){
            state = 46;
            break;
        }
        else{
            break;
        }
    break;

    case 46:
        if(c == '&'){
            state = 47;
            break;
        }
        else{
            break;
        }
    break;

    case 48:
        if(c == '@'){
            state = 49;
        }
        else{
            break;
        }
    break;

    case 49:
        if(c == '@'){
            state = 50;
            break;
        }
        else{
            break;
        }
    break;

    case 51:
        if(c == '='){
            state = 53;
            break;
        }
        else{
            state = 52;
            break;
        }
    break;

    case 54:
        if(c == '='){
            state = 55;
            break;
        }
        else{
            break;
        }
    break;

    case 56:
        if(c == '='){
            state = 57;
            break;
        }
        else{
            break;
        }
   
    default:
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