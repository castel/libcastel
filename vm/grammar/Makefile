LEX       = lex
YACC      = yacc

MV        = mv
RM        = rm -f

CXXFLAGS += -Wall -Wextra
LDFLAGS  += 

all: grammar

grammar: p9.lex.o p9.yacc.o
	${CXX} ${LDFLAGS} -o grammar p9.lex.o p9.yacc.o

p9.lex.o: p9.lex.c p9.yacc.hh
	${CXX} ${CXXFLAGS} -w -c -o p9.lex.o p9.lex.c

p9.yacc.o: p9.yacc.cc
	${CXX} ${CXXFLAGS} -w -c -o p9.yacc.o p9.yacc.cc

p9.lex.c: p9.lex
	${LEX} p9.lex
	${MV} lex.yy.c p9.lex.c

p9.yacc.cc p9.tab.h: p9.yacc
	${YACC} -d -o p9.yacc.cc p9.yacc

clean:
	${RM} p9.yacc.hh
	${RM} p9.lex.c p9.yacc.cc
	${RM} p9.lex.o p9.yacc.o

fclean: clean
	${RM} grammar

re: fclean all

.PHONY: all clean fclean re

.SUFFIXES:
