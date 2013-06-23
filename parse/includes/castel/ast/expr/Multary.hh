#pragma once

#include <utility>

#include "castel/ast/Expression.hh"
#include "castel/ast/tools/List.hh"

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

            class Multary : public ast::Expression
            {

            public:

                enum class Operator {

                    New,
                    Call,

                    Subscript,

                    Require,

                };

            public:

                inline Multary( ast::expr::Multary::Operator type );

                inline Multary( ast::expr::Multary::Operator type, ast::tools::List< ast::Expression > && container );

            public:

                inline ast::expr::Multary::Operator type( void ) const;

                inline Multary & type( ast::expr::Multary::Operator type );

            public:

                inline ast::tools::List< ast::Expression > const & operands( void ) const;

                inline ast::tools::List< ast::Expression > & operands( void );

                inline Multary & operands( ast::tools::List< ast::Expression > && operands );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Multary::Operator mType;

                ast::tools::List< ast::Expression > mOperands;

            };

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

            Multary::Multary( ast::expr::Multary::Operator type )
                : mType( type )
                , mOperands( )
            {
            }

            Multary::Multary( ast::expr::Multary::Operator type, ast::tools::List< ast::Expression > && operands )
                : mType( type )
                , mOperands( std::move( operands ) )
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

            ast::tools::List< ast::Expression > const & Multary::operands( void ) const
            {
                return mOperands;
            }

            ast::tools::List< ast::Expression > & Multary::operands( void )
            {
                return mOperands;
            }

            Multary & Multary::operands( ast::tools::List< ast::Expression > && operands )
            {
                mOperands = std::move( operands );

                return * this;
            }

            void Multary::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Multary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
