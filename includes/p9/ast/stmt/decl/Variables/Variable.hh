#pragma once

#include <memory>
#include <string>

#include "p9/ast/stmt/decl/Variables.hh"
#include "p9/ast/Expression.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/utils/Linked.hh"

namespace p9
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                class Variables::Variable : public utils::Linked< Variable >
                {

                public:

                    Variable       ( std::string const & name, ast::Expression * initializer = nullptr )
                    : mName        ( name )
                    , mInitializer ( initializer )
                    {
                    }

                    Variable       ( lexer::Lexeme const & lexeme, ast::Expression * initializer = nullptr )
                    : mName        ( lexeme.as< std::string >( ) )
                    , mInitializer ( initializer )
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

                    ast::Expression * initializer( void ) const
                    {
                        return mInitializer.get( );
                    }

                    Variable & initializer( ast::Expression * initializer )
                    {
                        mInitializer.reset( initializer );

                        return *this;
                    }

                    ast::Expression * takeInitializer( void )
                    {
                        return mInitializer.release( );
                    }

                private:

                    std::string mName;

                    std::unique_ptr< ast::Expression > mInitializer;

                };

            }

        }

    }

}
