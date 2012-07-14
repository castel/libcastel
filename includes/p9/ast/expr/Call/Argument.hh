#pragma once

#include <memory>

#include "p9/ast/expr/Call.hh"
#include "p9/ast/Expression.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/utils/Linked.hh"

namespace p9
{

    namespace ast
    {

        namespace expr
        {

            class Call::Argument : public utils::Linked< Call::Argument >
            {

            public:

                Argument ( ast::Expression * value = nullptr )
                : mValue ( value )
                {
                }

            public:

                ast::Expression * value( void ) const
                {
                    return mValue.get( );
                }

                Argument & value( ast::Expression * value )
                {
                    mValue.reset( value );

                    return *this;
                }

                ast::Expression * takeValue( void )
                {
                    return mValue.release( );
                }

            private:

                std::unique_ptr< ast::Expression > mValue;

            };

        }

    }

}
