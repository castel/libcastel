#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/ast/Parameter.hh"
#include "castel/ast/Statement.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            /**
             * Represents a function literal in the AST.
             */

            class Function : public ast::Expression
            {

            public:

                /**
                 * Constructs a Function instance.
                 *
                 * It will take ownership of the Parameter and Statement pointers (they will be
                 * destroyed when the Function instance will be destroyed).
                 */

                inline Function( ast::Parameter * parameters = nullptr, ast::Statement * statements = nullptr );

            public:

                /**
                 * @return Function parameter list
                 *
                 * Please note that calling this function will not release parameters from Function
                 * ownership. You should not delete the returned pointer.
                 */

                inline ast::Parameter * parameters( void ) const;

                /**
                 * @param parameters Function parameter list
                 *
                 * Please note that the Function instance will take ownership of the parameters.
                 * If existing, the previous parameters will be destroyed.
                 */

                inline Function & parameters( ast::Parameter * parameters );

                /**
                 * @return Function parameter list
                 *
                 * The pointer will be released from the Function instance. You will be responsible
                 * to release it after usage.
                 */

                inline ast::Parameter * takeParameters( void );

            public:

                /**
                 * @return Function statement list
                 *
                 * Please note that calling this function will not release statements from Function
                 * ownership. You should not delete the returned pointer.
                 */

                inline ast::Statement * statements( void ) const;

                /**
                 * @param statements Function statement list
                 *
                 * Please note that the Function instance will take ownership of the statements.
                 * If existing, the previous statements will be destroyed.
                 */

                inline Function & statements( ast::Statement * statements );

                /**
                 * @return Function statement list
                 *
                 * The pointer will be released from the Function instance. You will be responsible
                 * to release it after usage.
                 */

                inline ast::Statement * takeStatements( void );

            public:

                /**
                 * Calls the ast::expr::Function version of the ASTVisitor's visit method.
                 */

                inline virtual void accept( utils::Visitor & visitor );

            private:

                std::unique_ptr< ast::Parameter > mParameters;
                std::unique_ptr< ast::Statement > mStatements;

            };

        }

    }

}

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Function::Function( ast::Parameter * parameters, ast::Statement * statements )
                : mParameters( parameters )
                , mStatements( statements )
            {
            }

            ast::Parameter * Function::parameters( void ) const
            {
                return mParameters.get( );
            }

            Function & Function::parameters( ast::Parameter * parameters )
            {
                mParameters.reset( parameters );

                return * this;
            }

            ast::Parameter * Function::takeParameters( void )
            {
                return mParameters.release( );
            }

            ast::Statement * Function::statements( void ) const
            {
                return mStatements.get( );
            }

            Function & Function::statements( ast::Statement * statements )
            {
                mStatements.reset( statements );

                return * this;
            }

            ast::Statement * Function::takeStatements( void )
            {
                return mStatements.release( );
            }

            void Function::accept( utils::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
