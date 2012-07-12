LIBRARY  = libp9.a

CXX      = g++
AR       = ar
RAGEL    = ragel
LEMON    = lemon
MKDIR    = mkdir
MV       = mv
RM       = rm

CXXFLAGS = -g

SRCS     = $(shell find sources -name '*.cc')
OBJS     = $(addprefix build/objects/,$(SRCS:.cc=.o))
DEPS     = $(addprefix build/dependencies/,$(SRCS:.cc=.d))

PURPLE   = $(shell printf "\033[35m")
CYAN     = $(shell printf "\033[36m")
GREEN    = $(shell printf "\033[32m")
BROWN    = $(shell printf "\033[33m")
EOS      = $(shell printf "\033[00m")

CXXFLAGS += -I./includes -I.

all: $(LIBRARY)
	@printf "Compilation done, output is build/${LIBRARY}\n"

$(LIBRARY): build/$(LIBRARY)

-include $(DEPS)

build/$(LIBRARY): $(OBJS)
	@printf "%s# Merging object files.%s\n" "${PURPLE}" "${EOS}"
	@${AR} rcs build/$(LIBRARY) ${OBJS}

build/generated/lexer: sources/lexer/Lexer.rl
	@printf "%s+ Generating ragel p9 lexer.%s\n" "${CYAN}" "${EOS}"
	@${MKDIR} -p "$(dir ${@})"
	@${RAGEL} -C -o build/generated/lexer sources/lexer/Lexer.rl

build/generated/parser: sources/parser/parse.lm
	@printf "%s@ Generating lemon p9 parser.%s\n" "${CYAN}" "${EOS}"
	@${MKDIR} -p "$(dir ${@})"
	@${LEMON} sources/parser/parse.lm
	@${RM} sources/parser/parse.out
	@${RM} sources/parser/parse.h
	@${MV} sources/parser/parse.c build/generated/parser

$(DEPS): build/dependencies/%.d: %.cc
	@printf "%s+ Generating dependency file for %s.%s\n" "${GREEN}" "${<}" "${EOS}"
	@${MKDIR} -p "$(dir ${@})"
	@${CXX} ${CXXFLAGS} -MM -MG -MT "$(patsubst build/dependencies/%,build/objects/%,$(@:.d=.o))" "${<}" > $(@)

$(OBJS): build/objects/%.o: %.cc
	@printf "%s+ Compiling %s.%s\n" "${GREEN}" "${<}" "${EOS}"
	@${MKDIR} -p "$(dir ${@})"
	@${CXX} ${CXXFLAGS} -c -o "${@}" "${<}"

clean:
	@printf "%s- Removing temporary files.%s\n" "${BROWN}" "${EOS}"
	@${RM} -rf build/generated
	@${RM} -rf build/objects

clean-dependencies:
	@printf "%s- Removing dependencies listing.%s\n" "${BROWN}" "${EOS}"
	@${RM} -rf build/dependencies

fclean: clean
	@printf "%s- Removing binary files.%s\n" "${BROWN}" "${EOS}"
	@${RM} -rf build/${LIBRARY}

re: clean-dependencies fclean
	@$(MAKE) --no-print-directory all

.PHONY: $(LIBRARY) all clean fclean re clean-depends libp9
