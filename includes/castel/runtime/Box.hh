#pragma once

namespace castel
{

    namespace runtime
    {

        class Box
        {

        public:

            virtual runtime::Box * additionOperator       ( runtime::Box *** environment, runtime::Box * operand ) = 0;
            virtual runtime::Box * substractionOperator   ( runtime::Box *** environment, runtime::Box * operand ) = 0;
            virtual runtime::Box * multiplicationOperator ( runtime::Box *** environment, runtime::Box * operand ) = 0;
            virtual runtime::Box * divisionOperator       ( runtime::Box *** environment, runtime::Box * operand ) = 0;
            virtual runtime::Box * moduloOperator         ( runtime::Box *** environment, runtime::Box * operand ) = 0;

            virtual runtime::Box * callOperator ( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv ) = 0;

        };

    }

}
