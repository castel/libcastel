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

                class ForIn : public ast::Statement
                {

                public:

                    inline ForIn( std::string const & target, ast::tools::Hold< ast::Expression > && source, ast::tools::Hold< ast::Statement > && thenBranch );

                    inline ForIn( std::string const & target, ast::tools::Hold< ast::Expression > && source, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    inline std::string const & target( void ) const;

                    inline ForIn & target( std::string const & target );

                public:

                    inline ast::tools::Hold< ast::Expression > const & source( void ) const;

                    inline ast::tools::Hold< ast::Expression > & source( void );

                    inline ForIn & source( ast::tools::Hold< ast::Expression > && source );

                public:

                    inline ast::tools::Hold< ast::Statement > const & thenBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & thenBranch( void );

                    inline ForIn & thenBranch( ast::tools::Hold< ast::Statement > && thenBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & elseBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & elseBranch( void );

                    inline ForIn & elseBranch( ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::string mTarget;

                    ast::tools::Hold< ast::Expression > mSource;

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

                ForIn::ForIn( std::string const & target, ast::tools::Hold< ast::Expression > && source, ast::tools::Hold< ast::Statement > && thenBranch )
                    : mTarget( target )
                    , mSource( std::move( source ) )
                    , mThenBranch( std::move( thenBranch ) )
                {
                }

                ForIn::ForIn( std::string const & target, ast::tools::Hold< ast::Expression > && source, ast::tools::Hold< ast::Statement > && thenBranch, ast::tools::Hold< ast::Statement > && elseBranch )
                    : mTarget( target )
                    , mSource( std::move( source ) )
                    , mThenBranch( std::move( thenBranch ) )
                    , mElseBranch( std::move( elseBranch ) )
                {
                }

                std::string const & ForIn::target( void ) const
                {
                    return mTarget;
                }

                ForIn & ForIn::target( std::string const & target )
                {
                    mTarget = target;

                    return * this;
                }

                ast::tools::Hold< ast::Expression > const & ForIn::source( void ) const
                {
                    return mSource;
                }

                ast::tools::Hold< ast::Expression > & ForIn::source( void )
                {
                    return mSource;
                }

                ForIn & ForIn::source( ast::tools::Hold< ast::Expression > && source )
                {
                    mSource = std::move( source );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & ForIn::thenBranch( void ) const
                {
                    return mThenBranch;
                }

                ast::tools::Hold< ast::Statement > & ForIn::thenBranch( void )
                {
                    return mThenBranch;
                }

                ForIn & ForIn::thenBranch( ast::tools::Hold< ast::Statement > && thenBranch )
                {
                    mThenBranch = std::move( thenBranch );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & ForIn::elseBranch( void ) const
                {
                    return mElseBranch;
                }

                ast::tools::Hold< ast::Statement > & ForIn::elseBranch( void )
                {
                    return mElseBranch;
                }

                ForIn & ForIn::elseBranch( ast::tools::Hold< ast::Statement > && elseBranch )
                {
                    mElseBranch = std::move( elseBranch );

                    return * this;
                }

                void ForIn::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void ForIn::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
