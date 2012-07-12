#pragma once

#include "p9/ast/Token.hh"

namespace p9
{

    namespace ast
    {

        class BinaryOperator;
        class Number;

        class Visitor
        {

        public:

            virtual ~Visitor( void ) {}

        public:

            virtual void visit( ast::BinaryOperator & ) = 0;
            virtual void visit( ast::Number         & ) = 0;

        };

    }

}
