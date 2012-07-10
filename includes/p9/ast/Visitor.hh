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

            virtual void visit( BinaryOperator & ) = 0;
            virtual void visit( Number         & ) = 0;

        };

    }

}
