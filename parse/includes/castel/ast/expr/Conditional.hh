#pragma once

#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        namespace expr
        {

            class Conditional : public ast::Expression
            {

            public:

                inline Conditional( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Expression > && thenExpression, ast::tools::Hold< ast::Expression > && elseExpression );

            public:

                inline ast::tools::Hold< ast::Expression > const & condition( void ) const;

                inline ast::tools::Hold< ast::Expression > & condition( void );

                inline Conditional & condition( ast::tools::Hold< ast::Expression > && condition );

            public:

                inline ast::tools::Hold< ast::Expression > const & thenExpression( void ) const;

                inline ast::tools::Hold< ast::Expression > & thenExpression( void );

                inline Conditional & thenExpression( ast::tools::Hold< ast::Expression > && thenExpression );

            public:

                inline ast::tools::Hold< ast::Expression > const & elseExpression( void ) const;

                inline ast::tools::Hold< ast::Expression > & elseExpression( void );

                inline Conditional & elseExpression( ast::tools::Hold< ast::Expression > && elseExpression );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::tools::Hold< ast::Expression > mCondition;

                ast::tools::Hold< ast::Expression > mThenExpression;

                ast::tools::Hold< ast::Expression > mElseExpression;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Conditional::Conditional( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Expression > && thenExpression, ast::tools::Hold< ast::Expression > && elseExpression )
                : mCondition( std::move( condition ) )
                , mThenExpression( std::move( thenExpression ) )
                , mElseExpression( std::move( elseExpression ) )
            {
            }

            ast::tools::Hold< ast::Expression > const & Conditional::condition( void ) const
            {
                return mCondition;
            }

            ast::tools::Hold< ast::Expression > & Conditional::condition( void )
            {
                return mCondition;
            }

            Conditional & Conditional::condition( ast::tools::Hold< ast::Expression > && condition )
            {
                mCondition = std::move( condition );

                return * this;
            }

            ast::tools::Hold< ast::Expression > const & Conditional::thenExpression( void ) const
            {
                return mThenExpression;
            }

            ast::tools::Hold< ast::Expression > & Conditional::thenExpression( void )
            {
                return mThenExpression;
            }

            Conditional & Conditional::thenExpression( ast::tools::Hold< ast::Expression > && thenExpression )
            {
                mThenExpression = std::move( thenExpression );

                return * this;
            }

            ast::tools::Hold< ast::Expression > const & Conditional::elseExpression( void ) const
            {
                return mElseExpression;
            }

            ast::tools::Hold< ast::Expression > & Conditional::elseExpression( void )
            {
                return mElseExpression;
            }

            Conditional & Conditional::elseExpression( ast::tools::Hold< ast::Expression > && elseExpression )
            {
                mElseExpression = std::move( elseExpression );

                return * this;
            }

            void Conditional::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Conditional::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
