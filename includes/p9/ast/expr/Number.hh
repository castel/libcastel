#pragma once

#include "p9/ast/Expression.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/utils/Visitor.hh"

namespace p9
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

                    return *this;
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                dataType mValue;

            };

        }

    }

}