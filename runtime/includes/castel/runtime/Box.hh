#pragma once

#include <map>
#include <string>
#include <utility>

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Class;

        }

        class Attribute;

        class Context;

        class Box
        {

        public:

            enum class PropertyNS {
                Standards,
                Operators,
            };

        public:

            inline Box( void );

        public:

            inline runtime::Context * context( void ) const;

        public:

            inline runtime::boxes::Class * type( void ) const;

            inline Box & type( runtime::boxes::Class * type );

        public:

            inline runtime::Attribute * attribute( std::pair< runtime::Box::PropertyNS, std::string > key ) const;

            inline Box & attribute( std::pair< runtime::Box::PropertyNS, std::string > key, runtime::Attribute * value );

        public:

            virtual bool operatorBool( runtime::Context * context );

        public:

            virtual runtime::Box * operatorNumericPreIncrementation( runtime::Context * context );

            virtual runtime::Box * operatorNumericPreDecrementation( runtime::Context * context );

            virtual runtime::Box * operatorNumericPostIncrementation( runtime::Context * context );

            virtual runtime::Box * operatorNumericPostDecrementation( runtime::Context * context );

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

        public:

            virtual runtime::Box * operatorCall( runtime::Context * context, unsigned int argc, runtime::Box ** argv );

            virtual runtime::Box * operatorSubscript( runtime::Context * context, unsigned int argc, runtime::Box ** argv );

        public:

            runtime::Context * mContext;

            runtime::boxes::Class * mType;

            std::map< std::pair< runtime::Box::PropertyNS, std::string >, runtime::Attribute * > mAttributes;

        };

    }

}

#include <string>
#include <utility>

#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Attribute.hh"
#include "castel/runtime/Context.hh"

namespace castel
{

    namespace runtime
    {

        Box::Box( void )
        {
        }

        runtime::boxes::Class * Box::type( void ) const
        {
            return mType;
        }

        Box & Box::type( runtime::boxes::Class * type )
        {
            mType = type;

            return * this;
        }

        runtime::Attribute * Box::attribute( std::pair< runtime::Box::PropertyNS, std::string > key ) const
        {
            auto attributeIterator = mAttributes.find( key );

            return attributeIterator != mAttributes.end( ) ? attributeIterator->second : nullptr;
        }

        Box & Box::attribute( std::pair< runtime::Box::PropertyNS, std::string > key, runtime::Attribute * attribute )
        {
            mAttributes[ key ] = attribute;

            return * this;
        }

    }

}
