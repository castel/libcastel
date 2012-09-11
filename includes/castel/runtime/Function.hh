#pragma once

#include <new>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

namespace castel
{

    namespace runtime
    {

        class Function : public runtime::Box
        {

        public:

            typedef runtime::Box * ( * InternalFunction )( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

        public:

            static Function * create( InternalFunction function )
            {
                void * memory = castel_allocate( 1, sizeof( Function ) );
                return new ( memory ) Function( function );
            }

        private:

            Function    ( InternalFunction function )
            : mFunction ( function )
            {
            }

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * substractionOperator   ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * multiplicationOperator ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * divisionOperator       ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * moduloOperator         ( runtime::Box *** environment, runtime::Box * operand );

            virtual runtime::Box * callOperator ( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

        private:

            InternalFunction mFunction;

        };

    }

}
