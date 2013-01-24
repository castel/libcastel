#pragma once

#include <memory>
#include <string>

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        namespace expr
        {

            namespace literal
            {

                class Function;

            }

        }

        namespace stmt
        {

            namespace decl
            {

                class Function : public ast::Statement
                {

                public:

                    inline Function( std::string const & name, ast::expr::literal::Function * literal = nullptr );

                public:

                    inline std::string const & name( void ) const;

                    inline Function & name( std::string const & name );

                public:

                    inline ast::expr::literal::Function * literal( void ) const;

                    inline Function & literal( ast::expr::literal::Function * literal );

                    inline ast::expr::literal::Function * takeLiteral( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::string mName;

                    std::unique_ptr< ast::expr::literal::Function > mLiteral;

                };

            }

        }

    }

}

#include "castel/ast/expr/literal/Function.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                Function::Function( std::string const & name, ast::expr::literal::Function * literal )
                    : mName( name )
                    , mLiteral( literal )
                {
                }

                std::string const & Function::name( void ) const
                {
                    return mName;
                }

                Function & Function::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::expr::literal::Function * Function::literal( void ) const
                {
                    return mLiteral.get( );
                }

                Function & Function::literal( ast::expr::literal::Function * literal )
                {
                    mLiteral.reset( literal );

                    return * this;
                }

                ast::expr::literal::Function * Function::takeLiteral( void )
                {
                    return mLiteral.release( );
                }

                void Function::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
