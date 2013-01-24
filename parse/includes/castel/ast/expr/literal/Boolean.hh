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

                class Boolean : public ast::Expression
                {

                public:

                    inline Boolean( bool value );

                public:

                    inline bool value( void ) const;

                    inline Boolean & value( bool value );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                private:

                    bool mValue;

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

                Boolean::Boolean( bool value )
                    : mValue( value )
                {
                }

                bool Boolean::value( void ) const
                {
                    return mValue;
                }

                Boolean & Boolean::value( bool value )
                {
                    mValue = value;

                    return * this;
                }

                void Boolean::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
