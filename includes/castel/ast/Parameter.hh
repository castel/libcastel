#pragma once

#include <string>

#include "castel/utils/Linked.hh"

namespace castel
{

    namespace ast
    {

        /**
         * Represents a function parameter in the AST.
         *
         * For example :
         *     (function a, b, c: [...]
         *               ^  ^  ^
         *               \__\__\__ a, b and c are a list of Parameters
         *
         * This node cannot be traversed by the ASTVisitor.
         */

        class Parameter : public utils::Linked< Parameter >
        {

        public:

            /**
             * Constructs a Parameter instance.
             */

            inline Parameter( std::string const & name = "" );

        public:

            /**
             * @return Parameter name
             */

            inline std::string const & name( void ) const;

            /**
             * @param name Parameter name
             */

            inline Parameter & name( std::string const & name );

        private:

            std::string mName;

        };

    }

}

namespace castel
{

    namespace ast
    {

        Parameter::Parameter( std::string const & name )
            : mName( name )
        {
        }

        std::string const & Parameter::name( void ) const
        {
            return mName;
        }

        Parameter & Parameter::name( std::string const & name )
        {
            mName = name;

            return * this;
        }

    }

}
