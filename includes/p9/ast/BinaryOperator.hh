#pragma once

#include "p9/ast/Expression.hh"
#include "p9/ast/Visitor.hh"

namespace p9
{

    namespace ast
    {

        class BinaryOperator : public ast::Expression
        {

        public:

            BinaryOperator ( void )
            : mType        ( 0 )
            , mLeft        (   )
            , mRight       (   )
            {
            }

            BinaryOperator ( lexer::Lexeme const & lexeme, ast::Expression * left = 0, ast::Expression * right = 0 )
            : mType        ( lexeme.type( ) )
            , mLeft        ( left           )
            , mRight       ( right          )
            {
            }

            BinaryOperator ( int type, ast::Expression * left = 0, ast::Expression * right = 0 )
            : mType        ( type  )
            , mLeft        ( left  )
            , mRight       ( right )
            {
            }

        public:

            int type( void ) const
            {
                return mType;
            }

            BinaryOperator & type( int type )
            {
                mType = type;

                return *this;
            }

        public:

            ast::Expression * left( void ) const
            {
                return mLeft.get( );
            }

            ast::Expression * right( void ) const
            {
                return mRight.get( );
            }

            BinaryOperator & left( ast::Expression * expression )
            {
                mLeft.reset( expression );

                return *this;
            }

            BinaryOperator & right( ast::Expression * expression )
            {
                mRight.reset( expression );

                return *this;
            }

        public:

            ast::Expression * takeLeft( void )
            {
                return mLeft.release( );
            }

            ast::Expression * takeRight( void )
            {
                return mRight.release( );
            }

        public:

            virtual void accept( Visitor & visitor )
            {
                visitor.visit( *this );
            }

        private:

            int mType;

            std::auto_ptr< ast::Expression > mLeft;
            std::auto_ptr< ast::Expression > mRight;

        };

    }

}
