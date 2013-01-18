#pragma once

#include <list>
#include <map>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

namespace castel
{

    namespace toolchain
    {

        class Source;

        class Compiler
        {

        public:

            Compiler( void );

        public:

            inline std::list< std::string > const & globals( void ) const;

            inline std::list< std::string > & globals( void );

            inline Compiler & globals( std::list< std::string > const & globals );

        public:

            llvm::Module * build( Source const & source, std::string const & name = "main" );

        private:

            std::list< std::string > mGlobals;

            llvm::LLVMContext mContext;

        };

    }

}

#include "castel/toolchain/Source.hh"

namespace castel
{

    namespace toolchain
    {

        std::list< std::string > const & Compiler::globals( void ) const
        {
            return mGlobals;
        }

        std::list< std::string > & Compiler::globals( void )
        {
            return mGlobals;
        }

        Compiler & Compiler::globals( std::list< std::string > const & globals )
        {
            mGlobals = globals;

            return * this;
        }

    }

}
