#include<stdio.h>
#include "parsetable.h"
#include "parsetree.h"

void return_node(treenode *root, char *token);
void return_node_using_line(treenode *root, char *line_no);
treenode *parser(char *inputFile, parseUnit **parsetable /*[NON_TERMINALS_COUNT][TERMINALS_COUNT]*/, lhs *grammar);