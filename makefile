compileAll : lookuptable.o twinBuffer.o commentremove.o lexer.o  parsetable.o stack.o grammar_rules_new.o parser.o first_and_follow.o driver.o 
	gcc parsetable.o stack.o grammar_rules_new.o parser.o first_and_follow.o lookuptable.o twinBuffer.o commentremove.o lexer.o driver.o -o stage1exe
twinBuffer.o : twinBuffer.c twinBuffer.h
	gcc -c twinBuffer.c
lookuptable.o : lookuptable.c lookuptable.h
	gcc -c lookuptable.c
commentremove.o : commentremove.c commentremove.h
	gcc -c commentremove.c
lexer.o : lexer.c lexer.h lexerDef.h
	gcc -c  lexer.c
parsetable.o : parsetable.c parsetable.h
	gcc -c parsetable.c
stack.o : stack.c stack.h
	gcc -c stack.c
grammar_rules_new.o : grammar_rules_new.c grammar_def.h
	gcc -c grammar_rules_new.c
parser.o : parser.c parser.h
	gcc -c parser.c
first_and_follow.o : first_and_follow.c first_and_follow.h
	gcc -c first_and_follow.c
driver.o : driver.c 
	gcc -c driver.c

