#pragma once

#include "p9/lexer/MangledTokens.hh"

namespace p9
{

    namespace lexer
    {

        enum Token {

            TInvalid      = - 1,
            TEOF          =   0,

            TFunction     = P9_LEXER_MANGLEDTOKENS_Function,
            TReturn       = P9_LEXER_MANGLEDTOKENS_Return,
            TVar          = P9_LEXER_MANGLEDTOKENS_Var,

            TNumber       = P9_LEXER_MANGLEDTOKENS_Number,
            TIdentifier   = P9_LEXER_MANGLEDTOKENS_Identifier,

            TAdd          = P9_LEXER_MANGLEDTOKENS_Add,
            TSubstract    = P9_LEXER_MANGLEDTOKENS_Substract,
            TMultiply     = P9_LEXER_MANGLEDTOKENS_Multiply,
            TDivide       = P9_LEXER_MANGLEDTOKENS_Divide,
            TModulo       = P9_LEXER_MANGLEDTOKENS_Modulo,
            TEqual        = P9_LEXER_MANGLEDTOKENS_Equal,

            TLParenthesis = P9_LEXER_MANGLEDTOKENS_LParenthesis,
            TRParenthesis = P9_LEXER_MANGLEDTOKENS_RParenthesis,

            TColon        = P9_LEXER_MANGLEDTOKENS_Colon,
            TComma        = P9_LEXER_MANGLEDTOKENS_Comma,

            TSpaces       = P9_LEXER_MANGLEDTOKENS_Spaces,
            TNewline      = P9_LEXER_MANGLEDTOKENS_Newline,

            TIndent       = P9_LEXER_MANGLEDTOKENS_Indent,
            TDedent       = P9_LEXER_MANGLEDTOKENS_Dedent,

        };

    }

}
