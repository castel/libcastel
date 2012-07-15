LIBRARY  = libp9.a

CXX      = g++
AR       = ar
RAGEL    = ragel
LEMON    = lemon
MKDIR    = mkdir
MV       = mv
RM       = rm

CXXFLAGS = -g

SRCS     = $(shell (find sources -name '*.cc' ; echo sources/lexer/Lexer.cc) | sort | uniq)
HDRS     = $(shell (find includes -name '*.hh' ; echo includes/p9/lexer/MangledTokens.hh) | sort | uniq)
DEPS     = $(addprefix build/dependencies/,$(SRCS:.cc=.d) $(HDRS:.hh=.d))
OBJS     = $(addprefix build/objects/,$(SRCS:.cc=.o))

PURPLE   = $(shell printf "\033[35m")
CYAN     = $(shell printf "\033[36m")
GREEN    = $(shell printf "\033[32m")
BROWN    = $(shell printf "\033[33m")
EOS      = $(shell printf "\033[00m")

CXXFLAGS += -std=c++11 -I./includes -I.

all: $(LIBRARY)
	@printf "Compilation done, output is build/${LIBRARY}\n"

$(LIBRARY): build/$(LIBRARY)

-include $(DEPS)

build/$(LIBRARY): $(OBJS) includes/p9/lexer/MangledTokens.hh
	@printf "%s# Merging object files.%s\n" "${PURPLE}" "${EOS}"
	@${AR} rcs build/$(LIBRARY) ${OBJS}

sources/lexer/Lexer.cc: sources/lexer/Lexer.rl
	@printf "%s+ Generating ragel p9 lexer.%s\n" "${CYAN}" "${EOS}"
	@${RAGEL} -C -o sources/lexer/Lexer.cc sources/lexer/Lexer.rl

includes/p9/lexer/MangledTokens.hh sources/parser/parse.cc: sources/parser/parse.lm
	@printf "%s@ Generating lemon p9 parser.%s\n" "${CYAN}" "${EOS}"
	@${LEMON} sources/parser/parse.lm
	@${RM} sources/parser/parse.out
	@${MV} sources/parser/parse.h includes/p9/lexer/MangledTokens.hh
	@${MV} sources/parser/parse.c sources/parser/parse.cc

$(DEPS): build/dependencies/%.d: %.cc | includes/p9/lexer/MangledTokens.hh sources/parser/parse.cc
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
