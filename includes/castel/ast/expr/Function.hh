#pragma once

#include <memory>
#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        class Statement;

        namespace expr
        {

            namespace tools
            {

                class Visitor;

            }

            /**
             * Represents a function literal in the AST.
             */

            class Function : public ast::Expression
            {

            public:

                class Parameter;

            public:

                /**
                 * Constructs a Function instance.
                 *
                 * It will take ownership of the Parameter and Statement pointers (they will be
                 * destroyed when the Function instance will be destroyed).
                 */

                inline Function( ast::expr::Function::Parameter * parameters, ast::Statement * statements );

            public:

                /**
                 * @return Function parameter list
                 *
                 * Please note that calling this function will not release parameters from Function
                 * ownership. You should not delete the returned pointer.
                 */

                inline ast::expr::Function::Parameter * parameters( void ) const;

                /**
                 * @param parameters Function parameter list
                 *
                 * Please note that the Function instance will take ownership of the parameters.
                 * If existing, the previous parameters will be destroyed.
                 */

                inline Function & parameters( ast::expr::Function::Parameter * parameters );

                /**
                 * @return Function parameter list
                 *
                 * The pointer will be released from the Function instance. You will be responsible
                 * to release it after usage.
                 */

                inline ast::expr::Function::Parameter * takeParameters( void );

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

                inline virtual void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::expr::Function::Parameter > mParameters;
                std::unique_ptr< ast::Statement > mStatements;

            };

            /**
             * Represents a function parameter in the AST.
             *
             * For example :
             *     (function a, b, c: [...]
             *               ^  ^  ^
             *               \__\__\__ a, b and c are a list of Parameters
             *
             * This node cannot be traversed by the ASTVisitor.
             */

            class Function::Parameter : public utils::Linked< Function::Parameter >
            {

            public:

                /**
                 * Constructs a Parameter instance.
                 */

                inline Parameter( std::string const & name = "" );

            public:

                /**
                 * @return Parameter name
                 */

                inline std::string const & name( void ) const;

                /**
                 * @param name Parameter name
                 */

                inline Parameter & name( std::string const & name );

            private:

                std::string mName;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Function::Parameter::Parameter( std::string const & name )
                : mName( name )
            {
            }

            std::string const & Function::Parameter::name( void ) const
            {
                return mName;
            }

            Function::Parameter & Function::Parameter::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            Function::Function( ast::expr::Function::Parameter * parameters, ast::Statement * statements )
                : mParameters( parameters )
                , mStatements( statements )
            {
            }

            ast::expr::Function::Parameter * Function::parameters( void ) const
            {
                return mParameters.get( );
            }

            Function & Function::parameters( ast::expr::Function::Parameter * parameters )
            {
                mParameters.reset( parameters );

                return * this;
            }

            ast::expr::Function::Parameter * Function::takeParameters( void )
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

            void Function::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
