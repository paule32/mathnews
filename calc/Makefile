default:
	bison -d p1.ypp
	flex p1.lpp
	g++ -o libparser.so -shared -fPIC p1.tab.cpp lex.yy.c
	g++ -o calc.o -O2 -c calc.cc
	g++ -o calc calc.o -L. -lparser

#	g++ -o calc p1.tab.cpp lex.yy.c
