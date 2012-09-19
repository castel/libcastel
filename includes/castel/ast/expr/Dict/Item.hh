#pragma once

#include <memory>
#include <string>

#include "castel/ast/expr/Dict.hh"
#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Linked.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Dict::Item : public utils::Linked< Dict::Item >
            {

            public:

                Item     ( std::string const & name, ast::Expression * value )
                : mName  ( name  )
                , mValue ( value )
                {
                }

                Item     ( lexer::Lexeme const & lexeme, ast::Expression * value )
                : mName  ( lexeme.as< std::string >( ) )
                , mValue ( value                       )
                {
                }

            public:

                std::string const & name( void ) const
                {
                    return mName;
                }

                Item & name( std::string const & name )
                {
                    mName = name;
                }

            public:

                ast::Expression * value( void ) const
                {
                    return mValue.get( );
                }

                Item & value( ast::Expression * value )
                {
                    mValue.reset( value );

                    return * this;
                }

                ast::Expression * takeValue( void )
                {
                    return mValue.release( );
                }

            private:

                std::string mName;

                std::unique_ptr< ast::Expression > mValue;

            };

        }

    }

}
