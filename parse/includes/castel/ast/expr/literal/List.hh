#pragma once

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

                class List : public ast::Expression
                {

                public:

                    class Item;

                public:

                    inline List( void );

                    inline List( ast::tools::List< ast::expr::literal::List::Item > && items );

                public:

                    inline ast::tools::List< ast::expr::literal::List::Item > const & items( void ) const;

                    inline ast::tools::List< ast::expr::literal::List::Item > & items( void );

                    inline List & items( ast::tools::List< ast::expr::literal::List::Item > && items );

                public:

                    virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    ast::tools::List< ast::expr::literal::List::Item > mItems;

                };

                class List::Item
                {

                public:

                    inline Item( ast::tools::Hold< ast::Expression > && value );

                public:

                    inline ast::tools::Hold< ast::Expression > const & value( void ) const;

                    inline ast::tools::Hold< ast::Expression > & value( void );

                    inline Item & value( ast::tools::Hold< ast::Expression > && value );

                private:

                    ast::tools::Hold< ast::Expression > mValue;

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

                List::Item::Item( ast::tools::Hold< ast::Expression > && value )
                    : mValue( std::move( value ) )
                {
                }

                ast::tools::Hold< ast::Expression > const & List::Item::value( void ) const
                {
                    return mValue;
                }

                ast::tools::Hold< ast::Expression > & List::Item::value( void )
                {
                    return mValue;
                }

                List::Item & List::Item::value( ast::tools::Hold< ast::Expression > && value )
                {
                    mValue = std::move( value );

                    return * this;
                }

                List::List( void )
                    : mItems( )
                {
                }

                List::List( ast::tools::List< ast::expr::literal::List::Item > && items )
                    : mItems( std::move( items ) )
                {
                }

                ast::tools::List< ast::expr::literal::List::Item > const & List::items( void ) const
                {
                    return mItems;
                }

                ast::tools::List< ast::expr::literal::List::Item > & List::items( void )
                {
                    return mItems;
                }

                List & List::items( ast::tools::List< ast::expr::literal::List::Item > && items )
                {
                    mItems = std::move( items );

                    return * this;
                }

                void List::accept( ast::tools::ConstVisitor & visitor ) const
                {
                    visitor.visit( * this );
                }

                void List::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
