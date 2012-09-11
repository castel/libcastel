#pragma once

namespace castel
{

    namespace runtime
    {

        class Box
        {

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * substractionOperator   ( runtime::Box * operand ) = 0;
            virtual runtime::Box * multiplicationOperator ( runtime::Box * operand ) = 0;
            virtual runtime::Box * divisionOperator       ( runtime::Box * operand ) = 0;
            virtual runtime::Box * moduloOperator         ( runtime::Box * operand ) = 0;

            virtual runtime::Box * callOperator ( unsigned int argc, runtime::Box ** argv ) = 0;

        };

    }

}
