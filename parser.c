/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
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

treenode* node_found = NULL;
int flag = 0;
void return_node(treenode *root, char *token)
{
    if (root == NULL)
        return;
    if (strcmp(root->token->arr, token) == 0 && flag == 0)
    {
        flag = 1;
        node_found = root;
        printf("inside return_node func. Content of node_found\n");
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        if(root->children[i]==NULL)
        {
            break;
        }
        else{
            return_node(root->children[i], token);
        }
        
    }
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
    printf("entering parser function");
    treenode *root = (treenode *)malloc(sizeof(treenode));
    root->token = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    treenode *nodeptr = root;
    for (int i = 0; i < 10; i++)
    {
        root->children[i] = (treenode *) malloc(sizeof(treenode));
        printf("Allocated to %d\n", i);
    }
    // printf("HELLO\n");
    FILE *input = fopen(inputFile, "r");
    // printf("HELLOo\n");
    if (input == NULL)
    {
        fprintf(stderr, "Error Opening token File\n");
        return NULL;
    }
    
    stack *st = init_stack();
    // printf("hue hue hue 1");
    line_no_and_token *dollar_string = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    strcpy(dollar_string->arr, "$");
    strcpy(dollar_string->line_no, "0");
    // printf("meow meow");
    push(st, dollar_string);
    // printf("hue hue hue 2\n");
    line_no_and_token *program = (line_no_and_token *)malloc(sizeof(line_no_and_token));
    // printf("hue hue hue 3.1\n");
    // printf("hello : %s\n", grammar[0].nonterminal);
    strcpy(program->arr, grammar[0].nonterminal);
    // printf("hue hue hue 3.2\n");
    strcpy(program->line_no, "0");
    // printf("hue hue hue 3.3\n");
    push(st, program);
    // printf("Retured from push\n");
    strcpy(root->token->arr, grammar[0].nonterminal);
    // printf("hue hue hue 4b\n");
    root->parent = NULL;
    // root->parent->line_no = "NULL";
    // printf("hue hue hue 4\n");
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
    printf("\nLine no and token : %s %s\n", line_no, token_name);

    token_name[strlen(token_name) - 1] = '\0';

    while (!feof(input))
    {
        // if(st->i==1)
        // {
        //     //ERORRRRRR
        // }
         printf("Enters the bigger while loop. (feof one)\n");
        line_no_and_token *tempo = top(st);
        printf("top of stack : %s\n", tempo->arr);
        if (tempo->arr[0] != 'T' || tempo->arr[0] != '$')
        {
             printf("token name : %s\n", token_name);
            int col = getTerminalNumber(token_name);
             printf("no of elements in the stack at this point : %d\n", st->i);
             printf("printing the elements of the stack...\n");
             int size = st->i;
             while(size>0)
             {
                 printf("%s ",st->arr[size-1]->arr);
                 size--;
             }
             printf("\nCompleted printing elements of stack\n");
            // printf("top of stack : %s\n", tempo->arr);
            int row = getNonTerminalNumber(tempo->arr);
             printf("row : %d col : %d\n", row, col);
            parseUnit* pu = returnElement(38,21);
             printf("coordinates of the rule in the grammar : %d %d\n", pu->rule_number, pu->or_no);
            if (pu->rule_number == -1)
            {
                printf("Error reported in line %s\n", line_no);
                while (strcmp(tempo->line_no, line_no) == 0)
                {
                    tempo = top(st);
                    pop(st);
                }
                // printf("bhow bhow 4\n");
                int y = atoi(line_no);
                y++;
                return_node_using_line(root, line_no);
                printf("got the node searching through line no. token_name : %s, line_no : %s\n", node_found->token->arr, node_found->token->line_no);
                flag = 0;
                // node_found = node_found->parent;
                push(st, node_found->token);
                printf("Pushed the found token's parent. Current top : %s, token_pushed : %s(Both should be same ideally)\n", top(st)->arr,node_found->token->arr);
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
            printf("element popped : %s\n", pop(st)->arr);
            stack *temp_st = init_stack();
            rhs *temp = grammar[pu->rule_number].rule[pu->or_no];
            printf("grammar[pu->rule_number].nonterminal : %s\n", grammar[pu->rule_number].nonterminal);
            // pushing the tokens in reverse order using another stack
            return_node(root, grammar[pu->rule_number].nonterminal);
            flag = 0;
            printf("returned from return_node func. node_found : %s\n", node_found->token->arr);
            int i = 0;
            while (temp!= NULL)
            {
                printf("Entering into while %dth time\n", i);
                printf("Present content in node_found : %s\n", node_found->token->arr);
                // if(i>0)
                // {
                //     printf("Content in child of node_found : %s %d\n", node_found->children[i-1]->token->arr, i);
                // }
                // if(node_found->children[i]==NULL && i>0)
                // {
                //  printf("Nice %s\n",node_found->children[i-1]->token->arr);
                // }
                printf("PreAlloc Test\n");
                node_found->children[i] = NULL;
                printf("PreAlloc Test\n");
                node_found->children[i] = (treenode*)malloc(sizeof(treenode));
                printf("Memory allocated\n");
                strcpy(node_found->children[i]->token->arr, temp->token);
                printf("node_found->children[i]->token->arr : %s\n",node_found->children[i]->token->arr);
                strcpy(node_found->children[i]->token->line_no, line_no);
                node_found->children[i]->parent = node_found;
                // strcpy(node_found->children[i]->parent->token->line_no,node_found->token->line_no;
                // for (int j = 0; j < 10; j++)
                // {
                //     (node_found->children[i])->children[j] = NULL;
                // }
                printf("Going into the push_func. Doubt about tempo.\n");
                line_no_and_token* ele_to_be_pushed = (line_no_and_token*)malloc(sizeof(line_no_and_token));
                printf("ele defined?\n");
                printf("temp->token : %s\n",temp->token);
                strcpy(ele_to_be_pushed->arr,temp->token);
                printf("ele->arr : %s\n",ele_to_be_pushed->arr);
                strcpy(ele_to_be_pushed->line_no, line_no);
                printf("ele->line_no : %s\n",ele_to_be_pushed->line_no);
                push(temp_st, ele_to_be_pushed);
                // tempo = top(st);
                printf("Came out of push func.\n");
                temp = temp->next;
                if(temp!=NULL)
                {
                    printf("printing contents of temp...\n%s %d\n", temp->token, temp->or_no);
                }
                else{
                    printf("Encountered null\n");
                }
                i++;
            }
            printf("printing the elements of the temp_stack...\n");
            size = temp_st->i;
             while(size>0)
             {
                 printf("%s ",temp_st->arr[size-1]->arr);
                 size--;
             }
             printf("\nCompleted printing elements of temp_stack\n");
            printf("First while loop exited.\n");
            while (temp_st->i > 0)
            {
                push(st, top(temp_st));
                pop(temp_st);
            }
            printf("Second while loop exited.\n");
        }
        else if (tempo->arr[0] == 'T'||tempo->arr[0] =='$') // if it is a terminal
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
    return root;
}

void printparsetree(treenode* root, FILE* ptr)
{
    if(root==NULL)
    return;
    int no_of_children = 0;
    for(int i = 0;i<10;i++)
    {
        if(root->children[i]!=NULL)
        no_of_children++;
    }
    for(int i = 0;i<no_of_children-1;i++)
    {
        printparsetree(root->children[i],ptr);
    }
    char isLeafNode[5];
    strcpy(isLeafNode,(root->token->arr[0]=='T')?"YES":"NO");
    fprintf(ptr,"%s %s %s\n",root->token->arr, root->token->line_no, isLeafNode);
    printparsetree(root->children[no_of_children-1],ptr);

}


// int main()
// {
    //treenode* parser(char* inputFile, parseUnit parsetable[NON_TERMINALS_COUNT][TERMINALS_COUNT], lhs* grammar)
    // FILE *input = fopen("grammar_test_file.txt", "r");
    // if (input == NULL)
    // {
    //     fprintf(stderr, "Error Opening Grammar File\n");
    //     return -1;
    // }
    // grammar = take_input_from_grammar_file(input);
    // printf("\nGRammar taken in successfully\n");
    // FILE *fnf = fopen("FirstAndFollow.txt", "r");
    // firstAndfollow* fnfset = populateFirstandFollow(fnf);
    // printf("FNF done.\n");
    // complete_init(fnfset, grammar);
    // printf("INIT DONE\n");
//     treenode *tree = parser("onliTokens.txt", parsetable, grammar);
//     fclose(input);
//     fclose(fnf);
// }