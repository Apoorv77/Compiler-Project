/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdio.h>
typedef struct First{
    char token[50];
    struct First* next;
}first;

typedef struct Follow{
    char token[50];
    struct Follow* next;
}follow;

typedef struct FirstAndFollow{
    char token[50];
    first* First;
    follow* Follow;
    int epsPres;
    int dollarPres;
}firstAndfollow;

firstAndfollow * populateFirstandFollow(FILE* ptr);
void print_fnf(firstAndfollow* fnf);