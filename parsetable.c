/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include "parsetable.h"
#include <stdio.h>
#include "ternonter.h"

void init_parsetable()
{
    for (int i = 0; i < NON_TERMINAL_COUNT; i++)
    {
        for (int j = 0; j < TERMINAL_COUNT; j++)
        {
            parsetable[i][j].rule_number = -1;
            parsetable[i][j].or_no = -1;
        }
    }
}

int findOrNo(char *lexeme, int lineNo, lhs *Grammar, firstAndfollow *fnf)
{

    // printf("ToCheck Lexeme: %s RuleNumber: %d\n", lexeme, lineNo);

    if(lexeme == "$"){
        printf("$ found\n");
    }

    for (int i = 0; i < 10; i++)
    {

        if (Grammar[lineNo].rule[i] == NULL)
        {
            // printf("ded\n");
            break;
        }
        else
        {
            rhs *ruleTraversal = Grammar[lineNo].rule[i];
            if (strcmp(ruleTraversal->token, lexeme) == 0)
            {
                return i;
            }

            

            if (ruleTraversal->token[0] != 'T' && ruleTraversal->token[1] != 'K')
            {
                printf("Going Into %s Looking For %s\n", ruleTraversal->token, lexeme);
                int temp = findOrNo(lexeme, getNonTerminalNumber(ruleTraversal->token), Grammar, fnf);
                if (temp != -1)
                {
                    return temp;
                }
            }
            if (Grammar[lineNo].isEpsilon == 1)
            {
                printf("EPS Found going into followset of %s\n", Grammar[lineNo].nonterminal);
                follow *travtemp = fnf[getNonTerminalNumber(Grammar[lineNo].nonterminal)].Follow;
                while (travtemp != NULL)
                {
                    printf("%s->", travtemp->token);

                    if(travtemp->token[strlen(travtemp->token) - 1] == '\n'){
                        travtemp->token[strlen(travtemp->token) - 1] = '\0';
                    }
                    if (strcmp(travtemp->token, lexeme) == 0)
                    {   
                        printf("Found %s in followset of %s\n", lexeme, Grammar[lineNo].nonterminal);
                        return i;
                    }
                    else
                    {
                        travtemp = travtemp->next;
                    }
                }
                printf("\n");
            }
        }
    }

    printf("NoMatch: %s\n", lexeme);

    return -1;
}

void init_fromfirstset(firstAndfollow *ruleset, lhs *Grammar)
{
    for (int i = 0; i < NON_TERMINAL_COUNT; i++)
    {
        first *firstTraversal = ruleset[i].First;
        int nonT_Ref = -1;
        int ter_Ref = -1;
        int orRef = -1;

        nonT_Ref = getNonTerminalNumber(ruleset[i].token);

        while (firstTraversal != NULL)
        {

            ter_Ref = getTerminalNumber(firstTraversal->token);

            if (ter_Ref != -1 && nonT_Ref != -1)
            {
                orRef = findOrNo(firstTraversal->token, nonT_Ref, Grammar, ruleset);
                parsetable[nonT_Ref][ter_Ref].rule_number = nonT_Ref;
                parsetable[nonT_Ref][ter_Ref].or_no = orRef;
                printf("added first %d %d %d\n", nonT_Ref, ter_Ref, orRef);
            }
            firstTraversal = firstTraversal->next;
        }

        if(ruleset[i].epsPres == 1){
            follow* traversal = ruleset[i].Follow;
            nonT_Ref = -1;
            ter_Ref = -1;
            orRef = -1;

            nonT_Ref = getNonTerminalNumber(ruleset[i].token);
            
            while (traversal != NULL)
            {
            ter_Ref = getTerminalNumber(traversal->token);

            if (ter_Ref != -1 && nonT_Ref != -1)
            {
                orRef = findOrNo(traversal->token, nonT_Ref, Grammar, ruleset);
                parsetable[nonT_Ref][ter_Ref].rule_number = nonT_Ref;
                parsetable[nonT_Ref][ter_Ref].or_no = orRef;
                printf("epsilon added first %d %d %d\n", nonT_Ref, ter_Ref, orRef);
            }
            traversal = traversal->next;

            if (ruleset[i].dollarPres == 1)
            {
            nonT_Ref = getNonTerminalNumber(ruleset[i].token);
            orRef = findOrNo("$", nonT_Ref, Grammar, ruleset);
            parsetable[nonT_Ref][DOLLAR_NOS].rule_number = nonT_Ref;
            parsetable[nonT_Ref][DOLLAR_NOS].or_no = orRef;
            }
        }


        }
    }
}

// void init_followSet(firstAndfollow *ruleset, lhs *Grammar)
// {

//     for (int i = 0; i < NON_TERMINAL_COUNT; i++)
//     {
//         // if(ruleset[i].epsPres == 0){
//         //     return;
//         // }
//         follow *followTraversal = ruleset[i].Follow;
//         int nonT_Ref = -1;
//         int ter_Ref = -1;
//         int orRef = -1;

//         nonT_Ref = getNonTerminalNumber(ruleset[i].token);

//         while (followTraversal != NULL)
//         {
//             ter_Ref = getTerminalNumber(followTraversal->token);
//             if (ter_Ref != -1 && nonT_Ref != -1)
//             {
//                 orRef = findOrNo(followTraversal->token, nonT_Ref, Grammar, ruleset);
//                 parsetable[nonT_Ref][ter_Ref].rule_number = nonT_Ref;
//                 parsetable[nonT_Ref][ter_Ref].or_no = orRef;
//                 printf("added successfully\n");
//             }
//             followTraversal = followTraversal->next;
//         }

//         if (ruleset->dollarPres == 1)
//         {
//             nonT_Ref = getNonTerminalNumber(ruleset[i].token);
//             orRef = findOrNo("$", nonT_Ref, Grammar, ruleset);
//             parsetable[nonT_Ref][DOLLAR_NOS].rule_number = nonT_Ref;
//             parsetable[nonT_Ref][DOLLAR_NOS].or_no = orRef;
//         }
//     }
// }

int getTerminalNumber(char *lexeme)
{
    for (int i = 0; i < 60; i++)
    {
        if (strcmp(lexeme, terminals[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int getNonTerminalNumber(char *lexeme)
{
    for (int i = 0; i < 59; i++)
    {
        if (strcmp(lexeme, nonterminals[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

parseUnit *returnElement(int row, int col)
{
    return &parsetable[row][col];
}

void print_table()
{
    for (int i = 0; i < NON_TERMINAL_COUNT; i++)
    {
        for (int j = 0; j < TERMINAL_COUNT; j++)
        {
            printf("(%d,%d) ", parsetable[i][j].rule_number, parsetable[i][j].or_no);
        }
        printf("\n");
    }
}

void complete_init(firstAndfollow *ruleset, lhs *Grammar)
{
    init_parsetable();
    printf("Parse Table Initialized\n");
    init_fromfirstset(ruleset, Grammar);
    printf("First Set Table Initialized\n");
    // init_followSet(ruleset, Grammar);
    printf("Follwo Set Table Initialized\n");
    print_table();
}

// int main(){
//     firstAndfollow* temp = (firstAndfollow*)malloc(sizeof(firstAndfollow));

//     strcpy(temp->token, "program");
//     temp->epsPres = 0;
//     temp->dollarPres = 0;

//     temp->First = (first *)malloc(sizeof(first));
//     temp->Follow = (follow *)malloc(sizeof(follow));

//     strcpy(temp->First->token,"TK_ASSIGNOP");
//     strcpy(temp->Follow->token, "TK_COMeMENT");

//     temp->First->next = NULL;
//     temp->epsPres = 1;
//     temp->dollarPres = 0;

//     strcpy(grammar[0].nonterminal,"program");

//     rhs* temp2 = malloc(sizeof(rhs));
//     temp2->isNonTerm = 0;
//     strcpy(temp2->token,"TK_ASSIGNOP");
//     temp2->next = NULL;

//     rhs* temp3 = malloc(sizeof(rhs));
//     temp3->isNonTerm = 0;
//     strcpy(temp3->token,"TK_COMMENT");
//     temp3->next = NULL;

//     grammar[0].rule[0] = temp2;
//     grammar[0].rule[1] = temp3;

//     init_parsetable();
//     init_fromfirstset(temp, grammar);
//     init_followSet(temp, grammar);

//     printf("%d,%d,%d,%d\n", parsetable[0][0].rule_number, parsetable[0][0].or_no, parsetable[0][1].rule_number, parsetable[0][1].or_no);

// }