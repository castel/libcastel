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

        namespace stmt
        {

            namespace ctrl
            {

                class Try : public ast::Statement
                {

                public:

                    inline Try( ast::tools::Hold< ast::Statement > && tryBranch );

                    inline Try( ast::tools::Hold< ast::Statement > && tryBranch, ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & tryBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & tryBranch( void );

                    inline Try & tryBranch( ast::tools::Hold< ast::Statement > && tryBranch );

                public:

                    inline ast::tools::Hold< ast::Statement > const & elseBranch( void ) const;

                    inline ast::tools::Hold< ast::Statement > & elseBranch( void );

                    inline Try & elseBranch( ast::tools::Hold< ast::Statement > && elseBranch );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::Hold< ast::Statement > mTryBranch;

                    ast::tools::Hold< ast::Statement > mElseBranch;

                };

            }

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace ctrl
            {

                Try::Try( ast::tools::Hold< ast::Statement > && tryBranch )
                    : mTryBranch( std::move( tryBranch ) )
                {
                }

                Try::Try( ast::tools::Hold< ast::Statement > && tryBranch, ast::tools::Hold< ast::Statement > && elseBranch )
                    : mTryBranch( std::move( tryBranch ) )
                    , mElseBranch( std::move( elseBranch ) )
                {
                }

                ast::tools::Hold< ast::Statement > const & Try::tryBranch( void ) const
                {
                    return mTryBranch;
                }

                ast::tools::Hold< ast::Statement > & Try::tryBranch( void )
                {
                    return mTryBranch;
                }

                Try & Try::tryBranch( ast::tools::Hold< ast::Statement > && tryBranch )
                {
                    mTryBranch = std::move( tryBranch );

                    return * this;
                }

                ast::tools::Hold< ast::Statement > const & Try::elseBranch( void ) const
                {
                    return mElseBranch;
                }

                ast::tools::Hold< ast::Statement > & Try::elseBranch( void )
                {
                    return mElseBranch;
                }

                Try & Try::elseBranch( ast::tools::Hold< ast::Statement > && elseBranch )
                {
                    mElseBranch = std::move( elseBranch );

                    return * this;
                }

                void Try::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Try::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
