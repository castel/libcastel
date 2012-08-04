#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Binary : public ast::Expression
            {

            public:

                Binary   ( void )
                : mType  ( lexer::Lexeme::Type::Invalid )
                , mLeft  (                              )
                , mRight (                              )
                {
                }

                Binary   ( lexer::Lexeme::Type type, ast::Expression * left = nullptr, ast::Expression * right = nullptr )
                : mType  ( type  )
                , mLeft  ( left  )
                , mRight ( right )
                {
                }

            public:

                lexer::Lexeme::Type type( void ) const
                {
                    return mType;
                }

                Binary & type( lexer::Lexeme::Type type )
                {
                    mType = type;

                    return *this;
                }

            public:

                ast::Expression * left( void ) const
                {
                    return mLeft.get( );
                }

                Binary & left( ast::Expression * expression )
                {
                    mLeft.reset( expression );

                    return *this;
                }

                ast::Expression * takeLeft( void )
                {
                    return mLeft.release( );
                }

            public:

                ast::Expression * right( void ) const
                {
                    return mRight.get( );
                }

                Binary & right( ast::Expression * expression )
                {
                    mRight.reset( expression );

                    return *this;
                }

                ast::Expression * takeRight( void )
                {
                    return mRight.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                lexer::Lexeme::Type mType;

                std::unique_ptr< ast::Expression > mLeft;
                std::unique_ptr< ast::Expression > mRight;

            };

        }

    }

}
