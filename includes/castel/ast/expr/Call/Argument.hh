#pragma once

#include <memory>

#include "castel/ast/expr/Call.hh"
#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Linked.hh"

namespace castel
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
