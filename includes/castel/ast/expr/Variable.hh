#pragma once

#include <string>

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Variable : public ast::Expression
            {

            public:

                Variable ( std::string const & name )
                : mName  ( name )
                {
                }

                Variable ( lexer::Lexeme const & lexeme )
                : mName  ( lexeme.as< std::string >( ) )
                {
                }

            public:

                std::string const & name( void ) const
                {
                    return mName;
                }

                Variable & name( std::string const & name )
                {
                    mName = name;

                    return *this;
                }

            public:

                void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                std::string mName;

            };

        }

    }

}
