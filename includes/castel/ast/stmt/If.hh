#pragma once

#include <memory>

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        class Expression;

        namespace stmt
        {

            class If : public ast::Statement
            {

            public:

                inline If( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch = nullptr );

            public:

                inline ast::Expression * condition( void ) const;

                inline If & condition( ast::Expression * condition );

                inline ast::Expression * takeCondition( void );

            public:

                inline ast::Statement * thenBranch( void ) const;

                inline If & thenBranch( ast::Statement * thenBranch );

                inline ast::Statement * takeThenBranch( void );

            public:

                inline ast::Statement * elseBranch( void ) const;

                inline If & elseBranch( ast::Statement * elseBranch );

                inline ast::Statement * takeElseBranch( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::Expression > mCondition;

                std::unique_ptr< ast::Statement > mThenBranch;
                std::unique_ptr< ast::Statement > mElseBranch;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            If::If( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch )
                : mCondition( condition )
                , mThenBranch( thenBranch )
                , mElseBranch( elseBranch )
            {
            }

            ast::Expression * If::condition( void ) const
            {
                return mCondition.get( );
            }

            If & If::condition( ast::Expression * condition )
            {
                mCondition.reset( condition );

                return * this;
            }

            ast::Expression * If::takeCondition( void )
            {
                return mCondition.release( );
            }

            ast::Statement * If::thenBranch( void ) const
            {
                return mThenBranch.get( );
            }

            If & If::thenBranch( ast::Statement * thenBranch )
            {
                mThenBranch.reset( thenBranch );

                return * this;
            }

            ast::Statement * If::takeThenBranch( void )
            {
                return mThenBranch.release( );
            }

            ast::Statement * If::elseBranch( void ) const
            {
                return mElseBranch.get( );
            }

            If & If::elseBranch( ast::Statement * elseBranch )
            {
                mElseBranch.reset( elseBranch );

                return * this;
            }

            ast::Statement * If::takeElseBranch( void )
            {
                return mElseBranch.release( );
            }

            void If::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
