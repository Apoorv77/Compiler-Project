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
}firstAndfollow;

