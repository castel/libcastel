#pragma once

#include <memory>
#include <string>

#include "p9/ast/expr/Function.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/utils/Linked.hh"

namespace p9
{

    namespace ast
    {

        namespace expr
        {

            class Function::Parameter : public utils::Linked< Function::Parameter >
            {

            public:

                Parameter ( std::string const & name )
                : mName   ( name )
                {
                }

                Parameter ( lexer::Lexeme const & lexeme )
                : mName   ( lexeme.as< std::string >( ) )
                {
                }

            public:

                std::string const & name( void ) const
                {
                    return mName;
                }

                Parameter & name( std::string const & name )
                {
                    mName = name;

                    return *this;
                }

            private:

                std::string mName;

            };

        }

    }

}
