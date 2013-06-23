#pragma once

#include <string>
#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/tools/List.hh"
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

        class Expression;

        namespace stmt
        {

            namespace decl
            {

                class Variables : public ast::Statement
                {

                public:

                    class Item;

                public:

                    inline Variables( void );

                    inline Variables( ast::tools::List< ast::stmt::decl::Variables::Item > && variables );

                public:

                    inline ast::tools::List< ast::stmt::decl::Variables::Item > const & variables( void ) const;

                    inline ast::tools::List< ast::stmt::decl::Variables::Item > & variables( void );

                    inline Variables & variables( ast::tools::List< ast::stmt::decl::Variables::Item > && variables );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::List< ast::stmt::decl::Variables::Item > mVariables;

                };

                class Variables::Item
                {

                public:

                    inline Item( std::string const & name );

                    inline Item( std::string const & name, ast::tools::Hold< ast::Expression > && initializer );

                public:

                    inline std::string const & name( void ) const;

                    inline Item & name( std::string const & name );

                public:

                    inline ast::tools::Hold< ast::Expression > const & initializer( void ) const;

                    inline ast::tools::Hold< ast::Expression > & initializer( void );

                    inline Item & initializer( ast::tools::Hold< ast::Expression > && initializer );

                private:

                    std::string mName;

                    ast::tools::Hold< ast::Expression > mInitializer;

                };

            }

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                Variables::Item::Item( std::string const & name )
                    : mName( name )
                {
                }

                Variables::Item::Item( std::string const & name, ast::tools::Hold< ast::Expression > && initializer )
                    : mName( name )
                    , mInitializer( std::move( initializer ) )
                {
                }

                std::string const & Variables::Item::name( void ) const
                {
                    return mName;
                }

                Variables::Item & Variables::Item::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::tools::Hold< ast::Expression > const & Variables::Item::initializer( void ) const
                {
                    return mInitializer;
                }

                ast::tools::Hold< ast::Expression > & Variables::Item::initializer( void )
                {
                    return mInitializer;
                }

                Variables::Item & Variables::Item::initializer( ast::tools::Hold< ast::Expression > && initializer )
                {
                    mInitializer = std::move( initializer );

                    return * this;
                }

                Variables::Variables( void )
                    : mVariables( )
                {
                }

                Variables::Variables( ast::tools::List< ast::stmt::decl::Variables::Item > && variables )
                    : mVariables( std::move( variables ) )
                {
                }

                ast::tools::List< ast::stmt::decl::Variables::Item > const & Variables::variables( void ) const
                {
                    return mVariables;
                }

                ast::tools::List< ast::stmt::decl::Variables::Item > & Variables::variables( void )
                {
                    return mVariables;
                }

                Variables & Variables::variables( ast::tools::List< ast::stmt::decl::Variables::Item > && variables )
                {
                    mVariables = std::move( variables );

                    return * this;
                }

                void Variables::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Variables::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
