#pragma once

#include <memory>
#include <string>

#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Linked.hh"

namespace castel
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
