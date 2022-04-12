/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
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

#define NON_TERMINAL_COUNT 51
#define TERMINAL_COUNT 62
#define DOLLAR_NOS 59

parseUnit parsetable[NON_TERMINAL_COUNT][TERMINAL_COUNT];

int getNonTerminalNumber(char* lexeme);
int getTerminalNumber(char* lexeme);
void init_parsetable();
int findOrNo(firstAndfollow* ruleset,lhs* Grammar,int nt_no,char* lexeme);
void generate_parsetable(firstAndfollow *ruleset, lhs *Grammar);
void complete_init(firstAndfollow* ruleset, lhs* Grammar);
parseUnit* returnElement(int row, int col);

