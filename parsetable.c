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

// int compare(char* s1,char* s2){
//     int i=0,j=0;
//     while(s1[i] != '\0' && s2[j] != '\0'){
//         if(s1[i] != s2[j])return 1;
//         i++;
//         j++;
//     }
//     if(s1[i]>='a' && s1[i]<='z' || s1[i]>='A' && s1[i]<='Z' || s1[i]=='_')return 1;
//     if(s2[j]>='a' && s2[j] <='z' || s2[j]>='A' && s2[j]<='Z' || s2[j]=='_')return 1;
//     return 0;
// }
int getTerminalNumber(char *lexeme)
{
    
    for (int i = 0; i < 60; i++)
    {   
        if (strcmp(lexeme, terminals[i]) == 0) return i;
    }
    printf("Didnt find the terminal:%s\n",lexeme);
    return -1;
}

int getNonTerminalNumber(char *lexeme)
{
    for (int i = 0; i < 51; i++)
    {
        
        if (strcmp(lexeme, nonterminals[i]) == 0)
        {
            return i;
        }
    }
    printf("Didnt find the non-terminal:%s\n",lexeme);
    return -1;
}

parseUnit *returnElement(int row, int col)
{
    return &parsetable[row][col];
}

int findOrNo(firstAndfollow* ruleset,lhs* Grammar,int nt_no,char* lexeme){
    //printf("%d\n",nt_no);
    for(int i=0;i<10;i++){
        if(Grammar[nt_no].rule[i] == NULL){
            //lexeme didnt exist in its first set ,should never happen
            break;
        }
        
        rhs* rule = Grammar[nt_no].rule[i];
        //if terminal,check for equality
       // printf("%d %s\n",i,rule->token);
        if(rule->isNonTerm == 1 &&  strcmp(rule->token,lexeme) == 0)return i;
        //if non-terminal , check if it belongs to its first set
        if(rule->isNonTerm == 0){
            int rule_no = getNonTerminalNumber(rule->token);
            if(rule_no == -1){
                printf("That nt doesn't exist in the array\n");
            }
            else{
                // if(nt_no==23)printf("%s\n",rule->token);
                first* first_set_ptr = ruleset[rule_no].First;
                while(first_set_ptr != NULL){
                    // if(nt_no==23)printf("*%s %s*\n",first_set_ptr->token,lexeme);
                    
                    if(strcmp(first_set_ptr->token,lexeme) == 0){
                        // if(nt_no==23)printf("Ola\n");
                        return i;
                    }
                    first_set_ptr = first_set_ptr->next;
                    //printf("%s\n",first_set_ptr->token);
                }
                if(ruleset[rule_no].epsPres == 1){
                    follow* follow_ptr = ruleset[rule_no].Follow;
                    while(follow_ptr != NULL){
                        if(strcmp(follow_ptr->token,lexeme)==0)return i;
                        follow_ptr = follow_ptr->next;
                    }
                }
            }
        }
    }
    return -1;
}

void generate_parsetable(firstAndfollow *ruleset, lhs *Grammar){
    for(int i=0;i<NON_TERMINAL_COUNT;i++){
        //TYPE-1
        first* first_set_ptr = ruleset[i].First;
        int row = getNonTerminalNumber(ruleset[i].token),col;
        while(first_set_ptr != NULL){
            col = getTerminalNumber(first_set_ptr->token);
            int orNumOfRule = findOrNo(ruleset,Grammar,i,first_set_ptr->token);
            //printf("%d %d %d\n",row,col,orNumOfRule);
            if(orNumOfRule == -1){
                printf("No rule found for %s and %s %d %d\n",ruleset[i].token,first_set_ptr->token,row,col);
            }
            else{
                parsetable[row][col].or_no = orNumOfRule;
                parsetable[row][col].rule_number = row;
            }
            first_set_ptr = first_set_ptr->next;
        }

        if(ruleset[i].epsPres == 1){
            //insert the rule for all elements in follow(A)
            // *** OR NUMBER = 11 will represent taking A-> epsilon
            //TYPE-2
            follow* follow_set_ptr = ruleset[i].Follow;
            while(follow_set_ptr != NULL){
                col = getTerminalNumber(follow_set_ptr->token);
                parsetable[row][col].rule_number=row;
                parsetable[row][col].or_no = 11;
                follow_set_ptr = follow_set_ptr->next;
            }
            //TYPE-3
            if(ruleset[i].dollarPres ==1){
                parsetable[row][DOLLAR_NOS].rule_number=row;
                parsetable[row][DOLLAR_NOS].or_no = 11;
            }
        }

    }
}


void print_table()
{
    for (int i = 0; i < NON_TERMINAL_COUNT; i++)
    {
        for (int j = 0; j < TERMINAL_COUNT; j++)
        {           //if(parsetable[i][j].rule_number != -1 && parsetable[i][j].or_no != -1)
                    printf("(%d,%d) ", parsetable[i][j].rule_number, parsetable[i][j].or_no);
        }
        printf("\n");
     }
}


void complete_init(firstAndfollow *ruleset, lhs *Grammar)
{
    init_parsetable();
    printf("Parse Table Initialized\n");
    generate_parsetable(ruleset,Grammar);
    //print_table();
}


int main()
{
    FILE *input = fopen("FirstAndFollow.txt", "r");
    firstAndfollow *fnf = populateFirstandFollow(input);
    //print_fnf(fnf);
    FILE *fp = fopen("grammar_test_file.txt", "r");
    lhs *grammar = take_input_from_grammar_file(fp);
    complete_init(fnf,grammar);
    first* f = fnf[0].First;
}