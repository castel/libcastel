#pragma once

#include <memory>

#include "p9/ast/Expression.hh"
#include "p9/ast/Statement.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace ast
    {

        namespace expr
        {

            class Function : public ast::Expression
            {

            public:

                class Parameter;

            public:

                Function( ast::expr::Function::Parameter * parameters = nullptr, ast::Statement * statements = nullptr )
                : mParameters( parameters )
                , mStatements( statements )
                {
                }

            public:

                ast::expr::Function::Parameter * parameters( void ) const
                {
                    return mParameters.get( );
                }

                Function & parameters( ast::expr::Function::Parameter * parameters )
                {
                    mParameters.reset( parameters );

                    return *this;
                }

                ast::expr::Function::Parameter * takeParameters( void )
                {
                    return mParameters.release( );
                }

            public:

                ast::Statement * statements( void ) const
                {
                    return mStatements.get( );
                }

                Function & statements( ast::Statement * statements )
                {
                    mStatements.reset( statements );

                    return *this;
                }

                ast::Statement * takeStatements( void )
                {
                    return mStatements.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

                private:

                std::unique_ptr< ast::expr::Function::Parameter > mParameters;
                std::unique_ptr< ast::Statement > mStatements;

            };

        }

    }

}

#include "p9/ast/expr/Function/Parameter.hh"
