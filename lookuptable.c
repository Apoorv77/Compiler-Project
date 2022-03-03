/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include "lookuptable.h"
#include <stdlib.h>
#include <string.h>


int hash(char *str){
    // sum(str[i] * pow(p,i) mod m)
    int p = 101,length=strlen(str);
    // printf("%d\n",length);
    long long hashValue = 0,p_pow=1;
    for (int i=0;i<length;i++){
        hashValue = (hashValue + (long long)(str[i]) * p_pow) % HASHTABLE_SIZE;
        p_pow = (p_pow * p) % HASHTABLE_SIZE;
    }
    return hashValue;
}

//Initialize hashtable
void init_lookuptable(lookuptable_element* table){
    if(table == NULL){
        //printf("HashTable allocation not found,Creating One.\n");
    }
    for(int i = 0; i < HASHTABLE_SIZE; i++){
        // strcpy(table[i].token_value, "");
        table[i].added = false;
    //   printf("checking loop %d\n", i);
    }
    
 //   printf("Table Initialized\n");

    add_tokens();

}

void add_tokens(){
    insert_token(lookuptable, "with", "TK_WITH");
    insert_token(lookuptable, "parameters", "TK_PARAMETERS");
    insert_token(lookuptable, "end", "TK_END");
    insert_token(lookuptable, "while", "TK_WHILE");
    insert_token(lookuptable, "union", "TK_UNION");
    insert_token(lookuptable, "endunion", "TK_ENDUNION");
    insert_token(lookuptable, "as", "TK_AS");
    insert_token(lookuptable, "type", "TK_TYPE");
    insert_token(lookuptable, "_main", "TK_MAIN");
    insert_token(lookuptable, "global", "TK_GLOBAL");
    insert_token(lookuptable, "parameter", "TK_PARAMETER");
    insert_token(lookuptable, "list", "TK_LIST");
    insert_token(lookuptable, "input", "TK_INPUT");
    insert_token(lookuptable, "output", "TK_OUTPUT");
    insert_token(lookuptable, "int", "TK_INT");
    insert_token(lookuptable, "real", "TK_REAL");
    insert_token(lookuptable, "endwhile", "TK_ENDWHILE");
    insert_token(lookuptable, "if", "TK_IF");
    insert_token(lookuptable, "then", "TK_THEN");
    insert_token(lookuptable, "endif", "TK_ENDIF");
    insert_token(lookuptable, "read", "TK_READ");
    insert_token(lookuptable, "write", "TK_WRITE");
    insert_token(lookuptable, "return", "TK_RETURN");
    insert_token(lookuptable, "call", "TK_CALL");
    insert_token(lookuptable, "record", "TK_RECORD");
    insert_token(lookuptable, "endrecord", "TK_ENDRECORD");
    insert_token(lookuptable, "else", "TK_ELSE");
    insert_token(lookuptable, "definetype", "TK_DEFINETYPE");
    insert_token(lookuptable, ".", "TK_DOT");
    insert_token(lookuptable, "(", "TK_OP");
    insert_token(lookuptable, "%", "TK_COMMENT");
    insert_token(lookuptable, "<=", "TK_LE");
    insert_token(lookuptable, "<---", "TK_ASSIGNOP");
    insert_token(lookuptable, "<", "TK_LT");
    insert_token(lookuptable, "[", "TK_SQL");
    insert_token(lookuptable, "]", "TK_SQR");
    insert_token(lookuptable, ",", "TK_COMMA");
    insert_token(lookuptable, ";", "TK_SEM");
    insert_token(lookuptable, ":", "TK_COLON");
    insert_token(lookuptable, ")", "TK_CL");
    insert_token(lookuptable, "+", "TK_PLUS");
    insert_token(lookuptable, "-", "TK_MINUS");
    insert_token(lookuptable, "*", "TK_MUL");
    insert_token(lookuptable, "/", "TK_DIV");
    insert_token(lookuptable, "~", "TK_NOT");
    insert_token(lookuptable, "&&&", "TK_AND");
    insert_token(lookuptable, "@@@", "TK_OR");
    insert_token(lookuptable, ">", "TK_GT");
    insert_token(lookuptable, ">=", "TK_GE");
    insert_token(lookuptable, "!=", "TK_NE");
    insert_token(lookuptable, "definetype", "TK_DEFINETYPE");
}

//Insert
void insert_token(lookuptable_element* table,char* lexeme, char* tokenVal){
    int lexeme_hash=hash(lexeme);
    int probe=1;
    while(table[lexeme_hash].added){
        lexeme_hash = (lexeme_hash + (probe*probe)) % HASHTABLE_SIZE;
        probe++;
    }
    strcpy(table[lexeme_hash].lexeme, lexeme);
    strcpy(table[lexeme_hash].token_value, tokenVal);
    table[lexeme_hash].added=true;
    //printf("Token Added: Lexeme: %s\t\t\tTokenValue: %s\n", lexeme, tokenVal);
}

//Search the hash table
char* find_token(lookuptable_element* table, char* lexeme){

    int lexeme_hash = hash(lexeme);
    int probe = 1;


    while(table[lexeme_hash].added){
        if(strcmp(table[lexeme_hash].lexeme, lexeme) == 0){
            return (table[lexeme_hash].token_value);
        }
        else{
            lexeme_hash = ( lexeme_hash + (probe * probe) ) % HASHTABLE_SIZE;
            probe++;
        }
    }

    return NULL;
}

// int main(){
//     init_lookuptable(lookuptable);
//     printf("Queried: %s \t\t Returned: %s\n", "While", find_token(lookuptable, "While"));
//     printf("Queried: %s \t\t Returned: %s\n", "definetype", find_token(lookuptable, "definetype"));
//     printf("Queried: %s \t\t Returned: %s\n", "hehe", find_token(lookuptable, "hehe"));
// }



