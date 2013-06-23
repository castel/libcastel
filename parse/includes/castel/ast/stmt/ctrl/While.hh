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

                class While : public ast::Statement
                {

                public:

                    inline While( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch );

                    inline While( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    inline ast::tools::Hold< ast::Expression > const & condition( void ) const;

                    inline ast::tools::Hold< ast::Expression > & condition( void );

                    inline While & condition( ast::tools::Hold< ast::Expression > && condition );

                public:

                    inline ast::tools::Hold< ast::Statement > const & thenBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & thenBranch( void );

                    inline While & thenBranch( ast::tools::Hold< ast::Statement > && thenBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & elseBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & elseBranch( void );

                    inline While & elseBranch( ast::tools::Hold< ast::Statement > && elseBranch );

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

                While::While( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                {
                }

                While::While( ast::tools::Hold< ast::Expression > && condition, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch )
                    : mCondition( std::move( condition ) )
                    , mThenBranch( std::move( thenBranch ) )
                    , mElseBranch( std::move( elseBranch ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & While::condition( void ) const
                {
                    return mCondition;
                }

                ast::tools::Hold< ast::Expression > & While::condition( void )
                {
                    return mCondition;
                }

                While & While::condition( ast::tools::Hold< ast::Expression > && condition )
                {
                    mCondition = std::move( condition );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & While::thenBranch( void ) const
                {
                    return mThenBranch;
                }

                ast::tools::Hold< ast::Statement > & While::thenBranch( void )
                {
                    return mThenBranch;
                }

                While & While::thenBranch( ast::tools::Hold< ast::Statement > && thenBranch )
                {
                    mThenBranch = std::move( thenBranch );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & While::elseBranch( void ) const
                {
                    return mElseBranch;
                }

                ast::tools::Hold< ast::Statement > & While::elseBranch( void )
                {
                    return mElseBranch;
                }

                While & While::elseBranch( ast::tools::Hold< ast::Statement > && elseBranch )
                {
                    mElseBranch = std::move( elseBranch );

                    return * this;
                }

                void While::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void While::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
