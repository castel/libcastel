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

        namespace stmt
        {

            namespace ctrl
            {

                class Try : public ast::Statement
                {

                public:

                    inline Try( ast::Statement * tryBranch, ast::Statement * elseBranch );

                public:

                    inline ast::Statement * tryBranch( void ) const;

                    inline Try & tryBranch( ast::Statement * tryBranch );

                    inline ast::Statement * takeTryBranch( void );

                public:

                    inline ast::Statement * elseBranch( void ) const;

                    inline Try & elseBranch( ast::Statement * elseBranch );

                    inline ast::Statement * takeElseBranch( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::unique_ptr< ast::Statement > mTryBranch;
                    std::unique_ptr< ast::Statement > mElseBranch;

                };

            }

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

            namespace ctrl
            {

                Try::Try( ast::Statement * tryBranch, ast::Statement * elseBranch )
                    : mTryBranch( tryBranch )
                    , mElseBranch( elseBranch )
                {
                }

                ast::Statement * Try::tryBranch( void ) const
                {
                    return mTryBranch.get( );
                }

                Try & Try::tryBranch( ast::Statement * tryBranch )
                {
                    mTryBranch.reset( tryBranch );

                    return * this;
                }

                ast::Statement * Try::takeTryBranch( void )
                {
                    return mTryBranch.release( );
                }

                ast::Statement * Try::elseBranch( void ) const
                {
                    return mElseBranch.get( );
                }

                Try & Try::elseBranch( ast::Statement * elseBranch )
                {
                    mElseBranch.reset( elseBranch );

                    return * this;
                }

                ast::Statement * Try::takeElseBranch( void )
                {
                    return mElseBranch.release( );
                }

                void Try::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
