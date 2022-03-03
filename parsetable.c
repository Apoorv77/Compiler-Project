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

void init_parsetable(){
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        for(int j = 0; j < TERMINAL_COUNT; j++){
            parsetable[i][j].rule_number = -1;
            parsetable[i][j].or_no = -1;
        }
    }
}

int findOrNo(char* lexeme, int lineNo, lhs* Grammar){

    for(int i = 0; i < 10; i++){

        if(Grammar[lineNo].rule[i] == NULL){
            // printf("ded\n");
            break;
        }
        else{
            if(strcmp(Grammar[lineNo].rule[i]->token, lexeme) == 0){
                printf("Match: %s\t%s\n", Grammar[lineNo].rule[i]->token, lexeme);
                return i;
            }
        }
    }

    printf("NoMatch: %s\n", lexeme);
    
    return -1;
}

void init_fromfirstset(firstAndfollow* ruleset, lhs* Grammar){
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        first* firstTraversal = ruleset[i].First;
        int nonT_Ref = -1;
        int ter_Ref = -1;
        int orRef = -1;

        nonT_Ref = getNonTerminalNumber(ruleset[i].token);

        while(firstTraversal != NULL){

            ter_Ref = getTerminalNumber(firstTraversal->token);
            
            if(ter_Ref != -1 && nonT_Ref != -1){
                orRef = findOrNo(firstTraversal->token, nonT_Ref, Grammar);
                parsetable[nonT_Ref][ter_Ref].rule_number = nonT_Ref;
                parsetable[nonT_Ref][ter_Ref].or_no = orRef;
            }
            firstTraversal = firstTraversal->next;
        }

    }
}

void init_followSet(firstAndfollow* ruleset, lhs* Grammar){
    
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        if(ruleset[i].epsPres == 0){
            return;
        }
        follow* followTraversal = ruleset[i].Follow;
        int nonT_Ref = -1;
        int ter_Ref = -1;
        int orRef= -1;

        nonT_Ref = getNonTerminalNumber(ruleset[i].token);

        while(followTraversal != NULL){
            ter_Ref = getTerminalNumber(followTraversal->token);
            if(ter_Ref != -1 && nonT_Ref != -1){
                orRef = findOrNo(followTraversal->token, nonT_Ref, Grammar);
                parsetable[nonT_Ref][ter_Ref].rule_number = nonT_Ref;
                parsetable[nonT_Ref][ter_Ref].or_no = orRef;
            }
            followTraversal = followTraversal->next;
    
        }

        if(ruleset->dollarPres == 1){
            nonT_Ref = getNonTerminalNumber(ruleset[i].token);
            orRef = findOrNo("$", nonT_Ref, Grammar);
            parsetable[nonT_Ref][DOLLAR_NOS].rule_number = nonT_Ref;
            parsetable[nonT_Ref][DOLLAR_NOS].or_no = orRef;
        }

    }



}

int getTerminalNumber(char* lexeme){
    for(int i = 0; i < 60; i++){
        if(strcmp(lexeme, terminals[i]) == 0){
            return i;
        }
    }
    return -1;
}

int getNonTerminalNumber(char* lexeme){
    for(int i = 0; i < 59; i++){
        if(strcmp(lexeme, nonterminals[i]) == 0){
            return i;
        }
    }

    return -1;
}

parseUnit* returnElement(int row, int col){
    return &parsetable[row][col];
}

void print_table(){
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        for(int j = 0; j < TERMINAL_COUNT; j++){
            printf("(%d,%d) ", parsetable[i][j].rule_number, parsetable[i][j].or_no);
        }
        printf("\n");
    }
}

void complete_init(firstAndfollow* ruleset, lhs* Grammar){
    init_parsetable();
    printf("Parse Table Initialized\n");
    init_fromfirstset(ruleset, Grammar);
    printf("First Set Table Initialized\n");
    init_followSet(ruleset, Grammar);
    printf("Follwo Set Table Initialized\n");
    // print_table();
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