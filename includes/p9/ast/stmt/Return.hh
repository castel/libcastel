#pragma once

#include <memory>

#include "p9/ast/Expression.hh"
#include "p9/ast/Statement.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace ast
    {

        namespace stmt
        {

            class Return : public ast::Statement
            {

            public:

                Return         ( ast::Expression * returnValue = nullptr )
                : mReturnValue ( returnValue )
                {
                }

            public:

                ast::Expression * returnValue( void ) const
                {
                    return mReturnValue.get( );
                }

                Return & returnValue( ast::Expression * returnValue )
                {
                    mReturnValue.reset( returnValue );

                    return *this;
                }

                ast::Expression * takeReturnValue( void )
                {
                    return mReturnValue.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                std::unique_ptr< ast::Expression > mReturnValue;

            };

        }

    }

}
