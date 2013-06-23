#pragma once

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        class Token
        {

        public:

            virtual ~Token( void ) {}

        public:

            virtual void accept( ast::tools::ConstVisitor & visitor ) const = 0;

            virtual void accept( ast::tools::Visitor & visitor ) = 0;

        };

    }

}
