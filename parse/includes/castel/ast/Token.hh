#pragma once

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        class Token
        {

        public:

            virtual ~Token( void ) {}

        public:

            virtual void accept( ast::tools::Visitor & visitor ) = 0;

        };

    }

}
