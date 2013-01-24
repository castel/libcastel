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

            virtual bool operatorBoolCast( void );

        public:

            virtual runtime::Box * operatorPreIncrementation( void );

            virtual runtime::Box * operatorPreDecrementation( void );

            virtual runtime::Box * operatorPostIncrementation( void );

            virtual runtime::Box * operatorPostDecrementation( void );

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

        public:

            virtual runtime::Box * operatorSubscript( unsigned int argc, runtime::Box ** argv );

            virtual runtime::Box * operatorCall( unsigned int argc, runtime::Box ** argv );

            virtual runtime::Box * operatorNew( unsigned int argc, runtime::Box ** argv );

            virtual runtime::Box * operatorRequire( unsigned int argc, runtime::Box ** argv );

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
