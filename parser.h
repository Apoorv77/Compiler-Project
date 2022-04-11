/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include<stdio.h>
#include "parsetable.h"
#include "parsetree.h"

void return_node(treenode *root, char *token);
void return_node_using_line(treenode *root, char *line_no);
treenode *parser(char *inputFile, parseUnit **parsetable /*[NON_TERMINALS_COUNT][TERMINALS_COUNT]*/, lhs *grammar);