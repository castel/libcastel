RAGEL  := ragel
LEMON  := lemon
CXX    := g++
MKDIR  := mkdir
AR     := ar
MV     := mv

SRCS   := $(shell find ./sources/ -name '*.cc') ./sources/lexer/Lexer.cc
OBJS   := $(addprefix ./build/o/,$(SRCS:.cc=.o))
DEPS   := $(addprefix ./build/d/,$(SRCS:.cc=.d))

purple := $(shell printf "\033[35m")
cyan   := $(shell printf "\033[36m")
green  := $(shell printf "\033[32m")
brown  := $(shell printf "\033[33m")
end    := $(shell printf "\033[00m")

SRCS   := $(sort $(SRCS))
OBJS   := $(sort $(OBJS))
DEPS   := $(sort $(DEPS))

all: ./build/libp9.a

-include $(DEPS)

./build/libp9.a: ${OBJS}
	@printf "%s# Merging object files.%s\n" "${purple}" "${end}"
	@${AR} rcs ./build/libp9.a ${OBJS}

./sources/lexer/Lexer.cc: ./sources/lexer/Lexer.rl
	@printf "%s@ Generating ragel p9 lexer.%s\n" "${cyan}" "${end}"
	@${RAGEL} -C -o ./sources/lexer/Lexer.cc ./sources/lexer/Lexer.rl

./includes/p9/lexer/LexemeTypes.hh ./sources/parser/parse.cc: ./sources/parser/parse.lm
	@printf "%s@ Generation lemon p9 parser.%s\n" "${cyan}" "${end}"
	@${LEMON} ./sources/parser/parse.lm
	@${RM} ./sources/parser/parse.out
	@${MV} ./sources/parser/parse.c ./sources/parser/parse.cc
	@${MV} ./sources/parser/parse.h ./includes/p9/lexer/LexemeTypes.hh

$(DEPS): ./build/d/%.d: %.cc
	@printf "%s+ Generating dependency file for %s.%s\n" "${green}" "${<}" "${end}"
	@${MKDIR} -p "$(dir ${@})"
	@${CXX} -I. -Iincludes/ -MM -MG -MT "$(patsubst build/d/%,build/o/%,$(@:.d=.o))" "${<}" > $(@)

$(OBJS): ./build/o/%.o: %.cc ./build/d/%.d
	@printf "%s+ Compiling %s.%s\n" "${green}" "${<}" "${end}"
	@${MKDIR} -p "$(dir ${@})"
	@${CXX} ${CXXFLAGS} -I. -I./includes/ -c -o "${@}" "${<}"

clean:
	@printf "%s- Removing object files.%s\n" "${brown}" "${end}"
	@${RM} -rf ./build/o/

fclean: clean
	@printf "%s- Removing binary files.%s\n" "${brown}" "${end}"
	@${RM} -rf ./build/libmy.a

re: fclean all

clean-depends:
	@printf "%s- Removing dependency files.%s\n" "${brown}" "${end}"
	@${RM} -rf ./build/d/

.PHONY: all clean fclean re clean-depends
