#pragma once

#include <memory>

#include "p9/ast/Expression.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Type.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace ast
    {

        namespace expr
        {

            class Binary : public ast::Expression
            {

            public:

                Binary   ( void )
                : mType  ( lexer::T_Invalid )
                , mLeft  (                  )
                , mRight (                  )
                {
                }

                Binary   ( lexer::Type type, ast::Expression * left = 0, ast::Expression * right = 0 )
                : mType  ( type  )
                , mLeft  ( left  )
                , mRight ( right )
                {
                }

            public:

                lexer::Type type( void ) const
                {
                    return mType;
                }

                Binary & type( lexer::Type type )
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

                lexer::Type mType;

                std::unique_ptr< ast::Expression > mLeft;
                std::unique_ptr< ast::Expression > mRight;

            };

        }

    }

}
