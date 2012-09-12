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

            static Function * create( runtime::Box *** environmentTable, InternalFunction function, unsigned int arity )
            {
                void * memory = castel_allocate( 1, sizeof( Function ) );
                return new ( memory ) Function( environmentTable, function, arity );
            }

        private:

            Function            ( runtime::Box *** environmentTable, InternalFunction function, unsigned int arity )
            : mEnvironmentTable ( environmentTable )
            , mFunction         ( function         )
            , mArity            ( arity            )
            {
            }

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box * operand );
            virtual runtime::Box * substractionOperator   ( runtime::Box * operand );
            virtual runtime::Box * multiplicationOperator ( runtime::Box * operand );
            virtual runtime::Box * divisionOperator       ( runtime::Box * operand );
            virtual runtime::Box * moduloOperator         ( runtime::Box * operand );

        public:

            virtual runtime::Box * callOperator ( unsigned int argc, runtime::Box ** argv );

        public:

            virtual bool booleanOperator( void );

        private:

            runtime::Box *** mEnvironmentTable;

            InternalFunction mFunction;
            unsigned int     mArity;

        };

    }

}
