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

                    inline Try( ast::Statement * tryBranch, ast::Statement * elsebranch );

                public:

                    inline ast::Statement * tryBranch( void ) const;

                    inline Try & tryBranch( ast::Statement * tryBranch );

                    inline ast::Statement * takeTryBranch( void );

                public:

                    inline ast::Statement * elsebranch( void ) const;

                    inline Try & elsebranch( ast::Statement * elsebranch );

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

                Try::Try( ast::Statement * tryBranch, ast::Statement * elsebranch )
                    : mTryBranch( tryBranch )
                    , mElseBranch( elsebranch )
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

                ast::Statement * Try::elsebranch( void ) const
                {
                    return mElseBranch.get( );
                }

                Try & Try::elsebranch( ast::Statement * elsebranch )
                {
                    mElseBranch.reset( elsebranch );

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
