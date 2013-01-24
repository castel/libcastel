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

                class Class;

            }

        }

        namespace stmt
        {

            namespace decl
            {

                class Class : public ast::Statement
                {

                public:

                    inline Class( std::string const & name, ast::expr::literal::Class * literal = nullptr );

                public:

                    inline std::string const & name( void ) const;

                    inline Class & name( std::string const & name );

                public:

                    inline ast::expr::literal::Class * literal( void ) const;

                    inline Class & literal( ast::expr::literal::Class * literal );

                    inline ast::expr::literal::Class * takeLiteral( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    std::string mName;

                    std::unique_ptr< ast::expr::literal::Class > mLiteral;

                };

            }

        }

    }

}

#include "castel/ast/expr/literal/Class.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                Class::Class( std::string const & name, ast::expr::literal::Class * literal )
                    : mName( name )
                    , mLiteral( literal )
                {
                }

                std::string const & Class::name( void ) const
                {
                    return mName;
                }

                Class & Class::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::expr::literal::Class * Class::literal( void ) const
                {
                    return mLiteral.get( );
                }

                Class & Class::literal( ast::expr::literal::Class * literal )
                {
                    mLiteral.reset( literal );

                    return * this;
                }

                ast::expr::literal::Class * Class::takeLiteral( void )
                {
                    return mLiteral.release( );
                }

                void Class::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
