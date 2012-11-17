#pragma once

#include <memory>

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

            class Multary : public ast::Expression
            {

            public:

                enum class Operator {

                    New,
                    Call,

                    Subscript,

                };

            public:

                inline Multary( ast::expr::Multary::Operator type, ast::Expression * operands );

            public:

                inline ast::expr::Multary::Operator type( void ) const;

                inline Multary & type( ast::expr::Multary::Operator type );

            public:

                inline ast::Expression * operands( void ) const;

                inline Multary & operands( ast::Expression * operands );

                inline ast::Expression * takeOperands( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Multary::Operator mType;
                std::unique_ptr< ast::Expression > mOperands;

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

            Multary::Multary( ast::expr::Multary::Operator type, ast::Expression * operands )
                : mType( type )
                , mOperands( operands )
            {
            }

            ast::expr::Multary::Operator Multary::type( void ) const
            {
                return mType;
            }

            Multary & Multary::type( ast::expr::Multary::Operator type )
            {
                mType = type;

                return * this;
            }

            ast::Expression * Multary::operands( void ) const
            {
                return mOperands.get( );
            }

            Multary & Multary::operands( ast::Expression * operands )
            {
                mOperands.reset( operands );

                return * this;
            }

            ast::Expression * Multary::takeOperands( void )
            {
                return mOperands.release( );
            }

            void Multary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
