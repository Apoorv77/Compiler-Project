/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "first_and_follow.h"
#include "grammar_def.h"

typedef struct parseunit{
    int rule_number;
    int or_no;
}parseUnit;

#define NON_TERMINAL_COUNT 60
#define TERMINAL_COUNT 60
#define DOLLAR_NOS 60

parseUnit parsetable[NON_TERMINAL_COUNT][TERMINAL_COUNT];

int getNonTerminalNumber(char* lexeme);
int getTerminalNumber(char* lexeme);
void init_parsetable();
int findOrNo(char* lexeme, int lineNo, lhs* Grammar, firstAndfollow* fnf);
void init_fromfirstset(firstAndfollow* ruleset, lhs* Grammar);
void init_followSet(firstAndfollow* ruleset, lhs* Grammar);
void complete_init(firstAndfollow* ruleset, lhs* Grammar);
parseUnit* returnElement(int row, int col);

