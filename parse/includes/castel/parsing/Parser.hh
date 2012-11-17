#pragma once

#include <string>

namespace castel
{

    namespace ast
    {

        class Statement;

    }

    namespace lexing
    {

        class Lexer;

    }

    namespace parsing
    {

        class Parser
        {

        public:

            inline Parser( lexing::Lexer & lexer );

        public:

            ast::Statement * exec( void );

        private:

            lexing::Lexer & mLexer;

        };

    }

}

#include "castel/ast/Statement.hh"
#include "castel/lexing/Lexer.hh"

namespace castel
{

    namespace parsing
    {

        Parser::Parser( lexing::Lexer & lexer )
            : mLexer( lexer )
        {
        }

    }

}
