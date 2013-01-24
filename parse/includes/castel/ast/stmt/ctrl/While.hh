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

                class While : public ast::Statement
                {

                public:

                    inline While( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch = nullptr );

                public:

                    inline ast::Expression * condition( void ) const;

                    inline While & condition( ast::Expression * condition );

                    inline ast::Expression * takeCondition( void );

                public:

                    inline ast::Statement * thenBranch( void ) const;

                    inline While & thenBranch( ast::Statement * thenBranch );

                    inline ast::Statement * takeThenBranch( void );

                public:

                    inline ast::Statement * elseBranch( void ) const;

                    inline While & elseBranch( ast::Statement * elseBranch );

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

                While::While( ast::Expression * condition, ast::Statement * thenBranch, ast::Statement * elseBranch )
                    : mCondition( condition )
                    , mThenBranch( thenBranch )
                    , mElseBranch( elseBranch )
                {
                }

                ast::Expression * While::condition( void ) const
                {
                    return mCondition.get( );
                }

                While & While::condition( ast::Expression * condition )
                {
                    mCondition.reset( condition );

                    return * this;
                }

                ast::Expression * While::takeCondition( void )
                {
                    return mCondition.release( );
                }

                ast::Statement * While::thenBranch( void ) const
                {
                    return mThenBranch.get( );
                }

                While & While::thenBranch( ast::Statement * thenBranch )
                {
                    mThenBranch.reset( thenBranch );

                    return * this;
                }

                ast::Statement * While::takeThenBranch( void )
                {
                    return mThenBranch.release( );
                }

                ast::Statement * While::elseBranch( void ) const
                {
                    return mElseBranch.get( );
                }

                While & While::elseBranch( ast::Statement * elseBranch )
                {
                    mElseBranch.reset( elseBranch );

                    return * this;
                }

                ast::Statement * While::takeElseBranch( void )
                {
                    return mElseBranch.release( );
                }

                void While::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
