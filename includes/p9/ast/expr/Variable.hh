#pragma once

#include <string>

#include "p9/ast/Expression.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/utils/Visitor.hh"

namespace p9
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
