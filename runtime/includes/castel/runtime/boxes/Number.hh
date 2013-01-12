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

                virtual bool operatorBool( void );

            public:

                virtual runtime::Box * operatorNumericPostIncrementation( void );

                virtual runtime::Box * operatorNumericPostDecrementation( void );

                virtual runtime::Box * operatorNumericPreIncrementation( void );

                virtual runtime::Box * operatorNumericPreDecrementation( void );

            public:

                virtual runtime::Box * operatorNumericPlus( void );

                virtual runtime::Box * operatorNumericMinus( void );

                virtual runtime::Box * operatorNumericAddition( runtime::Box * operand );

                virtual runtime::Box * operatorNumericSubstraction( runtime::Box * operand );

                virtual runtime::Box * operatorNumericMultiplication( runtime::Box * operand );

                virtual runtime::Box * operatorNumericDivision( runtime::Box * operand );

                virtual runtime::Box * operatorNumericModulo( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorNumericAssignmentAddition( runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentSubstraction( runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentMultiplication( runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentDivision( runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentModulo( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorBinaryNot( void );

                virtual runtime::Box * operatorBinaryAnd( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryOr( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryXOr( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryLShift( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryRShift( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorBinaryAssignmentAnd( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentOr( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentXOr( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentLShift( runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentRShift( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorComparisonLesser( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonGreater( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonLesserOrEqual( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonGreaterOrEqual( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonEqual( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonNotEqual( runtime::Box * operand );

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
