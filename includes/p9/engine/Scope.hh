#pragma once

#include <map>
#include <stdexcept>
#include <string>

#include <llvm/Instructions.h>

namespace p9
{

    namespace engine
    {

        class Scope
        {

        public:

            Scope     ( void )
            : mParent ( nullptr )
            {
            }

            Scope     ( Scope & parent )
            : mParent ( &parent )
            {
            }

        public:

            Scope & create( std::string const & name, llvm::Value * value )
            {
                auto it = mVariables.find( name );

                if ( it != mVariables.end( ) )
                    throw std::runtime_error( "Variable redefinition" );

                mVariables[ name ] = value;

                return *this;
            }

        public:

            llvm::Value * get( std::string const & name ) const
            {
                auto it = mVariables.find( name );

                if ( it != mVariables.end( ) )
                    return it->second;

                if ( ! mParent )
                    throw std::runtime_error( "Variable not found" );

                return mParent->get( name );
            }

        private:

            Scope * mParent;

            std::map< std::string, llvm::Value * > mVariables;

        };

    }

}
