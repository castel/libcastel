#pragma once

namespace castel
{

    namespace runtime
    {

        class Class : public runtime::Box
        {

        public:

            runtime::Class::BinaryOperator additionOperator( void ) const
            {
                return mAdditionOperator;
            }

            Class & additionOperator( runtime::Class::BinaryOperator additionOperator )
            {
                mAdditionOperator = additionOperator;

                return * this;
            }

            runtime::Class::BinaryOperator substractionOperator( void ) const
            {
                return mSubstractionOperator;
            }

            Class & substractionOperator( runtime::Class::BinaryOperator substractionOperator )
            {
                mSubstractionOperator = substractionOperator;

                return * this;
            }

            runtime::Class::BinaryOperator multiplicationOperator( void ) const
            {
                return mMultiplicationOperator;
            }

            Class & multiplicationOperator( runtime::Class::BinaryOperator multiplicationOperator )
            {
                mMultiplicationOperator = multiplicationOperator;

                return * this;
            }

            runtime::Class::BinaryOperator divisionOperator( void ) const
            {
                return mDivisionOperator;
            }

            Class & divisionOperator( runtime::Class::BinaryOperator divisionOperator )
            {
                mDivisionOperator = divisionOperator;

                return * this;
            }

        public:

            runtime::Class::RandomOperator callOperator( void ) const
            {
                return mCallOperator;
            }

            Class & callOperator( runtime::Class::RandomOperator callOperator )
            {
                mCallOperator = callOperator;

                return * this;
            }

        private:

            BinaryOperator mAdditionOperator;
            BinaryOperator mSubstractionOperator;
            BinaryOperator mMultiplicationOperator;
            BinaryOperator mDivisionOperator;

            RandomOperator mCallOperator;

        };

    }

}
