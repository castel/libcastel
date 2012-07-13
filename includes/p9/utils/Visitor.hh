#pragma once

namespace p9
{

    namespace ast
    {

        namespace expr
        {
            class Binary;
            class Number;
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
            virtual void visit( ast::expr::Number & ) = 0;

        };

    }

}
