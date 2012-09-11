#pragma once

#include <new>
#include <limits>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

namespace castel
{

    namespace runtime
    {

        class Number : public runtime::Box
        {

        public:

            typedef double InternalNumber;

        public:

            static Number * create( void )
            {
                return runtime::Number::create( std::numeric_limits< InternalNumber >::quiet_NaN( ) );
            }

            static Number * create( InternalNumber number )
            {
                void * memory = castel_allocate( 1, sizeof( Number ) );
                return new ( memory ) Number( number );
            }

        private:

            Number    ( InternalNumber number )
            : mNumber ( number )
            {
            }

        public:

            InternalNumber number( void ) const
            {
                return mNumber;
            }

            Number & number( InternalNumber number )
            {
                mNumber = number;

                return * this;
            }

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * substractionOperator   ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * multiplicationOperator ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * divisionOperator       ( runtime::Box *** environment, runtime::Box * operand );
            virtual runtime::Box * moduloOperator         ( runtime::Box *** environment, runtime::Box * operand );

            virtual runtime::Box * callOperator ( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

        private:

            InternalNumber mNumber;

        };

    }

}
