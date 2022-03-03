compileAll : lookuptable.o twinBuffer.o commentremove.o lexer.o driver.o
	gcc lookuptable.o twinBuffer.o commentremove.o lexer.o driver.o -o stage1exe
twinBuffer.o : twinBuffer.c twinBuffer.h
	gcc -c twinBuffer.c
lookuptable.o : lookuptable.c lookuptable.h
	gcc -c lookuptable.c
commentremove.o : commentremove.c commentremove.h
	gcc -c commentremove.c
lexer.o : lexer.c lexer.h lexerDef.h
	gcc -c  lexer.c
driver.o : driver.c 
	gcc -c driver.c

