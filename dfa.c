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
            default:
                break;
            }
        }
        break;
    
    default:
        break;
    }
}