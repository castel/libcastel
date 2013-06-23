#pragma once

#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

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

                    inline Until( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch );

                    inline Until( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    inline ast::tools::Hold< ast::Expression > const & condition( void ) const;

                    inline ast::tools::Hold< ast::Expression > & condition( void );

                    inline Until & condition( ast::tools::Hold< ast::Expression > && condition );

                public:

                    inline ast::tools::Hold< ast::Statement > const & thenBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & thenBranch( void );

                    inline Until & thenBranch( ast::tools::Hold< ast::Statement > && thenBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & elseBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & elseBranch( void );

                    inline Until & elseBranch( ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::Hold< ast::Expression > mCondition;

                    ast::tools::Hold< ast::Statement > mThenBranch;

                    ast::tools::Hold< ast::Statement > mElseBranch;

                };

            }

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
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

                Until::Until( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                {
                }

                Until::Until( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                    , mElseBranch( std::move( elseBranch ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & Until::condition( void ) const
                {
                    return mCondition;
                }

                ast::tools::Hold< ast::Expression > & Until::condition( void )
                {
                    return mCondition;
                }

                Until & Until::condition( ast::tools::Hold< ast::Expression > && condition )
                {
                    mCondition = std::move( condition );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & Until::thenBranch( void ) const
                {
                    return mThenBranch;
                }

                ast::tools::Hold< ast::Statement > & Until::thenBranch( void )
                {
                    return mThenBranch;
                }

                Until & Until::thenBranch( ast::tools::Hold< ast::Statement > && thenBranch )
                {
                    mThenBranch = std::move( thenBranch );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & Until::elseBranch( void ) const
                {
                    return mElseBranch;
                }

                ast::tools::Hold< ast::Statement > & Until::elseBranch( void )
                {
                    return mElseBranch;
                }

                Until & Until::elseBranch( ast::tools::Hold< ast::Statement > && elseBranch )
                {
                    mElseBranch = std::move( elseBranch );

                    return * this;
                }

                void Until::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Until::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
