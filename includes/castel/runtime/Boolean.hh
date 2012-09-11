#pragma once

#include <new>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

namespace castel
{

    namespace runtime
    {

        class Boolean : public runtime::Box
        {

        public:

            typedef bool InternalBoolean;

        public:

            static Boolean * create( InternalBoolean boolean )
            {
                void * memory = castel_allocate( 1, sizeof( Boolean ) );
                return new ( memory ) Boolean( boolean );
            }

        private:

            Boolean    ( InternalBoolean boolean )
            : mBoolean ( boolean )
            {
            }

        public:

            InternalBoolean boolean( void ) const
            {
                return mBoolean;
            }

            Boolean & boolean( InternalBoolean boolean )
            {
                mBoolean = boolean;

                return * this;
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

            virtual bool booleanOperator ( void );

        private:

            InternalBoolean mBoolean;

        };

    }

}
