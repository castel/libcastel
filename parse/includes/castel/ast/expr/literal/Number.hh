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

            namespace literal
            {

                class Number : public ast::Expression
                {

                public:

                    using DataType = double;

                public:

                    inline Number( DataType value );

                public:

                    inline DataType value( void ) const;

                    inline Number & value( DataType value );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    DataType mValue;

                };

            }

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

            namespace literal
            {

                Number::Number( ast::expr::literal::Number::DataType value )
                    : mValue( value )
                {
                }

                ast::expr::literal::Number::DataType Number::value( void ) const
                {
                    return mValue;
                }

                Number & Number::value( ast::expr::literal::Number::DataType value )
                {
                    mValue = value;

                    return * this;
                }

                void Number::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
