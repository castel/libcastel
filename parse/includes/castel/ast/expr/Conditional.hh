#pragma once

#include <memory>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Conditional : public ast::Expression
            {

            public:

                inline Conditional( ast::Expression * condition, ast::Expression * thenExpression, ast::Expression * elseExpression );

            public:

                inline ast::Expression * condition( void ) const;

                inline Conditional & condition( ast::Expression * condition );

                inline ast::Expression * takeCondition( void );

            public:

                inline ast::Expression * thenExpression( void ) const;

                inline Conditional & thenExpression( ast::Expression * thenExpression );

                inline ast::Expression * takeThenExpression( void );

            public:

                inline ast::Expression * elseExpression( void ) const;

                inline Conditional & elseExpression( ast::Expression * elseExpression );

                inline ast::Expression * takeElseExpression( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::Expression > mCondition;

                std::unique_ptr< ast::Expression > mThenExpression;

                std::unique_ptr< ast::Expression > mElseExpression;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Conditional::Conditional( ast::Expression * condition, ast::Expression * thenExpression, ast::Expression * elseExpression )
                : mCondition( condition )
                , mThenExpression( thenExpression )
                , mElseExpression( elseExpression )
            {
            }

            ast::Expression * Conditional::condition( void ) const
            {
                return mCondition.get( );
            }

            Conditional & Conditional::condition( ast::Expression * condition )
            {
                mCondition.reset( condition );

                return * this;
            }

            ast::Expression * Conditional::takeCondition( void )
            {
                return mCondition.release( );
            }

            ast::Expression * Conditional::thenExpression( void ) const
            {
                return mThenExpression.get( );
            }

            Conditional & Conditional::thenExpression( ast::Expression * thenExpression )
            {
                mThenExpression.reset( thenExpression );

                return * this;
            }

            ast::Expression * Conditional::takeThenExpression( void )
            {
                return mThenExpression.release( );
            }

            ast::Expression * Conditional::elseExpression( void ) const
            {
                return mElseExpression.get( );
            }

            Conditional & Conditional::elseExpression( ast::Expression * elseExpression )
            {
                mElseExpression.reset( elseExpression );

                return * this;
            }

            ast::Expression * Conditional::takeElseExpression( void )
            {
                return mElseExpression.release( );
            }

            void Conditional::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
