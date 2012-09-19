#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class List : public ast::Expression
            {

            public:

                class Item;

            public:

                List     ( ast::expr::List::Item * items = nullptr )
                : mItems ( items )
                {
                }

            public:

                ast::expr::List::Item * items( void ) const
                {
                    return mItems.get( );
                }

                List & items( ast::expr::List::Item * items )
                {
                    mItems.reset( items );

                    return * this;
                }

                ast::expr::List::Item * takeItems( void )
                {
                    return mItems.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                std::unique_ptr< ast::expr::List::Item > mItems;

            };

        }

    }

}

#include "castel/ast/expr/List/Item.hh"
