#pragma once

#include "castel/ast/Expression.hh"

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

            class Bool : public ast::Expression
            {

            public:

                inline Bool( bool value );

            public:

                inline bool value( void ) const;

                inline Bool & value( bool value );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                bool mValue;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Bool::Bool( bool value )
                : mValue( value )
            {
            }

            bool Bool::value( void ) const
            {
                return mValue;
            }

            Bool & Bool::value( bool value )
            {
                mValue = value;

                return * this;
            }

            void Bool::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
