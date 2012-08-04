#pragma once

#include <string>

#include "castel/ast/Statement.hh"
#include "castel/lexer/Lexer.hh"

namespace castel
{

    namespace parser
    {

        class Parser {

        public:

            Parser( lexer::Lexer & lexer );

        public:

            ast::Statement * exec( void );

        private:

            lexer::Lexer & mLexer;

        };

    }

}
