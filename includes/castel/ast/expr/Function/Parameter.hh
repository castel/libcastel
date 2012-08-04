#pragma once

#include <memory>
#include <string>

#include "castel/ast/expr/Function.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Linked.hh"

namespace castel
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
