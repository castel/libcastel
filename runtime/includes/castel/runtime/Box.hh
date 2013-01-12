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

            inline runtime::boxes::Class * type( void ) const;

            inline Box & type( runtime::boxes::Class * type );

        public:

            inline runtime::Attribute * attribute( std::pair< runtime::Box::PropertyNS, std::string > key ) const;

            inline Box & attribute( std::pair< runtime::Box::PropertyNS, std::string > key, runtime::Attribute * value );

        public:

            virtual bool operatorBool( void );

        public:

            virtual runtime::Box * operatorNumericPreIncrementation( void );

            virtual runtime::Box * operatorNumericPreDecrementation( void );

            virtual runtime::Box * operatorNumericPostIncrementation( void );

            virtual runtime::Box * operatorNumericPostDecrementation( void );

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

        public:

            virtual runtime::Box * operatorCall( unsigned int argc, runtime::Box ** argv );

            virtual runtime::Box * operatorSubscript( unsigned int argc, runtime::Box ** argv );

        public:

            runtime::boxes::Class * mType;

            std::map< std::pair< runtime::Box::PropertyNS, std::string >, runtime::Attribute * > mAttributes;

        };

    }

}

#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Attribute.hh"

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
