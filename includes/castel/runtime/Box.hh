#pragma once

namespace castel
{

    namespace runtime
    {

        class Box
        {

        public:

            virtual runtime::Box * positiveOperator ( void ) = 0;
            virtual runtime::Box * negativeOperator ( void ) = 0;

        public:

            virtual runtime::Box * preIncrementationOperator  ( void ) = 0;
            virtual runtime::Box * postIncrementationOperator ( void ) = 0;
            virtual runtime::Box * preDecrementationOperator  ( void ) = 0;
            virtual runtime::Box * postDecrementationOperator ( void ) = 0;

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * substractionOperator   ( runtime::Box * operand ) = 0;
            virtual runtime::Box * multiplicationOperator ( runtime::Box * operand ) = 0;
            virtual runtime::Box * divisionOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * moduloOperator         ( runtime::Box * operand ) = 0;

        public:

            virtual runtime::Box * lesserOperator         ( runtime::Box * operand ) = 0;
            virtual runtime::Box * greaterOperator        ( runtime::Box * operand ) = 0;
            virtual runtime::Box * lesserOrEqualOperator  ( runtime::Box * operand ) = 0;
            virtual runtime::Box * greaterOrEqualOperator ( runtime::Box * operand ) = 0;
            virtual runtime::Box * equalOperator          ( runtime::Box * operand ) = 0;
            virtual runtime::Box * notEqualOperator       ( runtime::Box * operand ) = 0;

        public:

            virtual runtime::Box * additionAssignmentOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * substractionAssignmentOperator   ( runtime::Box * operand ) = 0;
            virtual runtime::Box * multiplicationAssignmentOperator ( runtime::Box * operand ) = 0;
            virtual runtime::Box * divisionAssignmentOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * moduloAssignmentOperator         ( runtime::Box * operand ) = 0;

        public:

            virtual runtime::Box * callOperator      ( unsigned int argc, runtime::Box ** argv ) = 0;
            virtual runtime::Box * subscriptOperator ( unsigned int argc, runtime::Box ** argv ) = 0;

        public:

            virtual bool booleanOperator ( void ) = 0;

        };

    }

}
