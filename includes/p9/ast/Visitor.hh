#pragma once

#include "p9/ast/Token.hh"

namespace p9
{

    namespace ast
    {

        class Number;

        namespace expr
        {
            class Binary;
        }

        namespace stmt
        {
        }

        class Visitor
        {

        public:

            virtual ~Visitor( void ) {}

        public:

            virtual void visit( ast::expr::Binary & ) = 0;
            virtual void visit( ast::Number       & ) = 0;

        };

    }

}
