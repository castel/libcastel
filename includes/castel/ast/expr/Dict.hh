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

            class Dict : public ast::Expression
            {

            public:

                class Item;

            public:

                Dict     ( ast::expr::Dict::Item * items = nullptr )
                : mItems ( items )
                {
                }

            public:

                ast::expr::Dict::Item * items( void ) const
                {
                    return mItems.get( );
                }

                Dict & items( ast::expr::Dict::Item * items )
                {
                    mItems.reset( items );

                    return * this;
                }

                ast::expr::Dict::Item * takeItems( void )
                {
                    return mItems.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                std::unique_ptr< ast::expr::Dict::Item > mItems;

            };

        }

    }

}

#include "castel/ast/expr/Dict/Item.hh"
