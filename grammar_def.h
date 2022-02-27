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
#define sizeOfGrammer 45 //this is the number of grammmar rules in the grammar given by maam.

// we have to put -1 in one of the two in the symbol struct. Symbol can be either a terminal or a non terminal
struct symbol{
    NonTerminal nonterminal;
    Terminal terminal;
};
// random testing
/*
// typedef struct symbol symbol;
// struct symbol sym;
// sym.nonterminal = (NonTerminal)var;
*/

struct symbol_list{
    struct symbol sym;
    struct symbol_list* next;
    bool isTerm;
};

struct symbol_list_head{
    struct symbol_list* head;
    int size;
};

struct rules{
    struct symbol_list_head* rule_head;
    struct rules* next;
};

struct rule{
    struct rules* header;
    int size;
};
struct rule* grammar[sizeOfGrammer];