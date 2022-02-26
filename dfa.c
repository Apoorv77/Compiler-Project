#include<stdio.h>
int main(){


    switch (state)
    {
    case 0:
        if('a'<=c && c<='z' && !('b'<=c && c<='d')){
            state=1;
        }
        else if('b'<=c && c<='d')state=3;
        else if('0'<=c && c<='9')state=8;
        else{
            switch (c)
            {
            case '.':
                state=22;
                break;
            case '(':
                state=23;
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
                break;
            }
        }
        break;
    case 28:
        c = get_char_From_buffer(fp);      // plaacholder for now
        if(c == '='){
            state = 29;
            break;
        }
        else if(c == '-')(
            state = 30;
        )
        else{
            state = 33;
            break;
        }
    case 30:
        c = get_char_From_buffer(fp);
        if(c == '-'){
            state = 31;
        }
        else{
            break;
        }
    case 31:
        c = get_char_From_buffer(fp);
        if(c == '-'){
            state = 32;
            break;
        }
        else{
            break;
        }
    case 45:
        c = get_char_From_buffer(fp);
        if(c == '&'){
            state = 46;
        }
        else{
            break;
        }
    case 46:
        c = get_char_From_buffer(fp);
        if(c == '&'){
            state = 47;
            break;
        }
        else{
            break;
        }
    case 48:
        c = get_char_From_buffer(fp);
        if(c == '@'){
            state = 49;
        }
        else{
            break;
        }
    case 49:
        c = get_char_From_buffer(fp);
        if(c == '@'){
            state = 50;
            break;
        }
        else{
            break;
        }
    case 51:
        c = get_char_From_buffer(fp);
        if(c == '='){
            state = 53;
            break;
        }
        else{
            state = 52;
            break;
        }
    case 54:
        c = get_char_From_buffer(fp);
        if(c == '='){
            state = 55;
            break;
        }
        else{
            break;
        }
    case 56:
        c = get_char_From_buffer(fp);
        if(C == '='){
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