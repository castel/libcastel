#include <cstring>

#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/StringBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::StringBox;

StringBox & StringBox::value( char const * value, int length, bool copy )
{
    if ( value ) {
        mLength = length == -1 ? std::strlen( value ) : length;
        mValue = copy ? std::strcpy( reinterpret_cast< char * >( castel_allocate( mLength + 1, 1 ) ), value ) : value;
    } else {
        mValue = std::strcpy( reinterpret_cast< char * >( castel_allocate( 1, 1 ) ), "" );
        mLength = 0;
    }

    return * this;
}


runtime::Box * StringBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * StringBox::additionOperator( runtime::Box * operand )
{
    runtime::StringBox * stringOperand = dynamic_cast< runtime::StringBox * >( operand );

    if ( ! stringOperand )
        return nullptr;

    int length = mLength + stringOperand->mLength;
    char * value = reinterpret_cast< char * >( castel_allocate( length + 1, sizeof( char ) ) );

    std::strcpy( value, mValue );
    std::strcpy( value + mLength, stringOperand->mValue );
    value[ length ] = '\0';

    return runtime::StringBox::create( value, length, false );
}

runtime::Box * StringBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::equalOperator( runtime::Box * operand )
{
    runtime::StringBox * stringOperand = dynamic_cast< runtime::StringBox * >( operand );

    if ( ! stringOperand )
        return nullptr;

    return runtime::BooleanBox::create( mLength == stringOperand->mLength && std::strcmp( mValue, stringOperand->mValue ) == 0 );
}

runtime::Box * StringBox::notEqualOperator( runtime::Box * operand )
{
    runtime::StringBox * stringOperand = dynamic_cast< runtime::StringBox * >( operand );

    if ( ! stringOperand )
        return nullptr;

    return runtime::BooleanBox::create( mLength != stringOperand->mLength || std::strcmp( mValue, stringOperand->mValue ) != 0 );
}

runtime::Box * StringBox::additionAssignmentOperator( runtime::Box * operand )
{
    runtime::StringBox * stringOperand = dynamic_cast< runtime::StringBox * >( operand );

    if ( ! stringOperand )
        return nullptr;

    int length = mLength + stringOperand->mLength;
    char * value = reinterpret_cast< char * >( castel_allocate( length + 1, sizeof( char ) ) );

    std::strcpy( value, mValue );
    std::strcpy( value + mLength, stringOperand->mValue );
    value[ length ] = '\0';

    this->value( value, length, false );

    return this;
}

runtime::Box * StringBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * StringBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * StringBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool StringBox::booleanOperator( void )
{
    return false;
}
