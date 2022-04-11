/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/
#include <stdio.h>
# define MAX_SIZE_OF_SYMBOL 50
/*
The definitions of NonTerminal and Terminal need to be pasted here.

It would be of the form 
typedef enum{
    stuff
}Terminal;

typedef enum{
    stuff
}NonTerminal;
*/
typedef enum{
    program,
	mainFunction,
	otherFunctions,
	stmts,
	function,
	input_par,
	parameter_list,
	output_par,
	dataType,
	remaining_list,
	primitiveDatatype,
	constructedDatatype,
	typeDefinitions,
	declarations,
	otherStmts,
	returnStmt,
	actualOrRedefined,
	typeDefinition,
	definetypestmt,
	fieldDefinitions,
	fieldDefinition,
	moreFields,
	fieldType,
	declaration,
	global_or_not,
	stmt,
	assignmentStmt,
	iterativeStmt,
	conditionalStmt,
	ioStmt,
	funCallStmt,
	singleOrRecId,
	arithmeticExpression,
	option_single_constructed,
	oneExpansion,
	moreExpansions,
	outputParameters,
	inputParameters,
	idList,
	booleanExpression,
	elsePart,
	var,
	term,
	expPrime,
	lowPrecedenceOperators,
	factor,
	termPrime,
	highPrecedenceOperators,
	logicalOp,
	relationalOp,
	optionalReturn,
	more_ids,
	A
}NonTerminal;

typedef enum{
	TK_ASSIGNOP,
	TK_COMMENT,
	TK_FIELDID,
	TK_ID,
	TK_NUM,
	TK_RNUM,
	TK_FUNID,
	TK_RECORDID,
	TK_WITH,
	TK_PARAMETERS,
	TK_END,
	TK_WHILE,
	TK_TYPE,
	TK_MAIN,
	TK_GLOBAL,
	TK_PARAMETER,
	TK_LIST,
	TK_SQL,
	TK_SQR,
	TK_INPUT,
	TK_OUTPUT,
	TK_INT,
	TK_REAL,
	TK_COMMA,
	TK_SEM,
	TK_COLON,
	TK_DOT,
	TK_ENDWHILE,
	TK_OP,
	TK_CL,
	TK_IF,
	TK_THEN,
	TK_ENDIF,
	TK_READ,
	TK_WRITE,
	TK_RETURN,
	TK_PLUS,
	TK_MINUS,
	TK_MUL,
	TK_DIV,
	TK_CALL,
	TK_RECORD,
	TK_ENDRECORD,
	TK_ELSE,
	TK_AND,
	TK_OR,
	TK_NOT,
	TK_LT,
	TK_LE,
	TK_EQ,
	TK_GT,
	TK_GE,
	TK_NE,
	EPSILON,
	DOLLAR,
	ERROR,
	BOOLEAN,
	LABEL,
	GOTO
}Terminal;

#define sizeOfGrammer 53 //this is the number of grammmar rules in the grammar given by maam.

// we have to put -1 in one of the two in the symbol struct. Symbol can be either a terminal or a non terminal
// struct symbol{
//     NonTerminal nonterminal;
//     Terminal terminal;
// };
// random testing
/*
// typedef struct symbol symbol;
// struct symbol sym;
// sym.nonterminal = (NonTerminal)var;
*/
//this is one list of symbols that will have one grammar rule 
// struct symbol_list{
//     NonTerminal nonterminal;
// 	Terminal terminal;
// 	bool isTerm;
//     struct symbol_list* next;
// };

// struct rules{
//     struct symbol_list* rule_head;
//     struct rules* next;
// };

// struct rule{
//     struct rules* header;
//     int size;
// };

// struct lhs{
// 	NonTerminal nonterminal;
// 	struct rules array[10];
// }
// // struct lhs* lhs_array;
// struct rule** grammar;

typedef struct Rhs{
	char token[50];
	int isNonTerm; // 1 = terminal && 0 = nonterminal 
	int or_no;
	struct Rhs* next;
}rhs;

// typedef struct Rhs_head{
// 	rhs* head;
// 	int size;
// }rhs_head;

typedef struct Lhs{
	char nonterminal[50];
	rhs* rule[10]; // 10 is the maximum or's that we can have in a grammar rule.
	int isEpsilon; // 0 = false && 1 = true
}lhs;

lhs* grammar;
lhs* take_input_from_grammar_file(FILE* ptr);
