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

                class If : public ast::Statement
                {

                public:

                    inline If( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch );

                    inline If( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    inline ast::tools::Hold< ast::Expression > const & condition( void ) const;

                    inline ast::tools::Hold< ast::Expression > & condition( void );

                    inline If & condition( ast::tools::Hold< ast::Expression > && condition );

                public:

                    inline ast::tools::Hold< ast::Statement > const & thenBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & thenBranch( void );

                    inline If & thenBranch( ast::tools::Hold< ast::Statement > && thenBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & elseBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & elseBranch( void );

                    inline If & elseBranch( ast::tools::Hold< ast::Statement > && elseBranch );

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

                If::If( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                {
                }

                If::If( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                    , mElseBranch( std::move( elseBranch ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & If::condition( void ) const
                {
                    return mCondition;
                }

                ast::tools::Hold< ast::Expression > & If::condition( void )
                {
                    return mCondition;
                }

                If & If::condition( ast::tools::Hold< ast::Expression > && condition )
                {
                    mCondition = std::move( condition );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & If::thenBranch( void ) const
                {
                    return mThenBranch;
                }

                ast::tools::Hold< ast::Statement > & If::thenBranch( void )
                {
                    return mThenBranch;
                }

                If & If::thenBranch( ast::tools::Hold< ast::Statement > && thenBranch )
                {
                    mThenBranch = std::move( thenBranch );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & If::elseBranch( void ) const
                {
                    return mElseBranch;
                }

                ast::tools::Hold< ast::Statement > & If::elseBranch( void )
                {
                    return mElseBranch;
                }

                If & If::elseBranch( ast::tools::Hold< ast::Statement > && elseBranch )
                {
                    mElseBranch = std::move( elseBranch );

                    return * this;
                }

                void If::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void If::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
