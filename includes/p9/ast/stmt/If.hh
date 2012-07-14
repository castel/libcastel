#pragma once

#include <memory>

#include "p9/ast/Expression.hh"
#include "p9/ast/Statement.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace ast
    {

        namespace stmt
        {

            class If : public ast::Statement
            {

            public:

                If            ( ast::Expression * condition = nullptr, ast::Statement * thenBranch = nullptr, ast::Statement * elseBranch = nullptr )
                : mCondition  ( condition )
                , mThenBranch ( thenBranch )
                , mElseBranch ( elseBranch )
                {
                }

            public:

                ast::Expression * condition( void ) const
                {
                    return mCondition.get( );
                }

                If & condition( ast::Expression * condition )
                {
                    mCondition.reset( condition );

                    return *this;
                }

                ast::Expression * takeCondition( void )
                {
                    return mCondition.release( );
                }

            public:

                ast::Statement * thenBranch( void ) const
                {
                    return mThenBranch.get( );
                }

                If & thenBranch( ast::Statement * thenBranch )
                {
                    mThenBranch.reset( thenBranch );

                    return *this;
                }

                ast::Statement * takeThenBranch( void )
                {
                    return mThenBranch.release( );
                }

            public:

                ast::Statement * elseBranch( void ) const
                {
                    return mElseBranch.get( );
                }

                If & elseBranch( ast::Statement * elseBranch )
                {
                    mElseBranch.reset( elseBranch );

                    return *this;
                }

                ast::Statement * takeElseBranch( void )
                {
                    return mElseBranch.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                std::unique_ptr< ast::Expression > mCondition;

                std::unique_ptr< ast::Statement > mThenBranch;
                std::unique_ptr< ast::Statement > mElseBranch;

            };

        }

    }

}
