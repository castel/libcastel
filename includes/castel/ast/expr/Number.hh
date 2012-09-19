#pragma once

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Number : public ast::Expression
            {

            public:

                typedef double dataType;

            public:

                Number ( void )
                : mValue ( 0 )
                {
                }

                Number ( lexer::Lexeme const & lexeme )
                : mValue ( lexeme.as< dataType >( ) )
                {
                }

                Number ( dataType value )
                : mValue ( value )
                {
                }

            public:

                dataType value( void ) const
                {
                    return mValue;
                }

                Number & value( dataType value )
                {
                    mValue = value;

                    return * this;
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                dataType mValue;

            };

        }

    }

}
