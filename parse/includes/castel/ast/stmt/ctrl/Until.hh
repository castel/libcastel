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

            namespace ctrl
            {

                class Until : public ast::Statement
                {

                public:

                    inline Until( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch = nullptr );

                public:

                    inline ast::Expression * condition( void ) const;

                    inline Until & condition( ast::Expression * condition );

                    inline ast::Expression * takeCondition( void );

                public:

                    inline ast::Statement * thenBranch( void ) const;

                    inline Until & thenBranch( ast::Statement * thenBranch );

                    inline ast::Statement * takeThenBranch( void );

                public:

                    inline ast::Statement * elseBranch( void ) const;

                    inline Until & elseBranch( ast::Statement * elseBranch );

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

}

#include "castel/ast/tools/Visitor.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace ctrl
            {

                Until::Until( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch )
                    : mCondition( condition )
                    , mThenBranch( thenBranch )
                    , mElseBranch( elseBranch )
                {
                }

                ast::Expression * Until::condition( void ) const
                {
                    return mCondition.get( );
                }

                Until & Until::condition( ast::Expression * condition )
                {
                    mCondition.reset( condition );

                    return * this;
                }

                ast::Expression * Until::takeCondition( void )
                {
                    return mCondition.release( );
                }

                ast::Statement * Until::thenBranch( void ) const
                {
                    return mThenBranch.get( );
                }

                Until & Until::thenBranch( ast::Statement * thenBranch )
                {
                    mThenBranch.reset( thenBranch );

                    return * this;
                }

                ast::Statement * Until::takeThenBranch( void )
                {
                    return mThenBranch.release( );
                }

                ast::Statement * Until::elseBranch( void ) const
                {
                    return mElseBranch.get( );
                }

                Until & Until::elseBranch( ast::Statement * elseBranch )
                {
                    mElseBranch.reset( elseBranch );

                    return * this;
                }

                ast::Statement * Until::takeElseBranch( void )
                {
                    return mElseBranch.release( );
                }

                void Until::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
