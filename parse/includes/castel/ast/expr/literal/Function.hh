#pragma once

#include <memory>
#include <string>

#include "castel/ast/tools/Linked.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        class Statement;

        namespace expr
        {

            namespace literal
            {

                class Function : public ast::Expression
                {

                public:

                    class Parameter;

                public:

                    inline Function( ast::expr::literal::Function::Parameter * parameters, ast::Statement * statements );

                public:

                    inline ast::expr::literal::Function::Parameter * parameters( void ) const;

                    inline Function & parameters( ast::expr::literal::Function::Parameter * parameters );

                    inline ast::expr::literal::Function::Parameter * takeParameters( void );

                public:

                    inline ast::Statement * statements( void ) const;

                    inline Function & statements( ast::Statement * statements );

                    inline ast::Statement * takeStatements( void );

                public:

                    inline virtual void accept( ast::tools::Visitor & visitor );

                private:

                    std::unique_ptr< ast::expr::literal::Function::Parameter > mParameters;
                    std::unique_ptr< ast::Statement > mStatements;

                };

                class Function::Parameter : public ast::tools::Linked< Function::Parameter >
                {

                public:

                    inline Parameter( std::string const & name = "" );

                public:

                    inline std::string const & name( void ) const;

                    inline Parameter & name( std::string const & name );

                private:

                    std::string mName;

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

        namespace expr
        {

            namespace literal
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

                Function::Function( ast::expr::literal::Function::Parameter * parameters, ast::Statement * statements )
                    : mParameters( parameters )
                    , mStatements( statements )
                {
                }

                ast::expr::literal::Function::Parameter * Function::parameters( void ) const
                {
                    return mParameters.get( );
                }

                Function & Function::parameters( ast::expr::literal::Function::Parameter * parameters )
                {
                    mParameters.reset( parameters );

                    return * this;
                }

                ast::expr::literal::Function::Parameter * Function::takeParameters( void )
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

}
