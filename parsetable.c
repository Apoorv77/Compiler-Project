#include "parsetable.h"
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

        while(firstTraversal != NULL){

        }

    }
}

int getTokenNumber(char* lexeme){
    
}