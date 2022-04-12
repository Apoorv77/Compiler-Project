/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include<stdio.h>
#include<stdlib.h>
char terminals[62][20] = {"TK_ASSIGNOP",
"TK_COMMENT",
"TK_FIELDID",
"TK_ID",
"TK_NUM",
"TK_RNUM",
"TK_FUNID",
"TK_RECORDID",
"TK_WITH",
"TK_PARAMETERS",
"TK_END",
"TK_WHILE",
"TK_TYPE",
"TK_MAIN",
"TK_GLOBAL",
"TK_PARAMETER",
"TK_LIST",
"TK_SQL",
"TK_SQR",
"TK_INPUT",
"TK_OUTPUT",
"TK_INT",
"TK_REAL",
"TK_COMMA",
"TK_SEM",
"TK_COLON",
"TK_DOT",
"TK_ENDWHILE",
"TK_OP",
"TK_CL",
"TK_IF",
"TK_THEN",
"TK_ENDIF",
"TK_READ",
"TK_WRITE",
"TK_RETURN",
"TK_PLUS",
"TK_MINUS",
"TK_MUL",
"TK_DIV",
"TK_CALL",
"TK_RECORD",
"TK_ENDRECORD",
"TK_ELSE",
"TK_AND",
"TK_OR",
"TK_NOT",
"TK_LT",
"TK_LE",
"TK_EQ",
"TK_GT",
"TK_GE",
"TK_NE",
"TK_UNION",
"TK_DEFINETYPE",
"EPSILON",
"DOLLAR",
"ERROR",
"BOOLEAN",
"LABEL",
"GOTO",
"$"
};

char nonterminals[51][25] = {
"program",
"mainFunction",
"otherFunctions",
"function",
"input_par",
"output_par",
"parameter_list",
"dataType",
"primitiveDatatype",
"constructedDatatype",
"remaining_list",
"stmts",
"typeDefinitions",
"typeDefinition",
"fieldDefinitions",
"fieldDefinition",
"moreFields",
"declarations",
"declaration",
"global_or_not",
"otherStmts",
"stmt",
"assignmentStmt",
"singleOrRecId",
"singleOrNot",
"funCallStmt",
"outputParameters",
"inputParameters",
"iterativeStmt",
"conditionalStmt",
"elseOrNot",
"ioStmt",
"arithmeticExpression",
"moreArithmeticExpression",
"PlusOrMinus",
"term",
"moreFactors",
"MultOrDiv",
"factor",
"varOrRecord",
"EntireRecordOrOneField",
"booleanExpression",
"var",
"logicalOp",
"relationalOp",
"returnStmt",
"optionalReturn",
"idList",
"more_ids",
"definetypestmt",
"A"
};