#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Number : public runtime::Box
            {

            public:

                inline Number( double value );

            public:

                inline double value( void ) const;

                inline Number & value( double value );

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorPostIncrementation( void );

                virtual runtime::Box * operatorPostDecrementation( void );

                virtual runtime::Box * operatorPreIncrementation( void );

                virtual runtime::Box * operatorPreDecrementation( void );

            public:

                virtual runtime::Box * operatorPositive( void );

                virtual runtime::Box * operatorNegative( void );

            public:

                virtual runtime::Box * operatorAddition( runtime::Box * operand );

                virtual runtime::Box * operatorSubstraction( runtime::Box * operand );

                virtual runtime::Box * operatorMultiplication( runtime::Box * operand );

                virtual runtime::Box * operatorDivision( runtime::Box * operand );

                virtual runtime::Box * operatorModulo( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorBitwiseNot( void );

                virtual runtime::Box * operatorBitwiseAnd( runtime::Box * operand );

                virtual runtime::Box * operatorBitwiseOr( runtime::Box * operand );

                virtual runtime::Box * operatorBitwiseXOr( runtime::Box * operand );

                virtual runtime::Box * operatorLeftShift( runtime::Box * operand );

                virtual runtime::Box * operatorRightShift( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorLesser( runtime::Box * operand );

                virtual runtime::Box * operatorGreater( runtime::Box * operand );

                virtual runtime::Box * operatorLesserOrEqual( runtime::Box * operand );

                virtual runtime::Box * operatorGreaterOrEqual( runtime::Box * operand );

                virtual runtime::Box * operatorEqual( runtime::Box * operand );

                virtual runtime::Box * operatorNotEqual( runtime::Box * operand );

            private:

                double mValue;

            };

        }

    }

}

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Number::Number( double value )
                : Box( )
                , mValue( value )
            {
            }

            double Number::value( void ) const
            {
                return mValue;
            }

            Number & Number::value( double value )
            {
                mValue = value;

                return * this;
            }

        }

    }

}
