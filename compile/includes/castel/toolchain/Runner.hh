#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/Module.h>

namespace castel
{

    namespace runtime
    {

        class Box;

    }

    namespace toolchain
    {

        class Runner
        {

        private:

            static void staticInitializer( void );

        private:

            static runtime::Box * staticDependencyInitializer( Runner * runner, char const * global );

        public:

            Runner( void );

        public:

            inline std::map< std::string, std::function< runtime::Box * ( void ) > > const & globals( void ) const;

            inline std::map< std::string, std::function< runtime::Box * ( void ) > > & globals( void );

        public:

            runtime::Box * run( llvm::Module * module, std::string const & name = "main" );

        private:

            std::map< std::string, std::function< runtime::Box * ( void ) > > mGlobals;

        };

    }

}

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace toolchain
    {

        std::map< std::string, std::function< runtime::Box * ( void ) > > const & Runner::globals( void ) const
        {
            return mGlobals;
        }

        std::map< std::string, std::function< runtime::Box * ( void ) > > & Runner::globals( void )
        {
            return mGlobals;
        }

    }

}
