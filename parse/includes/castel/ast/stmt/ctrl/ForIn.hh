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

                class ForIn : public ast::Statement
                {

                public:

                    inline ForIn( std::string const & target, ast::Expression * source, ast::Statement * thenBranch, ast::Statement * elseBranch = nullptr );

                public:

                    inline std::string const & target( void ) const;

                    inline ForIn & target( std::string const & target );

                public:

                    inline ast::Expression * source( void ) const;

                    inline ForIn & source( ast::Expression * source );

                    inline ast::Expression * takeSource( void );

                public:

                    inline ast::Statement * thenBranch( void ) const;

                    inline ForIn & thenBranch( ast::Statement * thenBranch );

                    inline ast::Statement * takeThenBranch( void );

                public:

                    inline ast::Statement * elseBranch( void ) const;

                    inline ForIn & elseBranch( ast::Statement * elseBranch );

                    inline ast::Statement * takeElseBranch( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::string mTarget;

                    std::unique_ptr< ast::Expression > mSource;

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

                ForIn::ForIn( std::string const & target, ast::Expression * source, ast::Statement * thenBranch, ast::Statement * elseBranch )
                    : mTarget( target )
                    , mSource( source )
                    , mThenBranch( thenBranch )
                    , mElseBranch( elseBranch )
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

                ast::Expression * ForIn::source( void ) const
                {
                    return mSource.get( );
                }

                ForIn & ForIn::source( ast::Expression * source )
                {
                    mSource.reset( source );

                    return * this;
                }

                ast::Expression * ForIn::takeSource( void )
                {
                    return mSource.release( );
                }

                ast::Statement * ForIn::thenBranch( void ) const
                {
                    return mThenBranch.get( );
                }

                ForIn & ForIn::thenBranch( ast::Statement * thenBranch )
                {
                    mThenBranch.reset( thenBranch );

                    return * this;
                }

                ast::Statement * ForIn::takeThenBranch( void )
                {
                    return mThenBranch.release( );
                }

                ast::Statement * ForIn::elseBranch( void ) const
                {
                    return mElseBranch.get( );
                }

                ForIn & ForIn::elseBranch( ast::Statement * elseBranch )
                {
                    mElseBranch.reset( elseBranch );

                    return * this;
                }

                ast::Statement * ForIn::takeElseBranch( void )
                {
                    return mElseBranch.release( );
                }

                void ForIn::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
