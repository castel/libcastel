%{
#include "y.tab.h"
%}

%%

\+\+                                                    return T_INCREMENT;
--                                                      return T_DECREMENT;

=                                                       return T_ASSIGN;

\+=                                                     return T_ASSIGN_NUMERIC_ADD;
-=                                                      return T_ASSIGN_NUMERIC_SUB;
\*=                                                     return T_ASSIGN_NUMERIC_MUL;
\/=                                                     return T_ASSIGN_NUMERIC_DIV;
%=                                                      return T_ASSIGN_NUMERIC_MOD;

~=                                                      return T_ASSIGN_BINARY_NOT;
&=                                                      return T_ASSIGN_BINARY_AND;
\|=                                                     return T_ASSIGN_BINARY_OR;
^=                                                      return T_ASSIGN_BINARY_XOR;
\<\<=                                                   return T_ASSIGN_BINARY_LSHIFT;
>>=                                                     return T_ASSIGN_BINARY_RSHIFT;

\+                                                      return T_NUMERIC_ADD;
-                                                       return T_NUMERIC_SUB;
\*                                                      return T_NUMERIC_MUL;
\/                                                      return T_NUMERIC_DIV;
%                                                       return T_NUMERIC_MOD;

~                                                       return T_BINARY_NOT;
&                                                       return T_BINARY_AND;
\|                                                      return T_BINARY_OR;
\^                                                      return T_BINARY_XOR;
\<\<                                                    return T_BINARY_LSHIFT;
>>                                                      return T_BINARY_RSHIFT;

!                                                       return T_LOGICAL_NOT;
&&                                                      return T_LOGICAL_AND;
\|\|                                                    return T_LOGICAL_OR;

==                                                      return T_RELATIONAL_EQUAL;
!=                                                      return T_RELATIONAL_DIFFERENT;
\<                                                      return T_RELATIONAL_LESSER;
>                                                       return T_RELATIONAL_GREATER;
\<=                                                     return T_RELATIONAL_LESSER_OR_EQUAL;
>=                                                      return T_RELATIONAL_GREATER_OR_EQUAL;

{                                                       return T_LBRACE;
}                                                       return T_RBRACE;

\(                                                      return T_LPARENTHESIS;
\)                                                      return T_RPARENTHESIS;

\[                                                      return T_LBRACKET;
\]                                                      return T_RBRACKET;

\.                                                      return T_DOT;
,                                                       return T_COMMA;
;                                                       return T_SEMICOLON;
:                                                       return T_COLON;

this                                                    return T_THIS;
new                                                     return T_NEW;
class                                                   return T_CLASS;
function                                                return T_FUNCTION;
Mixed                                                   return T_MIXED;

[a-zA-Z]([a-zA-Z0-9_]*[a-zA-Z0-9]|[a-zA-Z0-9]*)         return T_IDENTIFIER;
[0-9]+(\.[0-9]*)?|[0-9]*\.[0-9]+|0x[0-9A-Fa-f]+|0[0-8]+ return T_NUMBER;
\"\"                                                    return T_STRING;

[ \t]+                                                  /* ignored */;
(\r\n|\r|\n)                                            /* ignored */;

.                                                       return T_UNEXPECTED;

%%
