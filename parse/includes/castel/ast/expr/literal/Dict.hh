#pragma once

#include <string>
#include <utility>

#include "castel/ast/tools/Hold.hh"
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

        namespace expr
        {

            namespace literal
            {

                class Dict : public ast::Expression
                {

                public:

                    class Item;

                public:

                    inline Dict( void );

                    inline Dict( ast::tools::List< ast::expr::literal::Dict::Item > && items );

                public:

                    inline ast::tools::List< ast::expr::literal::Dict::Item > const & items( void ) const;

                    inline ast::tools::List< ast::expr::literal::Dict::Item > & items( void );

                    inline Dict & items( ast::tools::List< ast::expr::literal::Dict::Item > && items );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::List< ast::expr::literal::Dict::Item > mItems;

                };

                class Dict::Item
                {

                public:

                    inline Item( std::string const & name, ast::tools::Hold< ast::Expression > && value );

                public:

                    inline std::string const & name( void ) const;

                    inline Item & name( std::string const & name );

                public:

                    inline ast::tools::Hold< ast::Expression > const & value( void ) const;

                    inline ast::tools::Hold< ast::Expression > & value( void );

                    inline Item & value( ast::tools::Hold< ast::Expression > && value );

                private:

                    std::string mName;

                    ast::tools::Hold< ast::Expression > mValue;

                };

            }

        }

    }

}

#include <string>

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

                Dict::Item::Item( std::string const & name, ast::tools::Hold< ast::Expression > && value )
                    : mName( name )
                    , mValue( std::move( value ) )
                {
                }

                std::string const & Dict::Item::name( void ) const
                {
                    return mName;
                }

                Dict::Item & Dict::Item::name( std::string const & name )
                {
                    mName = name;

                    return * this;
                }

                ast::tools::Hold< ast::Expression > const & Dict::Item::value( void ) const
                {
                    return mValue;
                }

                ast::tools::Hold< ast::Expression > & Dict::Item::value( void )
                {
                    return mValue;
                }

                Dict::Item & Dict::Item::value( ast::tools::Hold< ast::Expression > && value )
                {
                    mValue = std::move( value );

                    return * this;
                }

                Dict::Dict( void )
                    : mItems( )
                {
                }

                Dict::Dict( ast::tools::List< ast::expr::literal::Dict::Item > && items )
                    : mItems( std::move( items ) )
                {
                }

                ast::tools::List< ast::expr::literal::Dict::Item > const & Dict::items( void ) const
                {
                    return mItems;
                }

                ast::tools::List< ast::expr::literal::Dict::Item > & Dict::items( void )
                {
                    return mItems;
                }

                Dict & Dict::items( ast::tools::List< ast::expr::literal::Dict::Item > && items )
                {
                    mItems = std::move( items );

                    return * this;
                }

                void Dict::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void Dict::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
