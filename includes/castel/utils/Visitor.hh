#pragma once

namespace castel
{

    namespace ast
    {

        namespace expr
        {
            class Binary;
            class Call;
            class Function;
            class Number;
            class Variable;
        }

        namespace stmt
        {
            namespace decl
            {
                class Variables;
            }

            class Expression;
            class If;
            class Return;
        }

    }

    namespace utils
    {

        class Visitor
        {

        public:

            virtual ~Visitor( void ) {}

        public:

            virtual void visit( ast::expr::Binary          & ) = 0;
            virtual void visit( ast::expr::Call            & ) = 0;
            virtual void visit( ast::expr::Function        & ) = 0;
            virtual void visit( ast::expr::Number          & ) = 0;
            virtual void visit( ast::expr::Variable        & ) = 0;

            virtual void visit( ast::stmt::decl::Variables & ) = 0;
            virtual void visit( ast::stmt::Expression      & ) = 0;
            virtual void visit( ast::stmt::If              & ) = 0;
            virtual void visit( ast::stmt::Return          & ) = 0;

        };

    }

}
