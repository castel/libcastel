#pragma once

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

    }

    namespace utils
    {

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
