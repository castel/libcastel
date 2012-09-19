#pragma once

#include <memory>

#include "castel/ast/expr/List.hh"
#include "castel/ast/Expression.hh"
#include "castel/utils/Linked.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class List::Item : public utils::Linked< List::Item >
            {

            public:

                Item     ( ast::Expression * value )
                : mValue ( value )
                {
                }

            public:

                ast::Expression * value( void ) const
                {
                    return mValue.get( );
                }

                Item & value( ast::Expression * value )
                {
                    mValue.reset( value );

                    return * this;
                }

                ast::Expression * takeValue( void )
                {
                    return mValue.release( );
                }

            private:

                std::unique_ptr< ast::Expression > mValue;

            };

        }

    }

}
