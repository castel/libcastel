#pragma once

#include <string>

#include "p9/ast/Token.hh"
#include "p9/lexer/Lexer.hh"

namespace p9
{

    namespace parser
    {

        class Parser {

        public:

            Parser( lexer::Lexer & lexer );

        public:

            ast::Token * exec( void );

        private:

            lexer::Lexer & mLexer;

        };

    }

}
