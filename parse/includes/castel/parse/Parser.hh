#pragma once

#include <string>

#include "castel/ast/tools/List.hh"

namespace castel
{

    namespace ast
    {

        class Statement;

    }

    namespace lex
    {

        class Lexer;

    }

    namespace parse
    {

        class Parser
        {

        public:

            inline Parser( lex::Lexer & lexer );

        public:

            ast::tools::List< ast::Statement > exec( void );

        private:

            lex::Lexer & mLexer;

        };

    }

}

#include "castel/ast/Statement.hh"
#include "castel/lex/Lexer.hh"

namespace castel
{

    namespace parse
    {

        Parser::Parser( lex::Lexer & lexer )
            : mLexer( lexer )
        {
        }

    }

}
