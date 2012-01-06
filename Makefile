RAGEL = ragel
CXX   = g++
MKDIR = mkdir
AR    = ar
MV    = mv

purple = $(shell printf "\033[35m")
cyan   = $(shell printf "\033[36m")
green  = $(shell printf "\033[32m")
brown  = $(shell printf "\033[33m")
end    = $(shell printf "\033[00m")

all: ./binaries/libp9.a

./binaries/libp9.a: ./binaries/o/lexer/Lexer.o ./binaries/o/parser/Parser.o
	@printf "%s# Merging object files.%s\n" "${purple}" "${end}"
	@${AR} rcs binaries/libp9.a ${^}

./binaries/o/lexer/Lexer.cc: ./sources/lexer/Lexer.rl
	@printf "%s@ Generating ragel p9 lexer.%s\n" "${cyan}" "${end}"
	@${MKDIR} -p ./binaries/o/lexer/
	@${RAGEL} -C -o ./binaries/o/lexer/Lexer.cc ./sources/lexer/Lexer.rl

./binaries/o/lexer/Lexer.o: ./binaries/o/lexer/Lexer.cc ./includes/p9/lexer/TokenDefinitions.hh
	@printf "%s+ Compiling p9 lexer.%s\n" "${green}" "${end}"
	@${MKDIR} -p ./binaries/o/lexer/
	@${CXX} ${CXXFLAGS} -I./includes/ -c -o ./binaries/o/lexer/Lexer.o ./binaries/o/lexer/Lexer.cc

./includes/p9/lexer/TokenDefinitions.hh ./binaries/o/parser/parse.c: ./binaries/lemon ./sources/parser/parse.lm
	@printf "%s@ Generation lemon p9 parser.%s\n" "${cyan}" "${end}"
	@./binaries/lemon -T./tools/lempar.c ./sources/parser/parse.lm
	@${MKDIR} -p ./binaries/o/parser/
	@${RM} ./sources/parser/parse.out
	@${MV} ./sources/parser/parse.c ./binaries/o/parser/parse.c
	@${MV} ./sources/parser/parse.h ./includes/p9/lexer/TokenDefinitions.hh

./binaries/o/parser/Parser.o: ./sources/parser/Parser.cc ./binaries/o/parser/parse.c
	@printf "%s+ Compiling p9 parser.%s\n" "${green}" "${end}"
	@${MKDIR} -p ./binaries/o/parser/
	@${CXX} ${CXXFLAGS} -I./includes/ -include ./binaries/o/parser/parse.c -c -o ./binaries/o/parser/Parser.o ./sources/parser/Parser.cc

./binaries/lemon: ./tools/lemon.c
	@printf "%s# Compiling lemon.%s\n" "${purple}" "${end}"
	@${CC} -o ./binaries/lemon ./tools/lemon.c

clean:
	@printf "%s- Removing object files.%s\n" "${brown}" "${end}"
	@${RM} -rf ./binaries/o/

fclean: clean
	@printf "%s- Removing binary files.%s\n" "${brown}" "${end}"
	@${RM} -rf ./binaries/*

re: fclean all
