#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Number : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Number( double value );

            public:

                inline double value( void ) const;

                inline Number & value( double value );

            public:

                virtual bool operatorBool( runtime::Context * context );

            public:

                virtual runtime::Box * operatorNumericPostIncrementation( runtime::Context * context );

                virtual runtime::Box * operatorNumericPostDecrementation( runtime::Context * context );

                virtual runtime::Box * operatorNumericPreIncrementation( runtime::Context * context );

                virtual runtime::Box * operatorNumericPreDecrementation( runtime::Context * context );

            public:

                virtual runtime::Box * operatorNumericPlus( runtime::Context * context );

                virtual runtime::Box * operatorNumericMinus( runtime::Context * context );

                virtual runtime::Box * operatorNumericAddition( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericSubstraction( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericMultiplication( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericDivision( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericModulo( runtime::Context * context, runtime::Box * operand );

            public:

                virtual runtime::Box * operatorNumericAssignmentAddition( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentSubstraction( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentMultiplication( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentDivision( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorNumericAssignmentModulo( runtime::Context * context, runtime::Box * operand );

            public:

                virtual runtime::Box * operatorBinaryNot( runtime::Context * context );

                virtual runtime::Box * operatorBinaryAnd( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryOr( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryXOr( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryLShift( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryRShift( runtime::Context * context, runtime::Box * operand );

            public:

                virtual runtime::Box * operatorBinaryAssignmentAnd( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentOr( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentXOr( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentLShift( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorBinaryAssignmentRShift( runtime::Context * context, runtime::Box * operand );

            public:

                virtual runtime::Box * operatorComparisonLesser( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonGreater( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonLesserOrEqual( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonGreaterOrEqual( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonEqual( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonNotEqual( runtime::Context * context, runtime::Box * operand );

            private:

                double mValue;

            };

        }

    }

}

#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

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
