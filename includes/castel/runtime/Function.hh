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

            typedef runtime::Box * ( * InternalFunction )( runtime::Box *** environmentTable, unsigned int argc, runtime::Box ** argv );

        public:

            static Function * create( InternalFunction function, runtime::Box *** environmentTable )
            {
                void * memory = castel_allocate( 1, sizeof( Function ) );
                return new ( memory ) Function( function, environmentTable );
            }

        private:

            Function            ( InternalFunction function, runtime::Box *** environmentTable )
            : mFunction         ( function         )
            , mEnvironmentTable ( environmentTable )
            {
            }

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box * operand );
            virtual runtime::Box * substractionOperator   ( runtime::Box * operand );
            virtual runtime::Box * multiplicationOperator ( runtime::Box * operand );
            virtual runtime::Box * divisionOperator       ( runtime::Box * operand );
            virtual runtime::Box * moduloOperator         ( runtime::Box * operand );

            virtual runtime::Box * callOperator ( unsigned int argc, runtime::Box ** argv );

        private:

            InternalFunction mFunction;
            runtime::Box *** mEnvironmentTable;

        };

    }

}
