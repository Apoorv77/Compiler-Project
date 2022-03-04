/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
// #include "first_and_follow.h"
// #include "header_fnf.h"

treenode *node_found = NULL;
int flag = 0;
void return_node(treenode *root, char *token)
{
    if (root == NULL)
        return;
    if (strcmp(root->token->arr, token) == 0 && flag == 0)
    {
        flag = 1;
        node_found = root;
        return;
    }
    for (int i = 0; i < 10; i++)
        return_node(root->children[i], token);
}

void return_node_using_line(treenode *root, char *line_no)
{
    if (root == NULL)
        return;
    if (strcmp(root->token->line_no, line_no) == 0 && flag == 0)
    {
        flag = 1;
        node_found = root;
        return;
    }
    for (int i = 0; i < 10; i++)
        return_node_using_line(root->children[i], line_no);
}

treenode *parser(char *inputFile, parseUnit **parsetable /*[NON_TERMINALS_COUNT][TERMINALS_COUNT]*/, lhs *grammar)
{

    treenode *root = (treenode *)malloc(sizeof(treenode));
    root->token = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    treenode *nodeptr = root;
    for (int i = 0; i < 10; i++)
        root->children[i] = NULL;
    printf("HELLO\n");
    FILE *input = fopen(inputFile, "r");
    printf("HELLOo\n");
    if (input == NULL)
    {
        fprintf(stderr, "Error Opening token File\n");
        return NULL;
    }
    
    stack *st = init_stack();
    printf("hue hue hue 1");
    line_no_and_token *dollar_string = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    strcpy(dollar_string->arr, "$");
    strcpy(dollar_string->line_no, "0");
    printf("meow meow");
    push(st, dollar_string);
    printf("hue hue hue 2\n");
    line_no_and_token *program = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    printf("hue hue hue 3.1\n");
    printf("hello : %s\n", grammar[0].nonterminal);
    strcpy(program->arr, grammar[0].nonterminal);
    printf("hue hue hue 3.2\n");
    strcpy(program->line_no, "0");
    printf("hue hue hue 3.3\n");
    push(st, program);
    printf("Retured from push\n");
    strcpy(root->token->arr, grammar[0].nonterminal);
    printf("hue hue hue 4b\n");
    root->parent = NULL;
    // root->parent->line_no = "NULL";
    printf("hue hue hue 4\n");
    char str[50];
    fgets(str, 50, input);
    char line_no[10];
    char token_name[20];
    char *token = strtok(str, " ");
    strcpy(line_no, token);
    token = strtok(NULL, " ");
    if (token[0] == 'T')
    {
        strcpy(token_name, token);
    }
    else
    {
        strcpy(token_name, "ERROR");
    }
    printf("\nHue hue hue 5 %s %s\n", line_no, token_name);

    token_name[strlen(token_name) - 1] = '\0';

    while (!feof(input))
    {
        // if(st->i==1)
        // {
        //     //ERORRRRRR
        // }
        printf("bhow bhow\n");
        line_no_and_token *tempo = top(st);
        printf("bhow bhow 2\n %s", tempo->arr);
        if (tempo->arr[0] != 'T' || tempo->arr[0] != '$')
        {
            printf("hsgfg%sjbhjbh\n", token_name);
            int col = getTerminalNumber(token_name);
            printf("hello : %d", st->i);
            printf("bhow bhow 2.2 %s\n", tempo->arr);
            int row = getNonTerminalNumber(tempo->arr);
            printf("bhow bhow 2.3\n");
            printf("%d %d\n", row, col);
            parseUnit* pu = returnElement(38,5);
            printf("hell : %d %d\n", pu->rule_number, pu->or_no);
            if (pu->rule_number == -1)
            {
                //ERROR + recovery
                printf("bhow bhow 3\n");
                printf("Error reported in line %s\n", line_no);
                while (strcmp(tempo->line_no, line_no) == 0)
                {
                    tempo = top(st);
                    pop(st);
                }
                printf("bhow bhow 4\n");
                int y = atoi(line_no);
                y++;
                return_node_using_line(root, line_no);
                printf("bhow bhow 5\n");
                flag = 0;
                node_found = node_found->parent;
                push(st, node_found->token);
                printf("bhow bhow 6\n");

                while (1)
                {
                    fgets(str, 50, input);
                    token = strtok(str, " ");
                    strcpy(line_no, token);
                    token = strtok(NULL, " ");
                    if (token[0] == 'T')
                    {
                        strcpy(token_name, token);
                    }
                    else
                    {
                        strcpy(token_name, "ERROR");
                    }
                    if (y == atoi(line_no))
                        break;
                }
            }
            printf("bhow bhow 40.0\n");
            pop(st);
            printf("bhow bhow 40.1\n");
            stack *temp_st = init_stack();
            rhs *temp = grammar[pu->rule_number].rule[pu->or_no];
            printf("bhow bhow 40\n");
            // pushing the tokens in reverse order using another stack
            int i = 0;
            return_node(root, grammar[pu->rule_number].nonterminal);
            flag = 0;
            while (temp->next->next != NULL)
            {
                node_found->children[i] = (treenode *)malloc(sizeof(treenode));
                strcpy(node_found->children[i]->token->arr, tempo->arr);
                strcpy(node_found->children[i]->token->line_no, tempo->line_no);
                node_found->children[i]->parent = node_found;
                // node_found->children[i]->parent->line_no = node_found->token->line_no;
                for (int j = 0; j < 10; j++)
                    node_found->children[i]->children[j] = NULL;
                push(temp_st, tempo);
                i++;
            }
            while (temp_st->i > 0)
            {
                push(st, top(temp_st));
                pop(temp_st);
            }
            printf("bhow bhow 3");
        }
        else if (tempo->arr[0] == 'T') // if it is a terminal
        {
            if (strcmp(tempo->arr, token_name) == 0)
            {
                if (strcmp(tempo->arr, "$") == 0)
                {
                    break;
                }
                else
                {
                    pop(st);
                    // gets the next token
                    fgets(str, 50, input);
                    char *token = strtok(str, " ");
                    strcpy(line_no, token);
                    token = strtok(NULL, " ");
                    if (token[0] == 'T')
                    {
                        strcpy(token_name, token);
                    }
                    else
                    {
                        strcpy(token_name, "ERROR");
                    }
                }
            }
            else
            {
                //ERROR + recovery
                printf("Error reported in line %s\n", line_no);
                while (strcmp(tempo->line_no, line_no) == 0)
                {
                    tempo = top(st);
                    pop(st);
                }
                int y = atoi(line_no);
                y++;
                return_node_using_line(root, line_no);
                flag = 0;
                node_found = node_found->parent;
                push(st, node_found->token);
                while (1)
                {
                    fgets(str, 50, input);
                    token = strtok(str, " ");
                    strcpy(line_no, token);
                    token = strtok(NULL, " ");
                    if (token[0] == 'T')
                    {
                        strcpy(token_name, token);
                    }
                    else
                    {
                        strcpy(token_name, "ERROR");
                    }
                    if (y == atoi(line_no))
                        break;
                }
            }
        }
    }
    fclose(input);
    return nodeptr;
}

int main()
{
    //treenode* parser(char* inputFile, parseUnit parsetable[NON_TERMINALS_COUNT][TERMINALS_COUNT], lhs* grammar)
    FILE *input = fopen("grammar_test_file.txt", "r");
    if (input == NULL)
    {
        fprintf(stderr, "Error Opening Grammar File\n");
        return -1;
    }
    grammar = take_input_from_grammar_file(input);
    printf("\nGRammar taken in successfully\n");
    FILE *fnf = fopen("FirstAndFollow.txt", "r");
    firstAndfollow* fnfset = populateFirstandFollow(fnf);
    printf("FNF done.\n");
    complete_init(fnfset, grammar);
    printf("INIT DONE\n");
    treenode *tree = parser("onliTokens.txt", parsetable, grammar);
    fclose(input);
    fclose(fnf);
}