/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 12 "sources/parser/parse.lm"


    #include <cassert>

    #include "castel/ast/expr/Boolean.hh"
    #include "castel/ast/expr/Binary.hh"
    #include "castel/ast/expr/Call.hh"
    #include "castel/ast/expr/Function.hh"
    #include "castel/ast/expr/Null.hh"
    #include "castel/ast/expr/Number.hh"
    #include "castel/ast/expr/Undefined.hh"
    #include "castel/ast/expr/Variable.hh"
    #include "castel/ast/stmt/decl/Variables.hh"
    #include "castel/ast/stmt/Expression.hh"
    #include "castel/ast/stmt/If.hh"
    #include "castel/ast/stmt/Return.hh"
    #include "castel/ast/Expression.hh"
    #include "castel/ast/Statement.hh"
    #include "castel/lexer/Lexeme.hh"

    using namespace castel;

    static bool castelparserIsValid;
    static ast::Statement * castelparserRootStatement;

#line 34 "sources/parser/parse.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 65
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE  lexer::Lexeme *     
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  ast::expr::Boolean * yy6;
  ast::expr::Variable * yy20;
  ast::expr::Unary * yy21;
  ast::stmt::Return * yy23;
  ast::expr::Multary * yy24;
  ast::stmt::If * yy26;
  ast::stmt::decl::Variables * yy36;
  ast::expr::Null * yy45;
  void * yy49;
  ast::expr::Multary::Operand * yy57;
  ast::stmt::Expression * yy63;
  ast::Expression * yy83;
  ast::Statement * yy84;
  ast::expr::Undefined * yy85;
  ast::expr::Number * yy91;
  ast::stmt::decl::Variables::Variable * yy98;
  ast::expr::Function * yy108;
  ast::expr::Function::Parameter * yy125;
  ast::expr::Binary * yy127;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 109
#define YYNRULE 66
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (626)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    11,   16,   15,   14,   13,   12,   24,   22,   20,   18,
 /*    10 */    17,    4,    3,  109,  102,  176,   68,   34,    2,   69,
 /*    20 */     1,  108,    1,   67,   84,  101,  100,   11,   16,   15,
 /*    30 */    14,   13,   12,   24,   22,   20,   18,   17,    4,    3,
 /*    40 */    66,   86,    2,   61,   60,   85,    5,   33,   71,   60,
 /*    50 */    78,   75,  101,  100,   11,   16,   15,   14,   13,   12,
 /*    60 */    24,   22,   20,   18,   17,    4,    3,   72,   25,    9,
 /*    70 */    57,  107,   35,   31,   65,   27,   64,   83,   58,  101,
 /*    80 */   100,   87,   11,   16,   15,   14,   13,   12,   24,   22,
 /*    90 */    20,   18,   17,    4,    3,   59,   73,  177,   70,  177,
 /*   100 */   177,  177,  177,  177,  177,  177,  177,  101,  100,   11,
 /*   110 */    16,   15,   14,   13,   12,   24,   22,   20,   18,   17,
 /*   120 */     4,    3,  177,  177,   24,   22,   20,   18,   17,    4,
 /*   130 */     3,  177,   32,  177,  101,  100,   30,  177,  106,  105,
 /*   140 */   104,  103,   40,  101,  100,   99,   98,   97,   96,   95,
 /*   150 */    94,   93,   92,   91,   90,   29,  177,  106,  105,  104,
 /*   160 */   103,   40,  177,  177,   99,   98,   97,   96,   95,   94,
 /*   170 */    93,   92,   91,   90,   11,   16,   15,   14,   13,   12,
 /*   180 */    24,   22,   20,   18,   17,    4,    3,  177,  177,  177,
 /*   190 */    23,   21,  177,    4,    3,    7,  177,  177,  177,  101,
 /*   200 */   100,    6,   26,  177,   79,  177,    8,  101,  100,   19,
 /*   210 */    10,  177,  177,   89,   88,  177,   82,   81,   80,   39,
 /*   220 */   177,  177,   99,   98,   97,   96,   95,   94,   93,   92,
 /*   230 */    91,   90,   62,   77,   39,  177,  177,   99,   98,   97,
 /*   240 */    96,   95,   94,   93,   92,   91,   90,   63,   77,   23,
 /*   250 */    21,  177,  177,  177,    7,  177,  177,  177,  177,  177,
 /*   260 */   177,  177,  177,   79,  177,  177,  177,  177,   19,   10,
 /*   270 */   177,  177,   89,   88,   28,   82,   81,   80,  177,  177,
 /*   280 */    23,   21,  177,  177,  177,    7,  177,  177,   74,  177,
 /*   290 */   177,  177,  177,  177,   79,  177,  177,  177,  177,   19,
 /*   300 */    10,  177,  177,   89,   88,  177,   82,   81,   80,  177,
 /*   310 */   177,   39,  177,  177,   99,   98,   97,   96,   95,   94,
 /*   320 */    93,   92,   91,   90,   50,   76,  177,   99,   98,   97,
 /*   330 */    96,   95,   94,   93,   92,   91,   90,   23,   21,  177,
 /*   340 */   177,  177,    7,  177,  177,  177,  177,  177,  177,  177,
 /*   350 */   177,   79,  177,  177,  177,  177,   19,   10,  177,  177,
 /*   360 */    89,   88,  177,   82,   81,   80,   53,  177,  177,   99,
 /*   370 */    98,   97,   96,   95,   94,   93,   92,   91,   90,   51,
 /*   380 */   177,  177,   99,   98,   97,   96,   95,   94,   93,   92,
 /*   390 */    91,   90,  177,  177,  177,  177,  177,  177,  177,   52,
 /*   400 */   177,  177,   99,   98,   97,   96,   95,   94,   93,   92,
 /*   410 */    91,   90,   54,  177,  177,   99,   98,   97,   96,   95,
 /*   420 */    94,   93,   92,   91,   90,   43,  177,  177,   99,   98,
 /*   430 */    97,   96,   95,   94,   93,   92,   91,   90,   56,  177,
 /*   440 */   177,   99,   98,   97,   96,   95,   94,   93,   92,   91,
 /*   450 */    90,   55,  177,  177,   99,   98,   97,   96,   95,   94,
 /*   460 */    93,   92,   91,   90,   49,  177,  177,   99,   98,   97,
 /*   470 */    96,   95,   94,   93,   92,   91,   90,   48,  177,  177,
 /*   480 */    99,   98,   97,   96,   95,   94,   93,   92,   91,   90,
 /*   490 */    47,  177,  177,   99,   98,   97,   96,   95,   94,   93,
 /*   500 */    92,   91,   90,   46,  177,  177,   99,   98,   97,   96,
 /*   510 */    95,   94,   93,   92,   91,   90,   45,  177,  177,   99,
 /*   520 */    98,   97,   96,   95,   94,   93,   92,   91,   90,   44,
 /*   530 */   177,  177,   99,   98,   97,   96,   95,   94,   93,   92,
 /*   540 */    91,   90,   42,  177,  177,   99,   98,   97,   96,   95,
 /*   550 */    94,   93,   92,   91,   90,   41,  177,  177,   99,   98,
 /*   560 */    97,   96,   95,   94,   93,   92,   91,   90,   36,  177,
 /*   570 */   177,   99,   98,   97,   96,   95,   94,   93,   92,   91,
 /*   580 */    90,   38,  177,  177,   99,   98,   97,   96,   95,   94,
 /*   590 */    93,   92,   91,   90,   37,  177,  177,   99,   98,   97,
 /*   600 */    96,   95,   94,   93,   92,   91,   90,   20,   18,   17,
 /*   610 */     4,    3,  177,  177,  177,  177,  177,  177,  177,  177,
 /*   620 */   177,  177,  177,  177,  101,  100,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,    0,   15,   37,   38,   24,   40,   39,
 /*    20 */    40,   39,   40,   62,   63,   26,   27,    1,    2,    3,
 /*    30 */     4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*    40 */    38,   17,   40,   48,   49,   28,   20,   20,   48,   49,
 /*    50 */    29,   28,   26,   27,    1,    2,    3,    4,    5,    6,
 /*    60 */     7,    8,    9,   10,   11,   12,   13,   15,   20,   22,
 /*    70 */    25,   40,   15,   24,   42,   16,   21,   63,   42,   26,
 /*    80 */    27,   28,    1,    2,    3,    4,    5,    6,    7,    8,
 /*    90 */     9,   10,   11,   12,   13,   21,   15,   64,   42,   64,
 /*   100 */    64,   64,   64,   64,   64,   64,   64,   26,   27,    1,
 /*   110 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   120 */    12,   13,   64,   64,    7,    8,    9,   10,   11,   12,
 /*   130 */    13,   64,   24,   64,   26,   27,   41,   64,   43,   44,
 /*   140 */    45,   46,   47,   26,   27,   50,   51,   52,   53,   54,
 /*   150 */    55,   56,   57,   58,   59,   41,   64,   43,   44,   45,
 /*   160 */    46,   47,   64,   64,   50,   51,   52,   53,   54,   55,
 /*   170 */    56,   57,   58,   59,    1,    2,    3,    4,    5,    6,
 /*   180 */     7,    8,    9,   10,   11,   12,   13,   64,   64,   64,
 /*   190 */     7,    8,   64,   12,   13,   12,   64,   64,   64,   26,
 /*   200 */    27,   18,   19,   64,   21,   64,   23,   26,   27,   26,
 /*   210 */    27,   64,   64,   30,   31,   64,   33,   34,   35,   47,
 /*   220 */    64,   64,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   230 */    58,   59,   60,   61,   47,   64,   64,   50,   51,   52,
 /*   240 */    53,   54,   55,   56,   57,   58,   59,   60,   61,    7,
 /*   250 */     8,   64,   64,   64,   12,   64,   64,   64,   64,   64,
 /*   260 */    64,   64,   64,   21,   64,   64,   64,   64,   26,   27,
 /*   270 */    64,   64,   30,   31,   32,   33,   34,   35,   64,   64,
 /*   280 */     7,    8,   64,   64,   64,   12,   64,   64,   15,   64,
 /*   290 */    64,   64,   64,   64,   21,   64,   64,   64,   64,   26,
 /*   300 */    27,   64,   64,   30,   31,   64,   33,   34,   35,   64,
 /*   310 */    64,   47,   64,   64,   50,   51,   52,   53,   54,   55,
 /*   320 */    56,   57,   58,   59,   47,   61,   64,   50,   51,   52,
 /*   330 */    53,   54,   55,   56,   57,   58,   59,    7,    8,   64,
 /*   340 */    64,   64,   12,   64,   64,   64,   64,   64,   64,   64,
 /*   350 */    64,   21,   64,   64,   64,   64,   26,   27,   64,   64,
 /*   360 */    30,   31,   64,   33,   34,   35,   47,   64,   64,   50,
 /*   370 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   47,
 /*   380 */    64,   64,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   390 */    58,   59,   64,   64,   64,   64,   64,   64,   64,   47,
 /*   400 */    64,   64,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   410 */    58,   59,   47,   64,   64,   50,   51,   52,   53,   54,
 /*   420 */    55,   56,   57,   58,   59,   47,   64,   64,   50,   51,
 /*   430 */    52,   53,   54,   55,   56,   57,   58,   59,   47,   64,
 /*   440 */    64,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   450 */    59,   47,   64,   64,   50,   51,   52,   53,   54,   55,
 /*   460 */    56,   57,   58,   59,   47,   64,   64,   50,   51,   52,
 /*   470 */    53,   54,   55,   56,   57,   58,   59,   47,   64,   64,
 /*   480 */    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
 /*   490 */    47,   64,   64,   50,   51,   52,   53,   54,   55,   56,
 /*   500 */    57,   58,   59,   47,   64,   64,   50,   51,   52,   53,
 /*   510 */    54,   55,   56,   57,   58,   59,   47,   64,   64,   50,
 /*   520 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   47,
 /*   530 */    64,   64,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   540 */    58,   59,   47,   64,   64,   50,   51,   52,   53,   54,
 /*   550 */    55,   56,   57,   58,   59,   47,   64,   64,   50,   51,
 /*   560 */    52,   53,   54,   55,   56,   57,   58,   59,   47,   64,
 /*   570 */    64,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   580 */    59,   47,   64,   64,   50,   51,   52,   53,   54,   55,
 /*   590 */    56,   57,   58,   59,   47,   64,   64,   50,   51,   52,
 /*   600 */    53,   54,   55,   56,   57,   58,   59,    9,   10,   11,
 /*   610 */    12,   13,   64,   64,   64,   64,   64,   64,   64,   64,
 /*   620 */    64,   64,   64,   64,   26,   27,
};
#define YY_SHIFT_USE_DFLT (-8)
#define YY_SHIFT_COUNT (68)
#define YY_SHIFT_MIN   (-7)
#define YY_SHIFT_MAX   (598)
static const short yy_shift_ofst[] = {
 /*     0 */    57,  183,  183,  330,  330,  330,  273,  242,  330,  330,
 /*    10 */   330,  330,  330,  330,  330,  330,  330,  330,  330,  330,
 /*    20 */   330,  330,  330,  330,  330,   74,   74,   57,   55,   57,
 /*    30 */    57,   59,   59,   55,   59,   57,  108,   81,   53,   26,
 /*    40 */    -1,  173,  173,  173,  117,  117,  117,  117,  117,  117,
 /*    50 */   598,  598,  598,  598,  181,  181,  181,   49,   45,   47,
 /*    60 */    48,   52,   23,   21,   27,   17,   24,   -7,   13,
};
#define YY_REDUCE_USE_DFLT (-40)
#define YY_REDUCE_COUNT (35)
#define YY_REDUCE_MIN   (-39)
#define YY_REDUCE_MAX   (547)
static const short yy_reduce_ofst[] = {
 /*     0 */   -22,  114,   95,  187,  172,  264,  547,  534,  521,  508,
 /*    10 */   495,  482,  469,  456,  443,  430,  417,  404,  391,  378,
 /*    20 */   365,  352,  332,  319,  277,    0,   -5,    2,  -39,  -18,
 /*    30 */   -20,   56,   36,   14,   32,   31,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   114,  111,  175,  160,  160,  175,  175,  175,  175,  175,
 /*    10 */   175,  175,  175,  175,  175,  175,  175,  175,  175,  175,
 /*    20 */   175,  175,  175,  175,  175,  175,  175,  114,  172,  114,
 /*    30 */   114,  175,  175,  175,  175,  114,  175,  175,  175,  162,
 /*    40 */   175,  127,  144,  142,  156,  155,  154,  153,  152,  151,
 /*    50 */   146,  147,  141,  140,  148,  150,  149,  175,  129,  126,
 /*    60 */   125,  175,  175,  175,  174,  175,  175,  175,  175,  112,
 /*    70 */   128,  124,  123,  122,  121,  157,  161,  159,  158,  169,
 /*    80 */   168,  167,  166,  173,  171,  165,  115,  170,  164,  163,
 /*    90 */   139,  138,  137,  136,  135,  134,  133,  132,  131,  130,
 /*   100 */   145,  143,  120,  119,  118,  117,  116,  113,  110,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "Assignment",    "AdditionAssignment",  "SubstractionAssignment",
  "MultiplicationAssignment",  "DivisionAssignment",  "ModuloAssignment",  "PositiveAddition",
  "NegativeSubstraction",  "Multiplication",  "Division",      "Modulo",      
  "LParenthesis",  "LBracket",      "Spaces",        "Newline",     
  "Indent",        "Dedent",        "Return",        "Var",         
  "Comma",         "Identifier",    "Assign",        "If",          
  "Colon",         "Else",          "Incrementation",  "Decrementation",
  "RParenthesis",  "RBracket",      "False",         "True",        
  "Function",      "Null",          "Number",        "Undefined",   
  "error",         "program",       "statements",    "statementlist",
  "emptystatementlist",  "statement",     "statementblock",  "expressionstatement",
  "returnstatement",  "variabledeclarationstatement",  "ifstatement",   "expression",  
  "variabledeclarations",  "variabledeclaration",  "unaryexpression",  "binaryexpression",
  "multaryexpression",  "booleanexpression",  "functionexpression",  "nullexpression",
  "numberexpression",  "undefinedexpression",  "variableexpression",  "parenthesisexpression",
  "multaryoperands",  "multaryoperandslist",  "parameters",    "parameterlist",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= statements",
 /*   1 */ "statementlist ::= emptystatementlist statement statementlist",
 /*   2 */ "statementlist ::= emptystatementlist",
 /*   3 */ "statements ::= emptystatementlist statement statementlist",
 /*   4 */ "emptystatementlist ::= Newline emptystatementlist",
 /*   5 */ "emptystatementlist ::=",
 /*   6 */ "statementblock ::= Indent statements Dedent",
 /*   7 */ "statement ::= expressionstatement",
 /*   8 */ "statement ::= returnstatement",
 /*   9 */ "statement ::= variabledeclarationstatement",
 /*  10 */ "statement ::= ifstatement",
 /*  11 */ "expressionstatement ::= expression Newline",
 /*  12 */ "returnstatement ::= Return Newline",
 /*  13 */ "returnstatement ::= Return expression Newline",
 /*  14 */ "variabledeclarationstatement ::= Var variabledeclarations Newline",
 /*  15 */ "variabledeclarations ::= variabledeclaration Comma variabledeclarations",
 /*  16 */ "variabledeclarations ::= variabledeclaration",
 /*  17 */ "variabledeclaration ::= Identifier",
 /*  18 */ "variabledeclaration ::= Identifier Assign expression",
 /*  19 */ "ifstatement ::= If expression Colon statementblock Else Colon statementblock",
 /*  20 */ "ifstatement ::= If expression Colon statementblock",
 /*  21 */ "expression ::= unaryexpression",
 /*  22 */ "expression ::= binaryexpression",
 /*  23 */ "expression ::= multaryexpression",
 /*  24 */ "expression ::= booleanexpression",
 /*  25 */ "expression ::= functionexpression",
 /*  26 */ "expression ::= nullexpression",
 /*  27 */ "expression ::= numberexpression",
 /*  28 */ "expression ::= undefinedexpression",
 /*  29 */ "expression ::= variableexpression",
 /*  30 */ "expression ::= parenthesisexpression",
 /*  31 */ "unaryexpression ::= PositiveAddition expression",
 /*  32 */ "unaryexpression ::= NegativeSubstraction expression",
 /*  33 */ "unaryexpression ::= Incrementation expression",
 /*  34 */ "unaryexpression ::= expression Incrementation",
 /*  35 */ "unaryexpression ::= Decrementation expression",
 /*  36 */ "unaryexpression ::= expression Decrementation",
 /*  37 */ "binaryexpression ::= expression PositiveAddition expression",
 /*  38 */ "binaryexpression ::= expression NegativeSubstraction expression",
 /*  39 */ "binaryexpression ::= expression Multiplication expression",
 /*  40 */ "binaryexpression ::= expression Division expression",
 /*  41 */ "binaryexpression ::= expression Modulo expression",
 /*  42 */ "binaryexpression ::= expression AdditionAssignment expression",
 /*  43 */ "binaryexpression ::= expression SubstractionAssignment expression",
 /*  44 */ "binaryexpression ::= expression MultiplicationAssignment expression",
 /*  45 */ "binaryexpression ::= expression DivisionAssignment expression",
 /*  46 */ "binaryexpression ::= expression ModuloAssignment expression",
 /*  47 */ "binaryexpression ::= expression Assignment expression",
 /*  48 */ "multaryexpression ::= expression LParenthesis multaryoperands RParenthesis",
 /*  49 */ "multaryexpression ::= expression LBracket multaryoperands RBracket",
 /*  50 */ "multaryoperands ::= multaryoperandslist",
 /*  51 */ "multaryoperands ::=",
 /*  52 */ "multaryoperandslist ::= expression Comma multaryoperandslist",
 /*  53 */ "multaryoperandslist ::= expression",
 /*  54 */ "booleanexpression ::= False",
 /*  55 */ "booleanexpression ::= True",
 /*  56 */ "functionexpression ::= LParenthesis Function parameters Colon statementblock RParenthesis",
 /*  57 */ "nullexpression ::= Null",
 /*  58 */ "numberexpression ::= Number",
 /*  59 */ "undefinedexpression ::= Undefined",
 /*  60 */ "variableexpression ::= Identifier",
 /*  61 */ "parenthesisexpression ::= LParenthesis expression RParenthesis",
 /*  62 */ "parameters ::= parameterlist",
 /*  63 */ "parameters ::=",
 /*  64 */ "parameterlist ::= Identifier Comma parameterlist",
 /*  65 */ "parameterlist ::= Identifier",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 37, 1 },
  { 39, 3 },
  { 39, 1 },
  { 38, 3 },
  { 40, 2 },
  { 40, 0 },
  { 42, 3 },
  { 41, 1 },
  { 41, 1 },
  { 41, 1 },
  { 41, 1 },
  { 43, 2 },
  { 44, 2 },
  { 44, 3 },
  { 45, 3 },
  { 48, 3 },
  { 48, 1 },
  { 49, 1 },
  { 49, 3 },
  { 46, 7 },
  { 46, 4 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 50, 2 },
  { 50, 2 },
  { 50, 2 },
  { 50, 2 },
  { 50, 2 },
  { 50, 2 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 52, 4 },
  { 52, 4 },
  { 60, 1 },
  { 60, 0 },
  { 61, 3 },
  { 61, 1 },
  { 53, 1 },
  { 53, 1 },
  { 54, 6 },
  { 55, 1 },
  { 56, 1 },
  { 57, 1 },
  { 58, 1 },
  { 59, 3 },
  { 62, 1 },
  { 62, 0 },
  { 63, 3 },
  { 63, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* program ::= statements */
#line 44 "sources/parser/parse.lm"
{ castelparserRootStatement = yymsp[0].minor.yy84; }
#line 971 "sources/parser/parse.c"
        break;
      case 1: /* statementlist ::= emptystatementlist statement statementlist */
#line 47 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[-1].minor.yy84; yymsp[-1].minor.yy84->next( yymsp[0].minor.yy84 ); }
#line 976 "sources/parser/parse.c"
        break;
      case 2: /* statementlist ::= emptystatementlist */
#line 48 "sources/parser/parse.lm"
{ yygotominor.yy84 = nullptr;         }
#line 981 "sources/parser/parse.c"
        break;
      case 3: /* statements ::= emptystatementlist statement statementlist */
#line 51 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[-1].minor.yy84; yygotominor.yy84->next( yymsp[0].minor.yy84 ); }
#line 986 "sources/parser/parse.c"
        break;
      case 4: /* emptystatementlist ::= Newline emptystatementlist */
      case 5: /* emptystatementlist ::= */ yytestcase(yyruleno==5);
#line 54 "sources/parser/parse.lm"
{ /* no action */ }
#line 992 "sources/parser/parse.c"
        break;
      case 6: /* statementblock ::= Indent statements Dedent */
#line 58 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[-1].minor.yy84;           }
#line 997 "sources/parser/parse.c"
        break;
      case 7: /* statement ::= expressionstatement */
#line 61 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[0].minor.yy63;           }
#line 1002 "sources/parser/parse.c"
        break;
      case 8: /* statement ::= returnstatement */
#line 62 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[0].minor.yy23;           }
#line 1007 "sources/parser/parse.c"
        break;
      case 9: /* statement ::= variabledeclarationstatement */
#line 63 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[0].minor.yy36;           }
#line 1012 "sources/parser/parse.c"
        break;
      case 10: /* statement ::= ifstatement */
#line 64 "sources/parser/parse.lm"
{ yygotominor.yy84 = yymsp[0].minor.yy26;           }
#line 1017 "sources/parser/parse.c"
        break;
      case 11: /* expressionstatement ::= expression Newline */
#line 67 "sources/parser/parse.lm"
{ yygotominor.yy63 = new ast::stmt::Expression( yymsp[-1].minor.yy83 ); }
#line 1022 "sources/parser/parse.c"
        break;
      case 12: /* returnstatement ::= Return Newline */
#line 70 "sources/parser/parse.lm"
{ yygotominor.yy23 = new ast::stmt::Return( );   }
#line 1027 "sources/parser/parse.c"
        break;
      case 13: /* returnstatement ::= Return expression Newline */
#line 71 "sources/parser/parse.lm"
{ yygotominor.yy23 = new ast::stmt::Return( yymsp[-1].minor.yy83 ); }
#line 1032 "sources/parser/parse.c"
        break;
      case 14: /* variabledeclarationstatement ::= Var variabledeclarations Newline */
#line 74 "sources/parser/parse.lm"
{ yygotominor.yy36 = new ast::stmt::decl::Variables( yymsp[-1].minor.yy98 ); }
#line 1037 "sources/parser/parse.c"
        break;
      case 15: /* variabledeclarations ::= variabledeclaration Comma variabledeclarations */
#line 77 "sources/parser/parse.lm"
{ yygotominor.yy98 = yymsp[-2].minor.yy98; yymsp[-2].minor.yy98->next( yymsp[0].minor.yy98 );                   }
#line 1042 "sources/parser/parse.c"
        break;
      case 16: /* variabledeclarations ::= variabledeclaration */
#line 78 "sources/parser/parse.lm"
{ yygotominor.yy98 = yymsp[0].minor.yy98;                                 }
#line 1047 "sources/parser/parse.c"
        break;
      case 17: /* variabledeclaration ::= Identifier */
#line 81 "sources/parser/parse.lm"
{ yygotominor.yy98 = new ast::stmt::decl::Variables::Variable( *yymsp[0].minor.yy0 );     }
#line 1052 "sources/parser/parse.c"
        break;
      case 18: /* variabledeclaration ::= Identifier Assign expression */
#line 82 "sources/parser/parse.lm"
{ yygotominor.yy98 = new ast::stmt::decl::Variables::Variable( *yymsp[-2].minor.yy0, yymsp[0].minor.yy83 ); }
#line 1057 "sources/parser/parse.c"
        break;
      case 19: /* ifstatement ::= If expression Colon statementblock Else Colon statementblock */
#line 85 "sources/parser/parse.lm"
{ yygotominor.yy26 = new ast::stmt::If( yymsp[-5].minor.yy83, yymsp[-3].minor.yy84, yymsp[0].minor.yy84 ); }
#line 1062 "sources/parser/parse.c"
        break;
      case 20: /* ifstatement ::= If expression Colon statementblock */
#line 86 "sources/parser/parse.lm"
{ yygotominor.yy26 = new ast::stmt::If( yymsp[-2].minor.yy83, yymsp[0].minor.yy84 );    }
#line 1067 "sources/parser/parse.c"
        break;
      case 21: /* expression ::= unaryexpression */
#line 89 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy21;            }
#line 1072 "sources/parser/parse.c"
        break;
      case 22: /* expression ::= binaryexpression */
#line 90 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy127;            }
#line 1077 "sources/parser/parse.c"
        break;
      case 23: /* expression ::= multaryexpression */
#line 91 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy24;            }
#line 1082 "sources/parser/parse.c"
        break;
      case 24: /* expression ::= booleanexpression */
#line 93 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy6;            }
#line 1087 "sources/parser/parse.c"
        break;
      case 25: /* expression ::= functionexpression */
#line 94 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy108;            }
#line 1092 "sources/parser/parse.c"
        break;
      case 26: /* expression ::= nullexpression */
#line 95 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy45;            }
#line 1097 "sources/parser/parse.c"
        break;
      case 27: /* expression ::= numberexpression */
#line 96 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy91;            }
#line 1102 "sources/parser/parse.c"
        break;
      case 28: /* expression ::= undefinedexpression */
#line 97 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy85;            }
#line 1107 "sources/parser/parse.c"
        break;
      case 29: /* expression ::= variableexpression */
#line 99 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy20;            }
#line 1112 "sources/parser/parse.c"
        break;
      case 30: /* expression ::= parenthesisexpression */
#line 101 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[0].minor.yy83;            }
#line 1117 "sources/parser/parse.c"
        break;
      case 31: /* unaryexpression ::= PositiveAddition expression */
#line 104 "sources/parser/parse.lm"
{ yygotominor.yy21 = new ast::expr::Unary( lexer::Lexeme::Type::Positive, yymsp[0].minor.yy83 );           }
#line 1122 "sources/parser/parse.c"
        break;
      case 32: /* unaryexpression ::= NegativeSubstraction expression */
#line 105 "sources/parser/parse.lm"
{ yygotominor.yy21 = new ast::expr::Unary( lexer::Lexeme::Type::Negative, yymsp[0].minor.yy83 );           }
#line 1127 "sources/parser/parse.c"
        break;
      case 33: /* unaryexpression ::= Incrementation expression */
#line 107 "sources/parser/parse.lm"
{ yygotominor.yy21 = new ast::expr::Unary( lexer::Lexeme::Type::PreIncrementation, yymsp[0].minor.yy83 );  }
#line 1132 "sources/parser/parse.c"
        break;
      case 34: /* unaryexpression ::= expression Incrementation */
      case 36: /* unaryexpression ::= expression Decrementation */ yytestcase(yyruleno==36);
#line 108 "sources/parser/parse.lm"
{ yygotominor.yy21 = new ast::expr::Unary( lexer::Lexeme::Type::PostIncrementation, yymsp[-1].minor.yy83 ); }
#line 1138 "sources/parser/parse.c"
        break;
      case 35: /* unaryexpression ::= Decrementation expression */
#line 109 "sources/parser/parse.lm"
{ yygotominor.yy21 = new ast::expr::Unary( lexer::Lexeme::Type::PreDecrementation, yymsp[0].minor.yy83 );  }
#line 1143 "sources/parser/parse.c"
        break;
      case 37: /* binaryexpression ::= expression PositiveAddition expression */
#line 113 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Addition,                  yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1148 "sources/parser/parse.c"
        break;
      case 38: /* binaryexpression ::= expression NegativeSubstraction expression */
#line 114 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Substraction,              yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1153 "sources/parser/parse.c"
        break;
      case 39: /* binaryexpression ::= expression Multiplication expression */
#line 115 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Multiplication,            yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1158 "sources/parser/parse.c"
        break;
      case 40: /* binaryexpression ::= expression Division expression */
#line 116 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Division,                  yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1163 "sources/parser/parse.c"
        break;
      case 41: /* binaryexpression ::= expression Modulo expression */
#line 117 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Modulo,                    yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1168 "sources/parser/parse.c"
        break;
      case 42: /* binaryexpression ::= expression AdditionAssignment expression */
#line 119 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::AdditionAssignment,        yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1173 "sources/parser/parse.c"
        break;
      case 43: /* binaryexpression ::= expression SubstractionAssignment expression */
#line 120 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::SubstractionAssignment,    yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1178 "sources/parser/parse.c"
        break;
      case 44: /* binaryexpression ::= expression MultiplicationAssignment expression */
#line 121 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::MultiplicationAssignment,  yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1183 "sources/parser/parse.c"
        break;
      case 45: /* binaryexpression ::= expression DivisionAssignment expression */
#line 122 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::DivisionAssignment,        yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1188 "sources/parser/parse.c"
        break;
      case 46: /* binaryexpression ::= expression ModuloAssignment expression */
#line 123 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::ModuloAssignment,          yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1193 "sources/parser/parse.c"
        break;
      case 47: /* binaryexpression ::= expression Assignment expression */
#line 125 "sources/parser/parse.lm"
{ yygotominor.yy127 = new ast::expr::Binary( lexer::Lexeme::Type::Assignment,                yymsp[-2].minor.yy83, yymsp[0].minor.yy83 ); }
#line 1198 "sources/parser/parse.c"
        break;
      case 48: /* multaryexpression ::= expression LParenthesis multaryoperands RParenthesis */
#line 128 "sources/parser/parse.lm"
{ yygotominor.yy24 = new ast::expr::Multary( lexer::Lexeme::Type::Call,   yymsp[-3].minor.yy83, yymsp[-1].minor.yy57 ); }
#line 1203 "sources/parser/parse.c"
        break;
      case 49: /* multaryexpression ::= expression LBracket multaryoperands RBracket */
#line 129 "sources/parser/parse.lm"
{ yygotominor.yy24 = new ast::expr::Multary( lexer::Lexeme::Type::Access, yymsp[-3].minor.yy83, yymsp[-1].minor.yy57 ); }
#line 1208 "sources/parser/parse.c"
        break;
      case 50: /* multaryoperands ::= multaryoperandslist */
#line 132 "sources/parser/parse.lm"
{ yygotominor.yy57 = yymsp[0].minor.yy57;                        }
#line 1213 "sources/parser/parse.c"
        break;
      case 51: /* multaryoperands ::= */
#line 133 "sources/parser/parse.lm"
{ yygotominor.yy57 = nullptr;                  }
#line 1218 "sources/parser/parse.c"
        break;
      case 52: /* multaryoperandslist ::= expression Comma multaryoperandslist */
#line 136 "sources/parser/parse.lm"
{ yygotominor.yy57 = new ast::expr::Multary::Operand( yymsp[-2].minor.yy83 ); yygotominor.yy57->next( yymsp[0].minor.yy57 ); }
#line 1223 "sources/parser/parse.c"
        break;
      case 53: /* multaryoperandslist ::= expression */
#line 137 "sources/parser/parse.lm"
{ yygotominor.yy57 = new ast::expr::Multary::Operand( yymsp[0].minor.yy83 );               }
#line 1228 "sources/parser/parse.c"
        break;
      case 54: /* booleanexpression ::= False */
#line 140 "sources/parser/parse.lm"
{ yygotominor.yy6 = new ast::expr::Boolean( false ); }
#line 1233 "sources/parser/parse.c"
        break;
      case 55: /* booleanexpression ::= True */
#line 141 "sources/parser/parse.lm"
{ yygotominor.yy6 = new ast::expr::Boolean( true );  }
#line 1238 "sources/parser/parse.c"
        break;
      case 56: /* functionexpression ::= LParenthesis Function parameters Colon statementblock RParenthesis */
#line 144 "sources/parser/parse.lm"
{ yygotominor.yy108 = new ast::expr::Function( yymsp[-3].minor.yy125, yymsp[-1].minor.yy84 ); }
#line 1243 "sources/parser/parse.c"
        break;
      case 57: /* nullexpression ::= Null */
#line 147 "sources/parser/parse.lm"
{ yygotominor.yy45 = new ast::expr::Null( ); }
#line 1248 "sources/parser/parse.c"
        break;
      case 58: /* numberexpression ::= Number */
#line 150 "sources/parser/parse.lm"
{ yygotominor.yy91 = new ast::expr::Number( *yymsp[0].minor.yy0 ); }
#line 1253 "sources/parser/parse.c"
        break;
      case 59: /* undefinedexpression ::= Undefined */
#line 153 "sources/parser/parse.lm"
{ yygotominor.yy85 = new ast::expr::Undefined( ); }
#line 1258 "sources/parser/parse.c"
        break;
      case 60: /* variableexpression ::= Identifier */
#line 156 "sources/parser/parse.lm"
{ yygotominor.yy20 = new ast::expr::Variable( *yymsp[0].minor.yy0 ); }
#line 1263 "sources/parser/parse.c"
        break;
      case 61: /* parenthesisexpression ::= LParenthesis expression RParenthesis */
#line 159 "sources/parser/parse.lm"
{ yygotominor.yy83 = yymsp[-1].minor.yy83;            }
#line 1268 "sources/parser/parse.c"
        break;
      case 62: /* parameters ::= parameterlist */
#line 162 "sources/parser/parse.lm"
{ yygotominor.yy125 = yymsp[0].minor.yy125;                           }
#line 1273 "sources/parser/parse.c"
        break;
      case 63: /* parameters ::= */
#line 163 "sources/parser/parse.lm"
{ yygotominor.yy125 = nullptr;                     }
#line 1278 "sources/parser/parse.c"
        break;
      case 64: /* parameterlist ::= Identifier Comma parameterlist */
#line 166 "sources/parser/parse.lm"
{ yygotominor.yy125 = new ast::expr::Function::Parameter( *yymsp[-2].minor.yy0 ); yygotominor.yy125->next( yymsp[0].minor.yy125 ); }
#line 1283 "sources/parser/parse.c"
        break;
      case 65: /* parameterlist ::= Identifier */
#line 167 "sources/parser/parse.lm"
{ yygotominor.yy125 = new ast::expr::Function::Parameter( *yymsp[0].minor.yy0 );               }
#line 1288 "sources/parser/parse.c"
        break;
      default:
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 39 "sources/parser/parse.lm"

    castelparserIsValid = false;
#line 1353 "sources/parser/parse.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
