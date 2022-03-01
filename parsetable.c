#include "parsetable.h"
#include "first_And_follow.h"
#include <stdio.h>

void init_parsetable(){
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        for(int j = 0; j < TERMINAL_COUNT; j++){
            parsetable[i][j] = -1;
        }
    }
}

void init_fromfirstset(FirstAndFollow* ruleset){
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        first* firstTraversal = ruleset[i].First;
        int nonT_Ref = -1;
        int ter_Ref = -1;

        nonT_Ref = getNonTerminalNumber(ruleset[i].token);

        while(firstTraversal != NULL){
            ter_Ref = getTerminalNumber(firstTraversal.token);
            if(ter_Ref != -1 && nonT_Ref != -1){
                parsetable[nonT_Ref][ter_Ref] = nonT_ref;
            }
            firstTraversal = firstTraversal->next;
        }

    }
}

void init_followSet(FirstAndFollow* ruleset){
    if(ruleset.epsFound == 0){
        return;
    }
    for(int i = 0; i < NON_TERMINAL_COUNT; i++){
        follow* followTraversal = ruleset[i].Follow;
        int nonT_Ref = -1;
        int ter_Ref = -1;

        nonT_Ref = getNonTerminalNumber(ruleset[i].token);

        while(followTraversal != NULL){
            ter_Ref = getTerminalNumber(followTraversal.token)
            if(ter_Ref != -1 && nonT_Ref != -1){
                parsetable[nonT_Ref][ter_Ref] = i;
            }
    
        }

        if(dollarPres == 1){
            nonT_Ref = getNonTerminalNumber(ruleset[i].token);
            parseTable[nonT_Ref][DOLLAR_NOS] = i;
        }

    }



}

int getTerminalNumber(char* lexeme){
    FILE* fp =  fopen("terminals.txt", "r");
    int tok_count = 1;

    char token_read[50];

    char c;

    while(feof(fp) == 0){
        int char_read = 0;
        
        while(fp != '\n'){
            c = fgetc(fp);
            token_read[char_read++] = c;
        }
        token_read[char_read] = '\0';

        if(strcmp(token_read, lexeme) == 0){
            return tok_count;        
        }
        else{
            tok_count++;
        }
    }
    fclose(fp);
    return -1;
}

int getNonTerminalNumber(char* lexeme){
    FILE* fp =  fopen("nonterminals.txt", "r");
    int tok_count = 1;

    char token_read[50];

    char c;

    while(feof(fp) == 0){
        int char_read = 0;
        
        while(fp != '\n'){
            c = fgetc(fp);
            token_read[char_read++] = c;
        }
        token_read[char_read] = '\0';

        if(strcmp(token_read, lexeme) == 0){
            return tok_count;        
        }
        else{
            tok_count++;
        }
    }

    fclose(fp);
    return -1;
}