#pragma once

#include <memory>
#include <string>

#include "castel/ast/tools/List.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

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

                    inline Function( ast::tools::List< ast::expr::literal::Function::Parameter > && parameters, ast::tools::List< ast::Statement > && statements );

                public:

                    inline ast::tools::List< ast::expr::literal::Function::Parameter > const & parameters( void ) const;

                    inline ast::tools::List< ast::expr::literal::Function::Parameter > & parameters( void );

                    inline Function & parameters( ast::tools::List< ast::expr::literal::Function::Parameter > && parameters );

                public:

                    inline ast::tools::List< ast::Statement > const & statements( void ) const;

                    inline ast::tools::List< ast::Statement > & statements( void );

                    inline Function & statements( ast::tools::List< ast::Statement > && statements );

                public:

                    inline virtual void accept( ast::tools::ConstVisitor & visitor ) const;

                    inline virtual void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::List< ast::expr::literal::Function::Parameter > mParameters;

                    ast::tools::List< ast::Statement > mStatements;

                };

                class Function::Parameter
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

#include "castel/ast/tools/ConstVisitor.hh"
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

                Function::Function( ast::tools::List< ast::expr::literal::Function::Parameter > && parameters, ast::tools::List< ast::Statement > && statements )
                    : mParameters( std::move( parameters ) )
                    , mStatements( std::move( statements ) )
                {
                }

                ast::tools::List< ast::expr::literal::Function::Parameter > const & Function::parameters( void ) const
                {
                    return mParameters;
                }

                ast::tools::List< ast::expr::literal::Function::Parameter > & Function::parameters( void )
                {
                    return mParameters;
                }

                Function & Function::parameters( ast::tools::List< ast::expr::literal::Function::Parameter > && parameters )
                {
                    mParameters = std::move( parameters );

                    return * this;
                }

                ast::tools::List< ast::Statement > const & Function::statements( void ) const
                {
                    return mStatements;
                }

                ast::tools::List< ast::Statement > & Function::statements( void )
                {
                    return mStatements;
                }

                Function & Function::statements( ast::tools::List< ast::Statement > && statements )
                {
                    mStatements = std::move( statements );

                    return * this;
                }

                void Function::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Function::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
