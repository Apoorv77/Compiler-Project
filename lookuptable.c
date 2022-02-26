#include "lookuptable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hash(char *str){
    // sum(str[i] * pow(p,i) mod m)
    int p = 101,length=strlen(str);
    // printf("%d\n",length);
    long long hashValue = 0,p_pow=1;
    for (int i=0;i<length;i++){
        hashValue = (hashValue + (long long)(str[i] - 'a' + 1) * p_pow) % HASHTABLE_SIZE;
        p_pow = (p_pow * p) % HASHTABLE_SIZE;
    }
    return hashValue;
}

//Initialize hashtable
void init_lookuptable(lookuptable_element* table){
    if(table == NULL){
        printf("HashTable allocation not found,Creating One.\n");
    }
    for(int i = 0; i < HASHTABLE_SIZE; i++){
        table[i].token_value = "";
        table[i].added = false;
    //   printf("checking loop %d\n", i);
    }
    
    printf("Table Initialized\n");
}

//Insert
void insert_token(lookuptable_element* table,char* lexeme, char* tokenVal){
    printf("Inside insert token function\n");
    int lexeme_hash=hash(Token->lexeme);
    int probe=1;
    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash].added){
        if(strcmp(table[lexeme_hash].token_value,lexeme) == 0){
            break;
            printf("PreExisting Token found \n");
        }

        lexeme_hash = (lexeme_hash + (probe*probe)) % HASHTABLE_SIZE;
        probe++;
    }

    printf("Empty Space Found\n");
    table[lexeme_hash].token_value = tokenVal;
    table[lexeme_hash].added=true;
    printf("Token Added\n");
}

//Search the hash table
token* find_token(lookuptable_element* table, char* lexeme){
    printf("Inside find_token\n");

    int lexeme_hash = hash(lexeme);
    int probe = 1;

    printf("Lexeme Hashed: %d\n", lexeme_hash);
    while(table[lexeme_hash].added){
        if(strcmp(table[lexeme_hash].token_value, lexeme) == 0){
            printf("Found\n");
            return (table[lexeme_hash].token_value);
        }
        else{
            lexeme_hash = ( lexeme_hash + (probe * probe) ) % HASHTABLE_SIZE;
            probe++;
        }
    }

    return NULL;
}

//add the next part to the actual file

// insert_token(lookuptable, "with", "TK_WITH");
// insert_token(lookuptable, "parameters", "TK_PARAMETERS");
// insert_token(lookuptable, "end", "TK_END");
// insert_token(lookuptable, "While", "TK_WHILE");
// insert_token(lookuptable, "Union", "TK_UNION");
// insert_token(lookuptable, "endunion", "TK_ENDUNION");
// insert_token(lookuptable, "as", "TK_AS");
// insert_token(lookuptable, "Type", "TK_TYPE");
// insert_token(lookuptable, "_main", "TK_MAIN");
// insert_token(lookuptable, "Global", "TK_GLOBAL");
// insert_token(lookuptable, "parameter", "TK_PARAMETER");
// insert_token(lookuptable, "List", "TK_LIST");
// insert_token(lookuptable, "Input", "TK_INPUT");
// insert_token(lookuptable, "Output", "TK_OUTPUT");
// insert_token(lookuptable, "Int", "TK_INT");
// insert_token(lookuptable, "Real", "TK_REAL");
// insert_token(lookuptable, "endwhile", "TK_ENDWHILE");
// insert_token(lookuptable, "If", "TK_IF");
// insert_token(lookuptable, "Then", "TK_THEN");
// insert_token(lookuptable, "Endif", "TK_ENDIF");
// insert_token(lookuptable, "Read", "TK_READ");
// insert_token(lookuptable, "Write", "TK_WRITE");
// insert_token(lookuptable, "Return", "TK_RETURN");
// insert_token(lookuptable, "Call", "TK_CALL");
// insert_token(lookuptable, "Record", "TK_RECORD");
// insert_token(lookuptable, "endrecord", "TK_ENDRECORD");
// insert_token(lookuptable, "Else", "TK_ELSE");
// insert_token(lookuptable, "definetype", "TK_DEFINETYPE");

