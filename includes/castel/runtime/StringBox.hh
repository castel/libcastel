#pragma once

#include <cstring>
#include <new>
#include <string>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

namespace castel
{

    namespace runtime
    {

        class StringBox : public runtime::Box
        {

        public:

            static StringBox * create( std::string const & value )
            {
                void * memory = castel_allocate( 1, sizeof( StringBox ) );
                return new ( memory ) StringBox( value );
            }

            static StringBox * create( char const * value, int length = -1, bool copy = true )
            {
                void * memory = castel_allocate( 1, sizeof( StringBox ) );
                return new ( memory ) StringBox( value, length, copy );
            }

        private:

            StringBox ( std::string const & value )
            {
                this->value( value );
            }

            StringBox ( char const * value, int length = -1, bool copy = true )
            {
                this->value( value, length, copy );
            }

        public:

            char const * value( void ) const
            {
                return mValue;
            }

            StringBox & value( std::string const & value )
            {
                this->value( value.c_str( ), value.length( ) );
            }

            StringBox & value( char const * value, int length = -1, bool copy = true );

        public:

            virtual runtime::Box * positiveOperator ( void );
            virtual runtime::Box * negativeOperator ( void );

        public:

            virtual runtime::Box * preIncrementationOperator  ( void );
            virtual runtime::Box * postIncrementationOperator ( void );
            virtual runtime::Box * preDecrementationOperator  ( void );
            virtual runtime::Box * postDecrementationOperator ( void );

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box * operand );
            virtual runtime::Box * substractionOperator   ( runtime::Box * operand );
            virtual runtime::Box * multiplicationOperator ( runtime::Box * operand );
            virtual runtime::Box * divisionOperator       ( runtime::Box * operand );
            virtual runtime::Box * moduloOperator         ( runtime::Box * operand );

        public:

            virtual runtime::Box * lesserOperator         ( runtime::Box * operand );
            virtual runtime::Box * greaterOperator        ( runtime::Box * operand );
            virtual runtime::Box * lesserOrEqualOperator  ( runtime::Box * operand );
            virtual runtime::Box * greaterOrEqualOperator ( runtime::Box * operand );
            virtual runtime::Box * equalOperator          ( runtime::Box * operand );
            virtual runtime::Box * notEqualOperator       ( runtime::Box * operand );

        public:

            virtual runtime::Box * additionAssignmentOperator       ( runtime::Box * operand );
            virtual runtime::Box * substractionAssignmentOperator   ( runtime::Box * operand );
            virtual runtime::Box * multiplicationAssignmentOperator ( runtime::Box * operand );
            virtual runtime::Box * divisionAssignmentOperator       ( runtime::Box * operand );
            virtual runtime::Box * moduloAssignmentOperator         ( runtime::Box * operand );

        public:

            virtual runtime::Box * callOperator      ( unsigned int argc, runtime::Box ** argv );
            virtual runtime::Box * subscriptOperator ( unsigned int argc, runtime::Box ** argv );

        public:

            virtual bool booleanOperator ( void );

        private:

            char const * mValue;
            unsigned int mLength;

        };

    }

}
